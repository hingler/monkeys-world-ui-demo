#include <critter/Empty.hpp>
#include <critter/GameCamera.hpp>

#include <shader/light/SpotLight.hpp>

#include <scene/SplashScreen.hpp>
#include <game/OctTube.hpp>
#include <game/Monkey.hpp>

#include <glm/gtx/euler_angles.hpp>

#define M_PI_ 3.1415926535897932384626
#define M_PI_2_ 1.57079632679489661923

namespace scene {

using ::monkeysworld::critter::Empty;
using ::monkeysworld::critter::GameCamera;
using ::monkeysworld::engine::Context;
using ::monkeysworld::input::MouseEvent;
using ::monkeysworld::shader::light::SpotLight;
using ::game::OctTube;

SplashScreen::SplashScreen() : game_root_(nullptr), ui_root_(nullptr) {}

void SplashScreen::Initialize(Context* ctx) {
  // im not going to fucking texture shit anyway lol
  game_root_ = std::make_shared<Empty>(ctx);
  game_root_->SetPosition(glm::vec3(0, 0, 0));

  auto tube = std::make_shared<OctTube>(ctx);
  game_root_->AddChild(tube);

  auto cam = std::make_shared<GameCamera>(ctx);
  cam->SetPosition(glm::vec3(0, 0.7, 8));
  cam->SetFov(30.0f);
  cam->SetActive(true);
  game_root_->AddChild(cam);

  auto moneky = std::make_shared<game::Monkey>(ctx);
  moneky->SetScale(glm::vec3(0.3f));
  moneky->SetPosition(glm::vec3(0, 0.38, 0));
  game_root_->AddChild(moneky);

  auto lite = std::make_shared<SpotLight>(ctx);
  lite->SetPosition(glm::vec3(0, -15, 0));
  lite->SetColor(glm::vec3(1.0, 1.0, 1.0));
  lite->SetDiffuseIntensity(1.0);
  lite->SetSpecularIntensity(1.0);
  lite->SetAttenuationConst(1.0f);
  lite->SetAttenuationLinear(0.0f);
  lite->SetAttenuationQuad(0.0f);
  game_root_->AddChild(lite);
}

std::shared_ptr<::monkeysworld::critter::GameObject> SplashScreen::GetGameObjectRoot() {
  return game_root_;
}

std::shared_ptr<::monkeysworld::critter::ui::UIObject> SplashScreen::GetUIObjectRoot() {
  return ui_root_;
}

}