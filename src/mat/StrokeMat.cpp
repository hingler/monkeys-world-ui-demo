#include <mat/StrokeMat.hpp>
#include <shader/ShaderProgramBuilder.hpp>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace mat {

StrokeMat::StrokeMat(::monkeysworld::engine::Context* ctx) {
  ctx->GetExecutor()->ScheduleOnMainThread([&] {
    prog_ = ::monkeysworld::shader::ShaderProgramBuilder(ctx->GetCachedFileLoader())
              .WithVertexShader("resources/mat/StrokeMat.vert")
              .WithFragmentShader("resources/mat/StrokeMat.frag")
              .Build();

  }).wait();
}

void StrokeMat::UseMaterial() {
  glUseProgram(prog_.GetProgramDescriptor());
  glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model_matrix));
  glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(vp_matrix));
  glm::mat3 norm_mat = glm::inverseTranspose(glm::mat3(model_matrix));
  glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(norm_mat));
  glUniform1f(3, stroke_width);
  glUniform4fv(4, 1, glm::value_ptr(color));

}

}