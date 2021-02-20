#include <critter/Empty.hpp>
#include <critter/GameCamera.hpp>
#include <critter/ui/FPSCounter.hpp>

#include <shader/light/SpotLight.hpp>

#include <ui/HorizontalMenuGroup.hpp>
#include <ui/LerpMenu.hpp>

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
using ::monkeysworld::file::CachedFileLoader;

using ::monkeysworld::critter::ui::UIGroup;
using ::monkeysworld::critter::ui::FPSCounter;

using ::game::OctTube;
using ::ui::HorizontalMenuGroup;
using ::ui::LerpMenu;

SplashScreen::SplashScreen() : game_root_(nullptr), ui_root_(nullptr) {
  // TODO: propagate this file loader to other parts!
  file_loader_ = std::make_shared<CachedFileLoader>("splash_screen");
}

std::string SplashScreen::GetSceneIdentifier() {
  return "splashscreen";
}

void SplashScreen::Initialize(Context* ctx) {
  // im not going to fucking texture shit anyway lol
  game_root_ = std::make_shared<Empty>(ctx);
  game_root_->SetPosition(glm::vec3(0, 0, 0));

  auto tube = std::make_shared<OctTube>(ctx, file_loader_);
  game_root_->AddChild(tube);

  auto cam = std::make_shared<GameCamera>(ctx);
  cam->SetPosition(glm::vec3(0, 0.7, 8));
  cam->SetFov(30.0f);
  cam->SetActive(true);
  game_root_->AddChild(cam);

  auto moneky = std::make_shared<game::Monkey>(ctx, file_loader_);
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

  std::vector<std::string> test;

  test.push_back("START");
  test.push_back("CONTINUE");
  test.push_back("RESET");
  test.push_back("OPTIONS");
  test.push_back("CREDITS");
  test.push_back("HELLO THERE :)");
  auto menu = std::make_shared<LerpMenu>(ctx, test, "resources/Questrial-Regular.ttf");
  menu->SetMarginSize(128.0f);
  menu->SetTextSize(96.0f);
  menu->SetMenuOffset(0.0f);
  menu->SetDimensions(glm::vec2(900, 150));
  menu->SetPosition(glm::vec2(150, 600));
  BOOST_LOG_TRIVIAL(trace) << "adjust menu params";
  menu->Invalidate();
  std::shared_ptr<UIGroup> group = std::make_shared<UIGroup>(ctx);
  group->SetDimensions(glm::vec2(1920, 1080));
  group->SetPosition(glm::vec2(0));
  group->AddChild(menu);

  std::shared_ptr<FPSCounter> counter = std::make_shared<FPSCounter>(ctx, "resources/Questrial-Regular.ttf");
  counter->SetTextSize(32.0f);
  counter->SetDimensions(glm::vec2(300, 60));
  counter->SetPosition(glm::vec2(5));
  counter->SetTextColor(glm::vec4(1.0));

  group->AddChild(counter);
  ui_root_ = group;
}

std::shared_ptr<::monkeysworld::critter::GameObject> SplashScreen::GetGameObjectRoot() {
  return game_root_;
}

std::shared_ptr<::monkeysworld::critter::ui::UIObject> SplashScreen::GetUIObjectRoot() {
  return ui_root_;
}

}