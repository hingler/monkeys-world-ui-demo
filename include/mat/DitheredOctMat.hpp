#ifndef DITHERED_OCT_MAT_H_
#define DITHERED_OCT_MAT_H_

#include <shader/Material.hpp>
#include <glm/glm.hpp>

namespace scene {
namespace mat {

/**
 *  Material used for our octagonal portal light
 */ 
struct DitheredOctMat : public ::monkeysworld::shader::Material {
  void UseMaterial() override;

  /**
   *  Modifies how the shader treats the height of the geometry.
   */ 
  void SetHeightFactor(float height);

  /**
   *  Sets transform matrix for camera.
   */ 
  void SetCameraTransforms(const glm::mat4& view_proj);

  /**
   *  Sets transform matrix for model.
   */ 
  void SetModelTransforms(const glm::mat4 model);
 private:
  glm::mat4 view_mat_;
  glm::mat4 model_mat_;
  float height_fac_;
};

}
}

#endif