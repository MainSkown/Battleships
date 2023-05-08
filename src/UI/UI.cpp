#include "UI.h"
#include "../TextureManager.h"

/* UIElement */
void UIElement::draw() {
    TextureManager::Draw(texture, srcRect, destRect);
};

void UIElement::clean() {
    SDL_DestroyTexture(texture);
}

UIElement::~UIElement() noexcept {
    clean();
}
