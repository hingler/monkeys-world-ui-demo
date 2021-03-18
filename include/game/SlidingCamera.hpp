#ifndef SLIDING_CAMERA_H_
#define SLIDING_CAMERA_H_

#include <critter/GameCamera.hpp>

namespace game {

class SlidingCamera : public ::monkeysworld::critter::GameCamera {
 public:
  SlidingCamera(::monkeysworld::engine::Context* ctx);

  // sets the start position for the camera.
  void SetStartPosition(glm::vec3 pos);
  // sets the start rotation for the camera.
  void SetStartRotation(glm::vec3 rot);

  // sets the end position for the camera.
  void SetEndPosition(glm::vec3 pos);
  // sets the end rotation for the camera.
  void SetEndRotation(glm::vec3 rot);

  // sets the duration of the slide
  void SetSlideDuration(float time);

  // starts the animation from the beginning
  void StartAnimation();
  // stops the animation where it stands
  void StopAnimation();

  // updates position of camera
  void Update() override;
 private:
  /**
   *  @returns [0 - 1] representing the mix var between start and end.
   */ 
  float fade();

  // start coordinates
  glm::vec3 start_point_;
  glm::vec3 start_rotation_;

  // end coordinates
  glm::vec3 end_point_;
  glm::vec3 end_rotation_;

  // length of animation
  float slide_dur_;

  // current animation time
  float time_;

  // true if animating, false otherwise.
  bool animating_;
};

}

#endif