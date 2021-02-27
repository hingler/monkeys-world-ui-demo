#ifndef SLIDING_BLINDS_TRANSITION_H_
#define SLIDING_BLINDS_TRANSITION_H_

#include <engine/Context.hpp>
#include <critter/ui/UIObject.hpp>

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
   *  Stores the texture which will be displayed before this transition begins. (A)
   *  @param frame - a texture descriptor representing the initial image.
   */ 
  void SetTextureA(GLuint frame);
 private:
  BlindsTransitionMat mat_;
};

}
}

#endif