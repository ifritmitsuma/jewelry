#pragma once

#include <string>
#include "utils/FileUtils.h"

using namespace utils;

namespace media {

	class Image {

	private:

		int width;

		int height;

		std::string filename;

	public:

		Image(const std::string filename, const int width, const int height) {
			this->filename = filename;
			this->width = width;
			this->height = height;
		}

		const int getWidth() const { return width; }

		void setWidth(const int width) { this->width = width; }

		const int getHeight() const { return height; }

		void setHeight(const int height) { this->height = height; }

		const std::string getFilename() { return filename; }

		void setFilename(const std::string filename) { this->filename = filename; }

		const std::string getExtension() { return FileUtils::getExtension(filename); }

	};

}