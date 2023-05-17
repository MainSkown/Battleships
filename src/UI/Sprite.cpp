#include "Sprite.h"
#include "../TextureManager.h"

Sprite::Sprite(const char *texturePath, int x, int y, int width, int height) {
    texture = TextureManager::LoadTexture(texturePath);
    srcRect.x = srcRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
}

Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}

std::vector<SDL_EventType> Sprite::getAllEventsUsed() {
    return {};
}

void Sprite::HandleEvent(const SDL_Event *event) {

}