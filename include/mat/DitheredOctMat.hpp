#ifndef DITHERED_OCT_MAT_H_
#define DITHERED_OCT_MAT_H_

#include <engine/Context.hpp>
#include <shader/Material.hpp>
#include <shader/ShaderProgram.hpp>
#include <file/CachedFileLoader.hpp>
#include <glm/glm.hpp>

namespace mat {

/**
 *  Material used for our octagonal portal light
 */ 
struct DitheredOctMat : public ::monkeysworld::shader::Material {
  DitheredOctMat(::monkeysworld::engine::Context* ctx);
  void UseMaterial() override;
  // model matrix
  glm::mat4 model_mat;
  
  // view matrix
  glm::mat4 view_mat;

  // height factor -- larger = taller light
  float height_factor;
 private:
  ::monkeysworld::shader::ShaderProgram prog_;
};

}

#endif