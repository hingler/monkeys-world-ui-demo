#include <gamemenu/ui/SlidingBlindsTransition.hpp>

namespace gamemenu {
namespace ui {

using ::monkeysworld::shader::Texture;
using ::monkeysworld::shader::Canvas;

SlidingBlindsTransition::SlidingBlindsTransition(::monkeysworld::engine::Context* ctx) 
  : UIObject(ctx), mat_(ctx) {
  mat_.segment_count = 15;
  mat_.segment_offset = 0.06f;
  mat_.time = -0.3f;
}


void SlidingBlindsTransition::Create() {
  tex_ = std::make_shared<Texture>(GetContext(), GetContext()->GetLastFrame());
  mat_.texture = tex_->GetTextureDescriptor();
  mat_.time -= static_cast<float>(GetContext()->GetDeltaTime());
}

void SlidingBlindsTransition::Update() {
  mat_.time += static_cast<float>(GetContext()->GetDeltaTime());
  Invalidate();
}

void SlidingBlindsTransition::DrawUI(glm::vec2 minXY, glm::vec2 maxXY, Canvas canvas) {
  mat_.UseMaterial();
  DrawFullscreenQuad();
}

}
}