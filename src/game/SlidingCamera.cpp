#include <game/SlidingCamera.hpp>

namespace game {

using namespace monkeysworld;

SlidingCamera::SlidingCamera(engine::Context* ctx) : GameCamera(ctx) {
  start_point_ = end_point_ = glm::vec3(0);
  start_rotation_ = end_rotation_ = glm::vec3(0);
  slide_dur_ = 1.0f;
  time_ = 0.0f;
  animating_ = false;
}

void SlidingCamera::SetStartPosition(glm::vec3 pos) {
  start_point_ = pos;
}

void SlidingCamera::SetEndPosition(glm::vec3 rot) {
  start_rotation_ = rot;
}

void SlidingCamera::SetEndPosition(glm::vec3 pos) {
  end_point_ = pos;
}

void SlidingCamera::SetEndRotation(glm::vec3 rot) {
  end_rotation_ = rot;
}

void SlidingCamera::SetSlideDuration(float time) {
  slide_dur_ = time;
}

void SlidingCamera::StartAnimation() {
  time_ = 0.0f;
  animating_ = true;
}

void SlidingCamera::StopAnimation() {
  animating_ = false;
}

void SlidingCamera::Update() {
  if (animating_) {
    float f = fade();
    SetPosition(glm::mix(start_point_, end_point_, f));
    SetRotation(glm::mix(start_rotation_, end_rotation_, f));
    time_ += static_cast<float>(GetContext()->GetDeltaTime());
  }
}

float SlidingCamera::fade() {
  float t = time_ / slide_dur_;
  t = std::max(std::min(1.0f, t), 0.0f);
  // 10t^{3} - 15t^{4} + 6t^{5} -- from perlin noise impl :)
  return t * t * t * (t * (t * 6 - 15) + 10);
}

}