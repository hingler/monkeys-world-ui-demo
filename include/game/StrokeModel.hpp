#ifndef STROKE_MODEL_H_
#define STROKE_MODEL_H_

#include <mat/StrokeMat.hpp>
#include <shader/materials/MatteMaterial.hpp>
#include <critter/GameObject.hpp>

#include <model/Mesh.hpp>

namespace game {
class StrokeModel : public ::monkeysworld::critter::GameObject {
 public:
  /**
   *  Creates a new StrokeModel.
   */ 
  StrokeModel(::monkeysworld::engine::Context* ctx);
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;

  /**
   *  Sets the model used to draw the object's stroke onto the screen.
   *  @param mesh - the mesh for this.
   */ 
  void SetStrokeModel(std::shared_ptr<const ::monkeysworld::model::Mesh<>>& mesh);
  /**
   *  Sets the model used to draw the object itself onto the screen.
   *  @param mesh - the mesh for this.
   */ 
  void SetPrimaryModel(std::shared_ptr<const ::monkeysworld::model::Mesh<>>& mesh);

  /**
   *  Sets the width of the stroke drawn onto the screen.
   *  1.0f = 1/64th of a unit in GL space.
   */ 
  void SetStrokeWidth(float stroke);

  /**
   *  Sets the color of the stroke.
   *  @param col - the new desired color.
   */ 
  void SetColor(glm::vec4 col);
 private:
  mat::StrokeMat mat_;
  ::monkeysworld::shader::materials::MatteMaterial surf_;

  std::shared_ptr<const ::monkeysworld::model::Mesh<>> mesh_stroke_;
  std::shared_ptr<const ::monkeysworld::model::Mesh<>> mesh_draw_;
};
}

#endif