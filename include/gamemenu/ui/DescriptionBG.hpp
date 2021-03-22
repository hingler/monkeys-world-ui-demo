#ifndef DESCRIPTION_BG_H_
#define DESCRIPTION_BG_H_

#include <critter/ui/UIObject.hpp>
#include <shader/materials/FillMaterial.hpp>

namespace gamemenu {
namespace ui {

/**
 *  Background for description text on char select screen.
 */ 
class DescriptionBG : public ::monkeysworld::critter::ui::UIObject {
 public:
  DescriptionBG(::monkeysworld::engine::Context* ctx);
  void Update() override;
  void DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) override;
 private:
  ::monkeysworld::shader::materials::FillMaterial mat_;
};

}
}

#endif