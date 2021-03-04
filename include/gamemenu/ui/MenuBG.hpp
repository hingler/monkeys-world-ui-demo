#ifndef MENU_BG_H_
#define MENU_BG_H_

#include <critter/ui/UIObject.hpp>
#include <gamemenu/mat/MenuBGMat.hpp>

#include <shader/Texture.hpp>

namespace gamemenu {
namespace ui {

class MenuBG : public ::monkeysworld::critter::ui::UIObject {
 public:
  /**
   *  Creates a new MenuBG.
   */ 
  MenuBG(::monkeysworld::engine::Context* ctx);

  void Create() override;

  /**
   *  Update func.
   */ 
  void Update() override;

  void DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) override;

 private:
  mat::MenuBGMat mat_;
  std::shared_ptr<const ::monkeysworld::shader::Texture> tex_;

};

}
}

#endif