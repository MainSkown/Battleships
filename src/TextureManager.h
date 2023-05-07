#ifndef BATTLESHIPS_TEXTUREMANAGER_H
#define BATTLESHIPS_TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* path);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};


#endif //BATTLESHIPS_TEXTUREMANAGER_H
