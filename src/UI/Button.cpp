#include "Button.h"
#include "../TextureManager.h"

Button::Button(const char *path, int x, int y, int w, int h, std::function<void()> onClick) {
    texture = TextureManager::LoadTexture(path);
    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;
    this->onClick = onClick;
}

void Button::HandleEvent(const SDL_Event *event) {
    if(event->type == SDL_MOUSEBUTTONDOWN){
        int x,y;
        SDL_GetMouseState(&x, &y);
        if(x >= destRect.x && x <= destRect.x + destRect.w && y >= destRect.y && y <= destRect.y + destRect.h){
            onClick();
        }
    }
}

void Button::update() {

}

std::vector<SDL_EventType> Button::getAllEventsUsed() {
    std::vector<SDL_EventType> events = {SDL_MOUSEBUTTONDOWN};
    return events;
}