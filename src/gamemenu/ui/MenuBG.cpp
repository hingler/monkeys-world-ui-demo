#include <gamemenu/ui/MenuBG.hpp>

namespace gamemenu {
namespace ui {

MenuBG::MenuBG(::monkeysworld::engine::Context* ctx) : UIObject(ctx), mat_(ctx) {
  mat_.time = 0.0f;
  mat_.theta = 0.42f;
  mat_.grid_scale = 12.0f;
  mat_.grid_width = 0.03f;
  mat_.noise_facs = 4.0f;
}

void MenuBG::Create() {}

void MenuBG::Update() {
  mat_.time += static_cast<float>(GetContext()->GetDeltaTime());
  Invalidate();
}

void MenuBG::DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) {
  mat_.UseMaterial();
  DrawFullscreenQuad();
}

}
}