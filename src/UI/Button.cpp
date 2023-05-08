#include "Button.h"
#include "../TextureManager.h"

Button::Button(const char *path, int x, int y, int w, int h) {
    texture = TextureManager::LoadTexture(path);
    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;
}

void Button::HandleEvent(const SDL_Event *event) {

}

void Button::update() {

}

std::vector<SDL_EventType> Button::getAllEventsUsed() {
    std::vector<SDL_EventType> events = {SDL_MOUSEBUTTONDOWN};
    return events;
}