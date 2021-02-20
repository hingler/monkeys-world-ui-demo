#include <ui/LerpMenu.hpp>

namespace ui {

using ::monkeysworld::engine::Context;
using ::monkeysworld::audio::AudioFiletype;

LerpMenu::LerpMenu(Context* ctx, const std::vector<std::string>& text, const std::string& font_path)
  : HorizontalMenuGroup(ctx, text, font_path) {
  lerp_target_ = 0;
  SetMenuOffset(0.00001f);
  confirmed_ = false;
  confirmed_timer_ = 0.0;
}

void LerpMenu::Create() {
  auto lambda_l = [&] (int, int action, int) {
    if (action == GLFW_PRESS && lerp_target_ > 0) {
      lerp_target_--;
      GetContext()->GetAudioManager()->AddFileToBuffer("resources/tick.ogg", AudioFiletype::OGG);
    }
  };

  auto lambda_r = [&] (int, int action, int) {
    if (action == GLFW_PRESS && lerp_target_ < GetTextItems().size() - 1) {
      lerp_target_++;
      GetContext()->GetAudioManager()->AddFileToBuffer("resources/tick.ogg", AudioFiletype::OGG);
    }
  };

  auto lambda_enter = [&] (int, int action, int) {
    if (action == GLFW_PRESS) {
      // this is our target
      auto event_mgr = GetContext()->GetEventManager();
      event_mgr->RemoveKeyListener(listener_r_);
      event_mgr->RemoveKeyListener(listener_l_);
      event_mgr->RemoveKeyListener(listener_enter_);
      confirmed_ = true;
      GetContext()->GetAudioManager()->AddFileToBuffer("resources/click.ogg", AudioFiletype::OGG);
    }
  };

  listener_l_ = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_A, lambda_l);
  listener_r_ = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_D, lambda_r);
  listener_enter_ = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_ENTER, lambda_enter);
}

void LerpMenu::Update() {
  double delta = GetContext()->GetDeltaTime();
  float cur_offset = GetMenuOffset();
  glm::ivec2 win_dims;
  GetContext()->GetFramebufferSize(&win_dims.x, &win_dims.y);
  glm::vec2 dims = GetDimensions();
  SetPosition(glm::vec2(win_dims.x / 2 - dims.x / 2, win_dims.y - dims.y * 1.5));
  if (std::abs(lerp_target_ - cur_offset) < LERP_EPS) {
    SetMenuOffset(static_cast<float>(lerp_target_));
  } else {
    float t = static_cast<float>(1 - std::pow(SMOOTH_FACTOR, delta * 1.6));
    SetMenuOffset((1 - t) * cur_offset + (t * lerp_target_));
    Invalidate();
  }

  UpdateConfirmationOpacity();
}

void LerpMenu::UpdateConfirmationOpacity() {
  if (confirmed_) {
    if (confirmed_timer_ < CONFIRMED_DURATION) {
      SetOpacity(static_cast<float>(sin(confirmed_timer_ * 128.0)));
      confirmed_timer_ += GetContext()->GetDeltaTime();
    } else {
      SetOpacity(1.0f);
    }
  }
}

}