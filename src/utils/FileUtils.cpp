#include "utils/FileUtils.h"

using namespace utils;

std::string FileUtils::getExtension(std::string filename) {

	if (filename.size() == 0) {
		return "";
	}

	int sepIndex = filename.find_last_of('.');

	if (sepIndex == -1) {
		return "";
	}

	return filename.substr(sepIndex + 1, filename.size() - sepIndex);

}