#ifndef SLIDING_BLINDS_TRANSITION_H_
#define SLIDING_BLINDS_TRANSITION_H_

#include <engine/Context.hpp>
#include <critter/ui/UIObject.hpp>
#include <shader/Texture.hpp>

#include <gamemenu/mat/BlindsTransitionMat.hpp>
#include <glad/glad.h>

namespace gamemenu {
namespace ui {

/**
 *  A class which is primarily designed to transition from one scene to another.
 */ 
class SlidingBlindsTransition : public ::monkeysworld::critter::ui::UIObject {
 public:
  /**
   *  Construct a new SlidingBlindsTransition object.
   */ 
  SlidingBlindsTransition(::monkeysworld::engine::Context* ctx);

  /**
   *  Override for Update.
   */ 
  void Update() override;

  /**
   *  Override for DrawUI.
   */ 
  void DrawUI(glm::vec2 minXY, glm::vec2 maxXY, ::monkeysworld::shader::Canvas canvas);

  /**
   *  Stores the texture which will be displayed before this transition begins. (A)
   *  @param t - a texture object representing the initial image.
   */ 
  void SetTextureA(std::shared_ptr<::monkeysworld::shader::Texture> t);
 private:
  mat::BlindsTransitionMat mat_;
  std::shared_ptr<::monkeysworld::shader::Texture> tex_;
};

}
}

#endif