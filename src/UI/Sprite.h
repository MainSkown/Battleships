#ifndef BATTLESHIPS_SPRITE_H
#define BATTLESHIPS_SPRITE_H

#include "UI.h"
#include "UIElements.h"

class Sprite: public UIElement {
    public:
    Sprite(const char* texturePath, int x, int y, int width, int height);
    void HandleEvent(const SDL_Event* event) override;
    void update() override {};
    std::vector<SDL_EventType> getAllEventsUsed() override;
    ~Sprite() override;
};


#endif //BATTLESHIPS_SPRITE_H
