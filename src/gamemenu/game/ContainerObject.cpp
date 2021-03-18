#include <gamemenu/game/ContainerObject.hpp>

namespace gamemenu {
namespace game {

using ::monkeysworld::engine::Context;
using ::monkeysworld::engine::RenderContext;

ContainerObject::ContainerObject(Context* ctx) : Model(ctx),
                                                 mat_(ctx) {
  auto mesh = GetContext()->GetCachedFileLoader()->LoadModel("resources/gamemenu/container.obj");
  SetMesh(mesh);
}

void ContainerObject::RenderMaterial(const RenderContext& rc) {
  mat_.SetSurfaceColor(glm::vec4(glm::vec3(0.8f), 1.0f));
  mat_.SetSpotlights(rc.GetSpotlights());
  mat_.SetModelTransforms(GetTransformationMatrix());
  mat_.SetCameraTransforms(rc.GetActiveCamera().vp_matrix);
  mat_.UseMaterial();
  PrepareAttributes();
  Draw();
}

}
}