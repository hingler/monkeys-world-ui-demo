#include <gamemenu/ui/StageSelectTransition.hpp>
#include <gamemenu/GameMenu.hpp>

#include <engine/Context.hpp>
#include <engine/Scene.hpp>

namespace gamemenu {
namespace ui {

using ::monkeysworld::engine::Context;

StageSelectTransition::StageSelectTransition(Context* ctx) : UIObject(ctx) {
  timer_started_ = false;
  local_delta_ = false;
  banner_swapped_ = false;
}

void StageSelectTransition::Create() {
  auto window = GetContext()->GetScene()->GetWindow();
  stage_select_ = std::dynamic_pointer_cast<CourseSelectGroup>(window->GetChild(GameMenu::SELECT_GROUP_ID));
  banner_ = std::dynamic_pointer_cast<StageBanner>(window->GetChild(GameMenu::BANNER_ID));
  bg_ = std::dynamic_pointer_cast<::monkeysworld::critter::ui::UIObject>(window->GetChild(GameMenu::GRID_BG_ID));

  if (!bg_ || !banner_ || !stage_select_) {
    BOOST_LOG_TRIVIAL(error) << "some IDs did not resolve :sade:";
  }
}

void StageSelectTransition::Update() {
  if (timer_started_) {
    local_delta_ += static_cast<float>(GetContext()->GetDeltaTime());
    if (stage_select_->HideElements(local_delta_) && !banner_swapped_) {
      banner_->Advance();
      banner_swapped_ = true;
    } else if (banner_swapped_) {

    }

    bg_->SetOpacity(std::max(0.0f, 1.0f - (local_delta_ / 2)));
  }
}

void StageSelectTransition::StartTransition() {
  timer_started_ = true;
}

}
}