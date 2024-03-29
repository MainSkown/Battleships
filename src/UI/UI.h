#ifndef BATTLESHIPS_UI_H
#define BATTLESHIPS_UI_H

#include <SDL.h>
#include <vector>
#include <bitset>
#include <memory>
#include <algorithm>
#include <iostream>

class UILayer;

class UIElement;

using EventBitset = std::bitset<32>;

class UIElement {
protected:
    SDL_Rect srcRect, destRect;
    SDL_Texture *texture;

public:
    bool active = true;

    virtual void HandleEvent(const SDL_Event *event) = 0;

    virtual void update() = 0;

    virtual std::vector<SDL_EventType> getAllEventsUsed() = 0;

    void draw();

    virtual ~UIElement();

    virtual void clean();
};

class UILayer {
private:
    std::vector<std::unique_ptr<UIElement>> elements;

    EventBitset eventTypes;
public:
    void update() { for (auto &c: elements) c->update(); }

    void draw() { for (auto &element: elements) if (element->active)element->draw(); };

    void HandleEvent(const SDL_Event *event) {
        // Must be reversed because of the element may be deleted in the middle of the loop
        for (int i = elements.size() - 1; i >= 0; i--) if (elements[i]->active) elements[i]->HandleEvent(event);
    }

    template<typename T, typename... tArgs>
    T &AddElement(tArgs &&... mArgs) {
        T *element(new T(std::forward<tArgs>(mArgs)...));
        std::unique_ptr<UIElement> uPtr{element};

        elements.emplace_back(std::move(uPtr));

        auto events = element->getAllEventsUsed();
        for (auto e: events) {
            eventTypes[e] = true;
        }

        return *element;
    };


    bool HasEvent(Uint32 eT) const {
        return eventTypes[eT];
    }

    void DeleteElement(UIElement *element) {
        auto el =
                std::find_if(elements.begin(), elements.end(),
                             [&](std::unique_ptr<UIElement> &e) { return e.get() == element; });
        el->reset();
        elements.erase(std::remove(elements.begin(), elements.end(), *el), elements.end());
    }
};


#endif //BATTLESHIPS_UI_H
