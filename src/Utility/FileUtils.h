#ifndef SEAOTTER_UTILITY_FILE_UTILS_H
#define SEAOTTER_UTILITY_FILE_UTILS_H

#include <fstream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <vector>

namespace Otter {
class FileUtils {
public:
  static bool fileExists(const std::string &t_filename) {
    if (FILE *file = fopen(t_filename.c_str(), "r")) {
      fclose(file);
      return true;
    } else {
      return false;
    }
  }

  static bool readFileToBuffer(std::string filePath, std::string &buffer) {
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
      perror(filePath.c_str());
      return false;
    }

    // seek to the end
    file.seekg(0, std::ios::end);

    // Get the file size
    unsigned int fileSize = (unsigned int)file.tellg();
    file.seekg(0, std::ios::beg);

    // Reduce the file size by any header bytes that might be present
    fileSize -= (unsigned int)file.tellg();

    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize);
    file.close();

    return true;
  }
};
} // namespace Otter
#endif // SEAOTTER_UTILITY_FILE_UTILS_H
