#pragma once

#include "layers/Layer.h"
#include "media/Image.h"
#include "media/Text.h"
#include "layers/graphics/Viewport.h"
#include "layers/graphics/Color.h"

using namespace media;
using namespace graphics;

namespace layers {

	class Graphics : public Layer
	{

	protected:

		bool closed = false;

	public: 

		void setClosed() { closed = true; }
		
		const bool isClosed() const { return closed; }

		virtual void initialize() = 0;

		virtual void beforeRender() const = 0;

		virtual void clear() const = 0;

		virtual void render() const = 0;

		virtual void drawImage(const std::string imageName, const float x, const float y) const = 0;

		virtual void drawImage(Image* image, const float x, const float y) const = 0;

		virtual void drawImage(const std::string imageName, const float x, const float y, const Viewport viewport) const = 0;

		virtual void drawImage(Image* image, const float x, const float y, const Viewport viewport) const = 0;

		virtual void drawText(const Text text, const float x, const float y) const = 0;

		virtual void drawText(const Text text, const float x, const float y, const Viewport viewport) const = 0;

		virtual void fillRect(const float x, const float y, const float width, const float height, const Color color) const = 0;

		virtual void fillRect(const float x, const float y, const float width, const float height, const Color color, const Viewport viewport) const = 0;

		virtual Image* getImage(const std::string filename) = 0;

		virtual void onClose() const = 0;

	};

}