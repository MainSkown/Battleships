#include "UI.h"
#include "../TextureManager.h"

/* UIElement */
void UIElement::draw() {
    TextureManager::Draw(texture, srcRect, destRect);
};