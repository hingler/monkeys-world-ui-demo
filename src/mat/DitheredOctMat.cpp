#include <mat/DitheredOctMat.hpp>
#include <shader/ShaderProgramBuilder.hpp>

#include <glm/gtc/type_ptr.hpp>

using namespace monkeysworld;

using engine::Context;
using shader::ShaderProgramBuilder;
using file::CachedFileLoader;

namespace mat {

DitheredOctMat::DitheredOctMat(::monkeysworld::engine::Context* ctx) : view_mat(1.0), model_mat(1.0), height_factor(1.0) {
  auto exec_prog = [&] {
    prog_ = ShaderProgramBuilder(ctx->GetCachedFileLoader())
              .WithVertexShader("resources/mat/DitheredOctMat.vert")
              .WithFragmentShader("resources/mat/DitheredOctMat.frag")
              .Build();
  };

  auto f = ctx->GetExecutor()->ScheduleOnMainThread(exec_prog);
  f.wait();
}

void DitheredOctMat::UseMaterial() {
  glUseProgram(prog_.GetProgramDescriptor());
  glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model_mat));
  glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(view_mat));
  glUniform1f(2, height_factor);
}

}