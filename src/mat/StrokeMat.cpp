#include <mat/StrokeMat.hpp>
#include <shader/ShaderProgramBuilder.hpp>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace mat {

StrokeMat::StrokeMat(::monkeysworld::engine::Context* ctx) {
  prog_ = ::monkeysworld::shader::ShaderProgramBuilder(ctx->GetCachedFileLoader())
            .WithVertexShader("resources/mat/StrokeMat.vert")
            .WithFragmentShader("resources/mat/StrokeMat.frag")
            .Build();
}

void StrokeMat::UseMaterial() {
  glUseProgram(prog_.GetProgramDescriptor());
  glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model_matrix));
  glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(vp_matrix));
  glUniform1f(2, stroke_width);
  glUniform4fv(3, 1, glm::value_ptr(color));
}

}