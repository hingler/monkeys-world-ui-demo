#include <gamemenu/GameMenu.hpp>
#include <critter/ui/UIGroup.hpp>
#include <gamemenu/ui/SlidingBlindsTransition.hpp>
#include <gamemenu/ui/MenuBG.hpp>
#include <gamemenu/ui/CourseSelectGroup.hpp>
#include <gamemenu/ui/StageBanner.hpp>
#include <gamemenu/ui/StageSelectTransition.hpp>

#include <gamemenu/game/ContainerObject.hpp>

#include <game/SlidingCamera.hpp>

#include <shader/light/SpotLight.hpp>

#include <critter/ui/layout/Margin.hpp>
#include <critter/ui/UIImage.hpp>
#include <critter/GameCamera.hpp>

namespace gamemenu {

using ::monkeysworld::shader::light::SpotLight;
using ::monkeysworld::critter::ui::UIGroup;
using ui::SlidingBlindsTransition;
using ui::CourseSelectGroup;
using ui::StageBanner;
using namespace ::monkeysworld::critter::ui::layout;
using ::monkeysworld::critter::ui::UIImage;

using ::monkeysworld::critter::GameCamera;

using game::ContainerObject;

GameMenu::GameMenu() {

}

void GameMenu::SetLastFrameTexture(GLuint color) {
}

std::string GameMenu::GetSceneIdentifier() {
  return "game_menu";
}

void GameMenu::Initialize(::monkeysworld::engine::Context* ctx) {
  auto transition_screen = std::make_shared<SlidingBlindsTransition>(ctx);
  auto bg = std::make_shared<ui::MenuBG>(ctx);
  auto picks = std::make_shared<CourseSelectGroup>(ctx);
  auto banner = std::make_shared<StageBanner>(ctx);
  auto transition_obj = std::make_shared<ui::StageSelectTransition>(ctx);

  bg->SetId(GRID_BG_ID);
  picks->SetId(SELECT_GROUP_ID);
  banner->SetId(BANNER_ID);
  transition_obj->SetId(TRANSITION_ID);

  transition_screen->z_index = -10000;
  bg->z_index = 10;
  picks->z_index = 0;
  banner->z_index = -100;

  auto margins = transition_screen->GetLayoutParams();
  auto win = GetWindow();


  margins.top.anchor_id = banner->GetId();
  margins.top.anchor_face = Face::BOTTOM;
  margins.top.margin = 0;
  picks->SetLayoutParams(margins);

  margins.left.anchor_id = win->GetId();
  margins.left.anchor_face = Face::LEFT;
  margins.left.margin = 0;

  margins.right.anchor_id = win->GetId();
  margins.right.anchor_face = Face::RIGHT;
  margins.right.margin = 0;

  margins.top.anchor_id = win->GetId();
  margins.top.anchor_face = Face::TOP;

  banner->SetLayoutParams(margins);

  margins.bottom.anchor_id = win->GetId();
  margins.bottom.anchor_face = Face::BOTTOM;
  margins.bottom.margin = 0;

  transition_screen->SetLayoutParams(margins);
  bg->SetLayoutParams(margins);


  win->AddChild(transition_screen);
  win->AddChild(bg);
  win->AddChild(picks);
  win->AddChild(banner);
  win->AddChild(transition_obj);

  auto container = std::make_shared<ContainerObject>(ctx);
  container->SetPosition(glm::vec3(0, -0.3, -9.6));
  container->SetScale(glm::vec3(0.22, 1.0, 1.0));
  container->SetRotation(glm::vec3(0, -1.5706, 0));
  GetGameObjectRoot()->AddChild(container);

  auto sliding_cam = std::make_shared<::game::SlidingCamera>(ctx);
  sliding_cam->SetId(CAMERA_ID);

  sliding_cam->SetStartPosition(glm::vec3(-15, 0, 0));
  sliding_cam->SetStartRotation(glm::vec3(0, -0.92, 0));
  sliding_cam->SetEndPosition(glm::vec3(0));
  sliding_cam->SetEndRotation(glm::vec3(0));
  sliding_cam->SetSlideDuration(2.5f);
  sliding_cam->SetFov(36.0f);
  sliding_cam->SetActive(true);
  GetGameObjectRoot()->AddChild(sliding_cam);
  
  auto lite = std::make_shared<SpotLight>(ctx);
  lite->SetPosition(glm::vec3(0, -12, 0));
  lite->SetColor(glm::vec3(1.0, 1.0, 1.0));
  lite->SetDiffuseIntensity(1.0);
  lite->SetSpecularIntensity(1.0);
  lite->SetAttenuationConst(1.0f);
  lite->SetAttenuationLinear(0.0f);
  lite->SetAttenuationQuad(0.0f);
  GetGameObjectRoot()->AddChild(lite);

}


}