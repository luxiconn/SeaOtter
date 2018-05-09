#ifndef SEAOTTER_CORE_GAME_H
#define SEAOTTER_CORE_GAME_H

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <Components/Button.h>
#include <Core/Input.h>
#include <Core/Scene.h>
#include <Core/Session.h>
#include <Graphics/Atlas.h>
#include <Graphics/Color.h>
#include <Graphics/Drawables/Surface.h>
#include <Utility/Coroutine.h>
#include <Utility/DataSaver.h>
#include <Utility/DebugInput.h>
#include <Utility/Debugger.h>
#include <Utility/Tweener.h>
#include <Utility/Vector2.h>

namespace Otter {
class Game {
public:
  Game() = default;
  Game(std::string t_title, int32_t t_width, int32_t t_height,
       int32_t t_targetFramerate, bool t_fullscreen);
  static Game Instance;

  int32_t TargetFramerate = 0;
  bool FixedFramerate = true;
  bool Active = false;
  bool Paused = false;

  std::function<void()> OnInit;
  std::function<void()> OnUpdate;
  std::function<void()> OnSceneBegin;
  std::function<void()> OnSceneEnd;
  std::function<void()> OnEnd;
  std::function<void()> OnFocusLost;
  std::function<void()> OnFocusGained;
  std::function<void()> OnEndOfUpdate;
  std::function<void()> OnStartofNextUpdate;

  bool DrawInactiveScenes = true;
  Otter::Color Color;
  Otter::Color LetterBoxColor;
  float Timer;
  Scene FirstScene;
  int32_t GameFrames;
  bool MeasureTimeinFrames = true;
  bool LockMouse;
  int32_t LockMousePadding = 10;
  bool LockMouseCenter;
  bool AlwaysUpdate = true;
  Otter::Atlas Atlas;
  bool LockAspectRatio = true;
  Otter::Button QuitButton;
  Otter::Button ScreenshotButton;
  bool EnableQuitButton = true;
  bool EnableAltF4 = true;
  bool InvertAngleY = true;
  bool ReleaseModeDebugger = false;
  bool WindowResize = true;
  bool WindowClose = true;
  bool WindowBorder = true;
  bool LogExceptionsToFile;

  std::string GetTitle() { return m_title; }
  void SetTitle(std::string t_title) { m_title = t_title; }

  int32_t GetWindowX() { return m_window.getPosition().x; }
  void SetWindowX(int32_t t_x) {
    sf::Vector2i pos(t_x, m_window.getPosition().y);
    m_window.setPosition(pos);
  }

  int32_t GetWindowY() { return m_window.getPosition().y; }
  void SetWindowY(int32_t t_y) {
    sf::Vector2i pos(m_window.getPosition().x, t_y);
    m_window.setPosition(pos);
  }

  Otter::Vector2 GetCenter() {
    return Vector2(getHalfWidth(), getHalfHeight());
  }

  Otter::Debugger GetDebugger() { return m_debugger; }

  Otter::Coroutine GetCoroutine() { return m_coroutine; }

  Otter::Tweener GetTweener() { return m_tweener; }

  bool ShowDebugger() { return m_showDebugger; }

  float GetFramerate() { return m_frameRate; }

  float GetAverageFramerate() { return m_averageFramerate; }

  float GetDeltaTime() { return m_deltaTime; }

  int32_t GetWidth() { return m_width; }
  int32_t GetHeight() { return m_height; }
  int32_t GetWindowWidth() { return m_windowWidth; }
  int32_t GetWindowHeight() { return m_windowHeight; }
  bool GetWindowFullscreen() { return m_windowFullscreen; }
  std::vector<Otter::Scene> GetScenes() { return m_sceneList; }
  std::vector<Otter::Session> GetSessions() { return m_sessionList; }
  Otter::Input GetInput() { return m_input; }
  Otter::DebugInput GetDebugInput() { return m_debugInput; }
  Otter::Surface GetSurface() { return m_surface; }
  bool IsDebugMode() { return m_isDebugMode; }
  int32_t GetMouseDeltaX() { return m_mouseDeltaX; }
  int32_t GetMouseDeltaY() { return m_mouseDeltaY; }
  bool HasFocus() { return m_hasFocus; }
  Otter::DataSaver GetOptionsData() { return m_optionsData; }
  Otter::DataSaver GetSaveData() { return m_saveData; }
  Otter::DataSaver GetConfigData() { return m_configData; }
  std::string GetGameFolder() { return m_gameFolder; }
  void SaveGameFolder(std::string t_value) {
    m_gameFolder = t_value;

    // TODO: Convert this to C
    // var folder =
    // Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) + "/" +
    // GameFolder; if (!Directory.Exists(folder)) {
    //     Directory.CreateDirectory(folder);
    // }
    // SaveData.DefaultPath = Filepath;
    // OptionsData.DefaultPath = Filepath;
    // ConfigData.DefaultPath = Filepath;
  }

