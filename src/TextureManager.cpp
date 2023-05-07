#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(GameEngine::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(GameEngine::renderer, tex, &src, &dest);
}