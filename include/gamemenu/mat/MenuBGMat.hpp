#ifndef MENU_BG_MAT_H_
#define MENU_BG_MAT_H_

#include <shader/Material.hpp>
#include <engine/Context.hpp>

#include <shader/ShaderProgram.hpp>

namespace gamemenu {
namespace mat {

struct MenuBGMat : public ::monkeysworld::shader::Material {
  MenuBGMat(::monkeysworld::engine::Context* ctx);
  void UseMaterial();

  // current time offset
  float time;

  // angle of grid
  float theta;

  // width of grid [0.0, 1.0]
  float grid_width;

  // scale of displacement of grid
  float disp_scale;

  // number of intersections per screenspace
  float grid_scale;

  // factors of noise
  float noise_facs;
 private:
  ::monkeysworld::shader::ShaderProgram prog_;
};

}
}

#endif