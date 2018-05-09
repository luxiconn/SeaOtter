#ifndef SEAOTTER_UTILITY_DATASAVER_H
#define SEAOTTER_UTILITY_DATASAVER_H

#include <map>
#include <string>

namespace Otter {

enum class DataExportMode { Data, Config };

class DataSaver {
public:
  /*
   * Initalizes a new instance of the DataSaver class
   */
  DataSaver(std::string t_defaultPath);
  DataSaver() = default;

  /*
   * Verifies the specified string data. Only applies to DataExportMode.Data
   */
  bool verify(std::string t_stringData);

  /*
   * Deletes the exported file for this save data
   */
  void clearFile(std::string t_filename);

  /*
   * Clears the data
   */
  void clear();

  /*
   * Check if an exported file exists for this data
   */
  bool fileExists(std::string filename);

  /*
   * Imports the data in the specified file
   */
  void import(std::string t_filename, bool t_verify);

  /*
   * exports the data to the specified file
   */
  void exportData(std::string t_filename);

  std::string operator[](std::string t_key) {
    auto value = m_data.find(t_key);

    if (value == m_data.end()) {
      return nullptr;
    }

    return value->second;
  }

  std::string operator[](enum t_key) {
    std::string keyAsString = "";
    auto value = m_data.find(keyAsString);

    if (value == m_data.end()) {
      return nullptr;
    }

    return value->second;
  }

  float getFloat(std::string t_key);

  float getFloatOrDefault(std::string t_key, float t_default);

  float getFloatOrDefault(enum t_key, float t_default);

  int32_t getInt(std::string t_key);

  int32_t getInt(enum t_key);

  int32_t getIntOrDefault(std::string t_key, int t_default);

  int32_t getIntOrDefault(enum t_key, int t_default);

  std::string getString(std::string t_key);
  std::string getString(enum t_key);

  std::string getStringOrDefault(std::string t_key, std::string t_default);
  std::string getStringOrDefault(enum t_key, std::string t_default);

  bool getBool(std::string t_key);
  bool getBool(enum t_key);

  bool getBoolOrDefault(std::string t_key, bool t_default);
  bool getBoolOrDefault(enum t_key, bool t_default);

  void setData(std::string t_key, std::string t_value);
  void setData(enum t_key, std::string t_value);

  /**
   * The string to use when delimiting key data in data exports
   */
  std::string KeyDelim = "::OTTERK::";

  /**
   * The string to use when delimiting value data in data exports
   */
  std::string ValueDelim = "::OTTERV::";

  /*
   * The phase to use as a salt when encrypting the data exports
   */
  std::string EncryptionSalt = "otter";

  /*
   * The guide to salt the data string. {S} is the salt, {D} is the data.
   * It is recommended to change this from the default for your game, but
   * only if you really care about hacking save data.
   */
  std::string SaltGuide = "{S}{D}{S}";

  /*
   * The default path that the files will be imported from and exported to.
   */
  std::string DefaultPath = "";

  /*
   * The default file name that the data will export as
   */
  std::string DefaultFilename = "data";

  DataExportMode ExportMode = DataExportMode::Data;

private:
  std::map<std::string, std::string> m_data;

};
} // namespace Otter

#endif // SEAOTTER_UTILITY_DATASAVER_H