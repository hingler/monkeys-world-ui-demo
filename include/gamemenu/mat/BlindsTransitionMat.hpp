#ifndef BLINDS_TRANSITION_MAT_H_
#define BLINDS_TRANSITION_MAT_H_

#include <engine/Context.hpp>
#include <file/CachedFileLoader.hpp>
#include <shader/Material.hpp>
#include <shader/ShaderProgram.hpp>

#include <memory>

namespace gamemenu {
namespace mat {

struct BlindsTransitionMat : public ::monkeysworld::shader::Material {
  BlindsTransitionMat(::monkeysworld::engine::Context* ctx);
  void UseMaterial() override;

  int segment_count;
  float segment_offset;
  float time;
  GLuint texture;
 private:
  ::monkeysworld::shader::ShaderProgram prog_;
};

}
}

#endif