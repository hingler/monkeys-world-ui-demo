#include <gamemenu/GameMenu.hpp>
#include <critter/ui/UIGroup.hpp>
#include <gamemenu/ui/SlidingBlindsTransition.hpp>

#include <critter/ui/layout/Margin.hpp>
#include <critter/ui/UIImage.hpp>

namespace gamemenu {

using ::monkeysworld::critter::ui::UIGroup;
using ui::SlidingBlindsTransition;
using ::monkeysworld::critter::ui::layout::Face;
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
  auto bg = std::make_shared<UIImage>(ctx, "resources/unknown.png");
  bg->z_index = 10;

  transition_screen->z_index = -10000;
  
  auto margins = transition_screen->GetLayoutParams();
  auto win = GetWindow();

  margins.left.anchor_id = win->GetId();
  margins.left.anchor_face = Face::LEFT;
  margins.left.dist = 0;

  margins.right.anchor_id = win->GetId();
  margins.right.anchor_face = Face::RIGHT;
  margins.right.dist = 0;

  margins.bottom.anchor_id = win->GetId();
  margins.bottom.anchor_face = Face::BOTTOM;
  margins.bottom.dist = 0;

  margins.top.anchor_id = win->GetId();
  margins.top.anchor_face = Face::TOP;
  margins.top.dist = 0;

  transition_screen->SetLayoutParams(margins);
  bg->SetLayoutParams(margins);

  win->AddChild(transition_screen);
  win->AddChild(bg);
}


}