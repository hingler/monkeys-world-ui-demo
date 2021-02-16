#include <ui/LerpMenu.hpp>

namespace ui {

using ::monkeysworld::engine::Context;

LerpMenu::LerpMenu(Context* ctx, const std::vector<std::string>& text, const std::string& font_path)
  : HorizontalMenuGroup(ctx, text, font_path) {
  lerp_target_ = 0;
}

void LerpMenu::Create() {
  auto lambda_l = [&] (int, int, int) {
    if (lerp_target_ > 0) {
      lerp_target_--;
    }
  };

  auto lambda_r = [&] (int, int, int) {
    if (lerp_target_ < GetTextItems().size() - 1) {
      lerp_target_++;
    }
  };

  listener_l_ = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_A, lambda_l);
  listener_r_ = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_D, lambda_r);
}

void LerpMenu::Update() {
  double delta = GetContext()->GetDeltaTime();
  float cur_offset = GetMenuOffset();
  float t = static_cast<float>(1 - std::pow(SMOOTH_FACTOR, delta));
  SetMenuOffset((1 - t) * cur_offset + t * lerp_target_);
  
}

}