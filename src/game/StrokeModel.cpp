#include <game/StrokeModel.hpp>

namespace game {

StrokeModel::StrokeModel(::monkeysworld::engine::Context* ctx) : GameObject(ctx), mat_(ctx), surf_(ctx) {}

void StrokeModel::RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) {
  // disable depth writing to ensure model renders on top
  glDepthMask(GL_FALSE);
  auto tf_matrix = GetTransformationMatrix();
  mat_.model_matrix = tf_matrix;
  mat_.vp_matrix = rc.GetActiveCamera().vp_matrix;
  mat_.UseMaterial();
  mesh_stroke_->PointToVertexAttribs();
  glDrawElements(GL_TRIANGLES, mesh_stroke_->GetIndexCount(), GL_UNSIGNED_INT, (void*)0);
  glDepthMask(GL_TRUE);

  surf_.SetModelTransforms(tf_matrix);
  surf_.SetCameraTransforms(rc.GetActiveCamera().vp_matrix);
  surf_.SetSpotlights(rc.GetSpotlights());
  surf_.SetSurfaceColor(glm::vec4(glm::vec3(0.7), 1.0));
  surf_.UseMaterial();
  mesh_draw_->PointToVertexAttribs();
  glDrawElements(GL_TRIANGLES, mesh_draw_->GetIndexCount(), GL_UNSIGNED_INT, (void*)0);
}

void StrokeModel::SetStrokeModel(std::shared_ptr<const ::monkeysworld::model::Mesh<>>& mesh) {
  mesh_stroke_ = mesh;
}

void StrokeModel::SetPrimaryModel(std::shared_ptr<const ::monkeysworld::model::Mesh<>>& mesh) {
  mesh_draw_ = mesh;
}

void StrokeModel::SetStrokeWidth(float stroke) {
  mat_.stroke_width = stroke;
}

void StrokeModel::SetColor(glm::vec4 col) {
  mat_.color = col;
}

}