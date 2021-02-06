#include <game/OctTube.hpp>

namespace game {
using ::monkeysworld::engine::Context;
using ::monkeysworld::engine::RenderContext;

OctTube::OctTube(Context* ctx) : Model(ctx), tube_mat_(ctx) {
  auto mesh = GetContext()->GetCachedFileLoader()->LoadModel("resources/octtube.obj");
  SetMesh(mesh);
  rot_ = 0.0f;
}

void OctTube::Update() {
  rot_ += static_cast<float>(GetContext()->GetDeltaTime() * 0.3);
  SetRotation(glm::vec3(0.0f, rot_, 0.0f));
}

void OctTube::RenderMaterial(const RenderContext& rc) {
  PrepareAttributes();
  tube_mat_.height_factor = 0.9f;
  tube_mat_.view_mat = rc.GetActiveCamera().vp_matrix;
  tube_mat_.model_mat = GetTransformationMatrix();
  tube_mat_.UseMaterial();
  Draw();
}

}