  std::string GetFilepath() {
    // TODO: Fix this
    // return Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) +
    // "/" + GameFolder + "/";
    return "";
  }

  float GetAspectRatio() { return m_aspectRatio; }
  int32_t Second() { return (int)TargetFramerate; }

  std::vector<Otter::Surface> GetSurfaces() { return m_surfaces; }
  float GetCameraAngle() { return m_cameraAngle; }
  float SetCameraAngle(float t_value) {
    m_cameraAngle = t_value;
    updateView();
  }

  float getCameraZoom() { return m_cameraZoom; }
  void setCameraZoom(float t_value) {
    m_cameraZoom = t_value;
    if (m_cameraZoom <= 0) {
      m_cameraZoom = 0.0001f;
    }
    updateView();
  }

  float getRealDeltaTime() { return m_realDeltaTime; }

  bool isMouseVisible() { return m_mouseVisible; }
  void setMouseVisible(bool t_value) { m_mouseVisible = t_value; }

  int32_t GetRenderTime() {

    // TODO: Fix this with stopwatch
    // return m_updateTime.ElapsedMilliseconds;
    return 0;
  }

  int32_t GetUpdateTime() {
    // TODO: Fix this with stopwatch
    // return m_updateTime.ElaspsedMilliseconds;
    return 0;
  }

  int32_t GetRenderCount() { return m_renderCount; }
  int32_t GetUpdateCount() { return m_updateCount; }

  int getHalfWidth();
  int getHalfHeight();

private:
  void updateView();

  // TODO: Might have to make our own stopwatch class
  // auto m_renderTime = std::chrono::high_resolution_clock::now();
  // auto m_updateTime = std::chrono::high_resolution_clock::now();
  // auto m_gameTime = std::chrono::high_resolution_clock::now();

  float m_cameraAngle, m_cameraZoom = 0.0f;
  float m_deltaTime = 0.0f;
  float m_frameTime = 0.0f;
  float m_fpsTime = 0.0f;
  float m_skipTime = 0.0f;

  sf::View m_view;
  sf::RenderWindow m_window;

  std::vector<Scene> m_goToScenes;
  Scene m_goToScene;
  std::vector<Scene> m_scenesToRender;

  std::string m_gameFolder;

  std::vector<float> m_fpsTimes;
  int32_t m_nextFpsIndex = 0;
  int32_t m_fpsLogSize = 20;

  bool m_windowSet = false;
  bool m_updatedOnce = false;

  bool m_mouseVisible = false;
  uint32_t m_iconWidth, m_iconHeight = 0;
  std::string m_iconPath;

  sf::Image m_iconImage;

  std::string m_title;
  int32_t m_sleepTime;

  Otter::Debugger m_debugger;
  Otter::Coroutine m_coroutine;
  Otter::Tweener m_tweener;
  bool m_showDebugger;
  float m_frameRate;
  float m_averageFramerate;

  int32_t m_width;
  int32_t m_height;
  int32_t m_windowWidth;
  int32_t m_windowHeight;
  bool m_windowFullscreen;

  std::vector<Otter::Scene> m_sceneList;
  std::vector<Otter::Session> m_sessionList;
  Otter::Input m_input;
  Otter::DebugInput m_debugInput;
  Otter::Surface m_surface;
  bool m_isDebugMode;

  int32_t m_mouseDeltaX;
  int32_t m_mouseDeltaY;

  bool m_hasFocus;

  Otter::DataSaver m_optionsData;
  Otter::DataSaver m_saveData;
  Otter::DataSaver m_configData;

  float m_aspectRatio;

  std::vector<Otter::Surface> m_surfaces;
  float m_realDeltaTime;

  int32_t m_renderCount;
  int32_t m_updateCount;
};
} // namespace Otter

#endif // SEAOTTER_CORE_GAME_H