#ifndef SPLASH_SCREEN_H_
#define SPLASH_SCREEN_H_

#include <engine/Scene.hpp>

namespace scene {

struct SplashScreen : public ::monkeysworld::engine::Scene {
  SplashScreen();
  void Initialize(::monkeysworld::engine::Context* ctx) override;
  std::shared_ptr<::monkeysworld::critter::GameObject> GetGameObjectRoot() override;
  std::shared_ptr<::monkeysworld::critter::ui::UIObject> GetUIObjectRoot() override;
};

}

#endif