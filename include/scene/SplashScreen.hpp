#ifndef SPLASH_SCREEN_H_
#define SPLASH_SCREEN_H_

#include <engine/Scene.hpp>
#include <file/CachedFileLoader.hpp>

namespace scene {

class SplashScreen : public ::monkeysworld::engine::Scene {
 public:
  SplashScreen();
  void Initialize(::monkeysworld::engine::Context* ctx) override;
  std::shared_ptr<::monkeysworld::critter::GameObject> GetGameObjectRoot() override;
  std::shared_ptr<::monkeysworld::critter::ui::UIObject> GetUIObjectRoot() override;
  std::string GetSceneIdentifier() override;
 private:
  std::shared_ptr<::monkeysworld::critter::GameObject> game_root_;
  std::shared_ptr<::monkeysworld::critter::ui::UIObject> ui_root_;
  std::shared_ptr<::monkeysworld::file::CachedFileLoader> file_loader_;
  
};

}

#endif