#include <game/Monkey.hpp>

namespace game {
using ::monkeysworld::engine::Context;
using ::monkeysworld::engine::RenderContext;
Monkey::Monkey(Context* ctx) : Model(ctx), mat_(ctx) {
  auto model = GetContext()->GetCachedFileLoader()->LoadModel("resources/monkey.obj");
  SetMesh(model);
}

void Monkey::Update() {
  // nop for now
}

void Monkey::RenderMaterial(const RenderContext& rc) {
  PrepareAttributes();
  mat_.SetSurfaceColor(glm::vec4(glm::vec3(0.8), 1.0));
  mat_.SetModelTransforms(GetTransformationMatrix());
  mat_.SetCameraTransforms(rc.GetActiveCamera().vp_matrix);
  mat_.SetSpotlights(rc.GetSpotlights());
  mat_.UseMaterial();
  Draw();
}

}