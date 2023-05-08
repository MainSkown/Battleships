#ifndef BATTLESHIPS_BUTTON_H
#define BATTLESHIPS_BUTTON_H

#include <SDL.h>
#include <functional>
#include "UI.h"
#include "UIElements.h"

class Button : public UIElement {
private:
    std::function<void()> onClick;
public:
    Button(const char* path, int x, int y, int w, int h, std::function<void()> onClick);
    void HandleEvent(const SDL_Event* event) override;
    void update() override;
    std::vector<SDL_EventType> getAllEventsUsed() override;
};


#endif //BATTLESHIPS_BUTTON_H
