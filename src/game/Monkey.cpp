#include <game/Monkey.hpp>

namespace game {
using ::monkeysworld::engine::Context;
using ::monkeysworld::engine::RenderContext;
using ::monkeysworld::file::CachedFileLoader;
Monkey::Monkey(Context* ctx, std::shared_ptr<CachedFileLoader> loader) : Model(ctx), mat_(ctx) {
  auto model = loader->LoadModel("resources/moneky.obj");
  SetMesh(model);
}

void Monkey::Update() {
  // nop for now
}

void Monkey::RenderMaterial(const RenderContext& rc) {
  PrepareAttributes();
  mat_.SetSurfaceColor(glm::vec4(glm::vec3(0.8f), 1.0f));
  mat_.SetModelTransforms(GetTransformationMatrix());
  mat_.SetCameraTransforms(rc.GetActiveCamera().vp_matrix);
  mat_.SetSpotlights(rc.GetSpotlights());
  mat_.UseMaterial();
  Draw();
}

}