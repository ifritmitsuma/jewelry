#include "layers/graphics/Button.h"
#include "layers/graphics/GraphicsManager.h"

using namespace graphics;

void Button::drawButton(const float containerX, const float containerY, const bool hover, const graphics::Viewport* viewport) const {

    Color color = { 100, 100, 100, 255 };
    
    if (viewport == nullptr) {
        layers::GraphicsManager::fillRect(containerX, containerY, 200, 60, color);

        if (hover) {
            color = { 255, 255, 255, 127 };
            layers::GraphicsManager::fillRect(containerX, containerY, 200, 60, color);
        }

        layers::GraphicsManager::drawText(text, containerX + (200 - text.size / 2 * text.text.size()) / 2, containerY + (60 - text.size) / 2);
    }
    else {
        layers::GraphicsManager::fillRect(containerX, containerY, 200, 60, color, *viewport);

        if (hover) {
            color = { 255, 255, 255, 127 };
            layers::GraphicsManager::fillRect(containerX, containerY, 200, 60, color, *viewport);
        }

        layers::GraphicsManager::drawText(text, containerX + (200 - text.size / 2 * text.text.size()) / 2, containerY + (60 - text.size) / 2, *viewport);
    }



}