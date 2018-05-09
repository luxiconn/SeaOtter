

#include "DataSaver.h"

#include "FileUtils.h"
#include "StringUtils.h"

Otter::DataSaver::DataSaver(std::string t_filePath) {
  DefaultPath = t_filePath;
}

bool Otter::DataSaver::verify(std::string t_stringData) {
  auto splitString = Otter::StringUtils::split(t_stringData, ':');

  if (splitString.size() != 2)
    return false;

  std::string dataToHash = SaltGuide;
  dataToHash = Otter::StringUtils::replace(dataToHash, "{S}", EncryptionSalt);
  dataToHash = Otter::StringUtils::replace(dataToHash, "{D}", splitString[1]);

  std::string hash = Otter::StringUtils::md5(dataToHash);

  if (hash == splitString[0])
    return true;

  return false;
}

void Otter::DataSaver::clearFile(std::string t_fileName = "") {
  if (t_fileName == "")
    t_fileName = DefaultFilename;

  t_fileName = DefaultPath + t_fileName;
  if (!Otter::FileUtils::fileExists(t_fileName))
    return;

  remove(t_fileName.c_str());
}

void Otter::DataSaver::clear() { m_data.clear(); }

bool Otter::DataSaver::fileExists(std::string t_fileName) {
  if (t_fileName == "")
    t_fileName = DefaultFilename;

  t_fileName = DefaultPath + t_fileName;
  if (Otter::FileUtils::fileExists(t_fileName)) {
    std::string loaded;
    Otter::FileUtils::readFileToBuffer(t_fileName, loaded);

    if (ExportMode == DataExportMode::Data) {
      return verify(loaded);
    } else {
      return true;
    }
  }

  return false;
}

void Otter::DataSaver::import(std::string t_fileName, bool t_verify) {
  if (t_fileName == "")
    t_fileName = DefaultFilename;

  t_fileName = DefaultPath + t_fileName;
  if (!Otter::FileUtils::fileExists(t_fileName))
    return;

  std::string loaded;
  Otter::FileUtils::readFileToBuffer(t_fileName, loaded);

  if (ExportMode == DataExportMode::Data) {
    if (verify(loaded) || !t_verify) {
      std::vector<std::string> splitString =
          Otter::StringUtils::split(loaded, ':');
    }
  }
}
