#include "Game.h"

#include <string>

#include <Utility/DataSaver.h>

// Otter::Game(std::string t_title, int32_t t_width, int32_t t_height, int32_t
// t_targetFramerate, bool t_fullscreen) {
//   m_saveData = DataSaver(m_filePath);
//   m_optionsData = DataSaver(m_filePath);
//   m_configData = DataSaver(m_filePath);
// }
Otter::Game::Game(std::string t_title, int32_t t_width, int32_t t_height,
                  int32_t t_targetFramerate, bool t_fullscreen) {
  m_saveData = DataSaver(GetFilepath());
  m_optionsData = DataSaver(GetFilepath());
  m_configData = DataSaver(GetFilepath());
}
