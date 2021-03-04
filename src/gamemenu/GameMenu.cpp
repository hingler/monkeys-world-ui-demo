#include <gamemenu/GameMenu.hpp>
#include <critter/ui/UIGroup.hpp>
#include <gamemenu/ui/SlidingBlindsTransition.hpp>
#include <gamemenu/ui/MenuBG.hpp>

#include <critter/ui/layout/Margin.hpp>
#include <critter/ui/UIImage.hpp>

namespace gamemenu {

using ::monkeysworld::critter::ui::UIGroup;
using ui::SlidingBlindsTransition;
using namespace ::monkeysworld::critter::ui::layout;
using ::monkeysworld::critter::ui::UIImage;

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
  bg->z_index = 10;

  transition_screen->z_index = -10000;
  
  auto margins = transition_screen->GetLayoutParams();
  auto win = GetWindow();

  margins.left.anchor_id = win->GetId();
  margins.left.anchor_face = Face::LEFT;
  margins.left.margin = 0;

  margins.right.anchor_id = win->GetId();
  margins.right.anchor_face = Face::RIGHT;
  margins.right.margin = 0;

  margins.bottom.anchor_id = win->GetId();
  margins.bottom.anchor_face = Face::BOTTOM;
  margins.bottom.margin = 0;

  margins.top.anchor_id = win->GetId();
  margins.top.anchor_face = Face::TOP;
  margins.top.margin = 0;

  transition_screen->SetLayoutParams(margins);
  bg->SetLayoutParams(margins);

  win->AddChild(transition_screen);
  win->AddChild(bg);

  std::shared_ptr<UIImage> image_b = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionB.png");
  margins = image_b->GetLayoutParams();

  margins.left.anchor_id = margins.right.anchor_id = margins.top.anchor_id = margins.bottom.anchor_id = win->GetId();
  margins.left.margin = margins.right.margin = margins.top.margin = margins.bottom.margin = MarginType::AUTO;
  margins.top.anchor_face = Face::TOP;
  margins.bottom.anchor_face = Face::BOTTOM;
  margins.left.anchor_face = Face::LEFT;
  margins.right.anchor_face = Face::RIGHT;

  image_b->z_index = -10;

  image_b->SetLayoutParams(margins);
  image_b->SetDimensions(glm::vec2(360, 400));

  std::shared_ptr<UIImage> image_a = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionA.png");
  margins.left.anchor_id = 0;
  margins.left.margin = 0.0f;

  margins.right.anchor_id = image_b->GetId();
  margins.right.margin = 16.0f;
  margins.right.anchor_face = Face::LEFT;

  image_a->SetLayoutParams(margins);
  image_a->SetDimensions(glm::vec2(360, 400));

  image_a->z_index = -10;

  std::shared_ptr<UIImage> image_c = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionC.png");
  margins.left.anchor_id = image_b->GetId();
  margins.left.margin = 16.0f;
  margins.left.anchor_face = Face::RIGHT;

  margins.right.anchor_id = 0;
  margins.right.margin = 0.0f;

  image_c->SetLayoutParams(margins);
  image_c->SetDimensions(glm::vec2(360, 400));

  image_c->z_index = -10;

  win->AddChild(image_a);
  win->AddChild(image_b);
  win->AddChild(image_c);
}


}