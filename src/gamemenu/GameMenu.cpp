#include <gamemenu/GameMenu.hpp>
#include <critter/ui/UIGroup.hpp>
#include <gamemenu/ui/SlidingBlindsTransition.hpp>

#include <critter/ui/layout/Margin.hpp>

namespace gamemenu {

using ::monkeysworld::critter::ui::UIGroup;
using ui::SlidingBlindsTransition;
using ::monkeysworld::critter::ui::layout::Face;

GameMenu::GameMenu() : initialized_(false) {

}

void GameMenu::SetLastFrameTexture(GLuint color) {
  if (initialized_.load()) {
    // pass the color to the relevant component
    return;
  }
}

void GameMenu::Initialize(::monkeysworld::engine::Context* ctx) {
  auto transition_screen = std::make_shared<SlidingBlindsTransition>(ctx);
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
  win->AddChild(transition_screen);
}


}