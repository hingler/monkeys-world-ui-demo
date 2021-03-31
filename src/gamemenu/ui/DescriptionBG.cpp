#include <gamemenu/ui/DescriptionBG.hpp>
#include <shader/color/Gradient.hpp>

namespace gamemenu {
namespace ui {

using ::monkeysworld::shader::color::Gradient;

DescriptionBG::DescriptionBG(::monkeysworld::engine::Context* ctx) : UIObject(ctx), mat_(ctx) {}

void DescriptionBG::Update() {
  glm::vec2 dims = GetContext()->GetFramebufferSize();
  dims.x *= (1.0f / 2.618f);
  SetDimensions(dims);
}

void DescriptionBG::DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) {
  Gradient grad;
  grad.start_point = glm::vec2(0, GetDimensions().y / 2.0f);
  grad.end_point = grad.start_point + glm::vec2(GetDimensions().x * 0.95, 0);
  grad.AddStop(glm::vec4(glm::vec3(1.0f), 0.0f), 0.0f);
  grad.AddStop(glm::vec4(1.0f, 0.76f, 0.0f, 1.0f), 0.6f);
  grad.AddStop(glm::vec4(glm::vec3(1.0f), 1.0f), 1.0f);
  mat_.SetColor(grad);
  mat_.UseMaterial();
  DrawFullscreenQuad();
}

}
}