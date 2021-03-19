#ifndef STROKE_MAT_H_
#define STROKE_MAT_H_

#include <shader/Material.hpp>
#include <engine/Context.hpp>

#include <shader/ShaderProgram.hpp>

#include <glm/glm.hpp>

namespace mat {

struct StrokeMat : public ::monkeysworld::shader::Material {
  StrokeMat(::monkeysworld::engine::Context* ctx);
  void UseMaterial();

  // color of stroke
  glm::vec4 color;

  // width of stroke
  float stroke_width;
 private:
  ::monkeysworld::shader::ShaderProgram prog_;
};

}

#endif