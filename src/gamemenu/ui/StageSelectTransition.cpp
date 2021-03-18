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
  camera_started_ = false;
}

void StageSelectTransition::Create() {
  auto window = GetContext()->GetScene()->GetWindow();
  stage_select_ = std::dynamic_pointer_cast<CourseSelectGroup>(window->GetChild(GameMenu::SELECT_GROUP_ID));
  banner_ = std::dynamic_pointer_cast<StageBanner>(window->GetChild(GameMenu::BANNER_ID));
  bg_ = std::dynamic_pointer_cast<::monkeysworld::critter::ui::UIObject>(window->GetChild(GameMenu::GRID_BG_ID));
  cam_ = std::dynamic_pointer_cast<::game::SlidingCamera>(GetContext()->GetScene()->GetGameObjectRoot()->GetChild(GameMenu::CAMERA_ID));

  if (!bg_ || !banner_ || !stage_select_ || !cam_) {
    BOOST_LOG_TRIVIAL(error) << "some IDs did not resolve :sade:";
  }
}

void StageSelectTransition::Update() {
  if (timer_started_) {
    local_delta_ += static_cast<float>(GetContext()->GetDeltaTime());

    if (!camera_started_ && local_delta_ > 0.3f) {
      cam_->StartAnimation();
      camera_started_ = true;
    } else if (camera_started_) {
      // start moving the select group off the screen
      glm::vec2 win_dims = GetContext()->GetFramebufferSize();
      stage_select_->SetPosition(glm::vec2(cam_->Fade() * -(win_dims.x * 1.5), stage_select_->GetPosition().y));
      // once fade = 1.0, reset start/end and restart
    }

    if (stage_select_->HideElements(local_delta_) && !banner_swapped_) {
      banner_->Advance();
      banner_swapped_ = true;
    }

    // offset banner

    bg_->SetOpacity(std::max(0.0f, 1.0f - (local_delta_ / 2)));
  }
}

void StageSelectTransition::StartTransition() {
  timer_started_ = true;
}

}
}