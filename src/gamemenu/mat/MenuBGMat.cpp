#include <gamemenu/mat/MenuBGMat.hpp>

#include <shader/ShaderProgramBuilder.hpp>

namespace gamemenu {
namespace mat {

using ::monkeysworld::shader::ShaderProgramBuilder;

MenuBGMat::MenuBGMat(::monkeysworld::engine::Context* ctx) {
  
  auto exec_prog = [&] {
    prog_ = ShaderProgramBuilder(ctx->GetCachedFileLoader())
              .WithVertexShader("resources/gamemenu/menubg.vert")
              .WithFragmentShader("resources/gamemenu/menubg.frag")
              .Build();
  };

  auto f = ctx->GetExecutor()->ScheduleOnMainThread(exec_prog);
  f.wait();

  time = 0.0f;
  theta = 0.0f;
  grid_width = 0.03f;
  disp_scale = 1.0f;
  grid_scale = 8.0f;
  noise_facs = 4.0f;
}

void MenuBGMat::UseMaterial() {
  glUseProgram(prog_.GetProgramDescriptor());
  glUniform1f(0, time);
  glUniform1f(1, theta);
  glUniform1f(2, grid_width);
  glUniform1f(3, disp_scale);
  glUniform1f(4, grid_scale);
  glUniform1f(5, noise_facs);
}

}
}