#include <game/OctTube.hpp>

namespace game {
using ::monkeysworld::engine::Context;
using ::monkeysworld::engine::RenderContext;
using ::monkeysworld::file::CachedFileLoader;

OctTube::OctTube(Context* ctx, std::shared_ptr<CachedFileLoader> loader) : Model(ctx), tube_mat_(loader) {
  auto mesh = loader->LoadModel("resources/octtube.obj");
  SetMesh(mesh);
  rot_ = 0.0f;
}

void OctTube::Update() {
  rot_ += static_cast<float>(GetContext()->GetDeltaTime() * 0.3);
  SetRotation(glm::vec3(0.0f, rot_, 0.0f));
}

void OctTube::RenderMaterial(const RenderContext& rc) {
  PrepareAttributes();
  tube_mat_.height_factor = 1.1f;
  tube_mat_.view_mat = rc.GetActiveCamera().vp_matrix;
  tube_mat_.model_mat = GetTransformationMatrix();
  tube_mat_.UseMaterial();
  Draw();
}

}