#include <mat/DitheredOctMat.hpp>
#include <shader/ShaderProgramBuilder.hpp>

#include <glm/gtc/type_ptr.hpp>

using namespace monkeysworld;

using engine::Context;
using shader::ShaderProgramBuilder;
using file::CachedFileLoader;

namespace mat {

DitheredOctMat::DitheredOctMat(std::shared_ptr<CachedFileLoader> loader) : view_mat(1.0), model_mat(1.0), height_factor(1.0) {
  prog_ = ShaderProgramBuilder(loader)
            .WithVertexShader("resources/mat/DitheredOctMat.vert")
            .WithFragmentShader("resources/mat/DitheredOctMat.frag")
            .Build();
}

void DitheredOctMat::UseMaterial() {
  glUseProgram(prog_.GetProgramDescriptor());
  glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model_mat));
  glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(view_mat));
  glUniform1f(2, height_factor);
}

}