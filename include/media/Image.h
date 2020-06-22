#pragma once

#include <string>
#include "utils/FileUtils.h"

using namespace utils;

namespace media {

	class Image {

	private:

		float width;

		float height;

		std::string filename;

	public:

		Image(const std::string filename, const float width, const float height) {
			this->filename = filename;
			this->width = width;
			this->height = height;
		}

		const float getWidth() const { return width; }

		void setWidth(const float width) { this->width = width; }

		const float getHeight() const { return height; }

		void setHeight(const float height) { this->height = height; }

		const std::string getFilename() const { return filename; }

		void setFilename(const std::string filename) { this->filename = filename; }

		const std::string getExtension() { return FileUtils::getExtension(filename); }

	};

}