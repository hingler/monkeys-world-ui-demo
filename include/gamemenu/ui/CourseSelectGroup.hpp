#ifndef COURSE_SELECT_GROUP_H_
#define COURSE_SELECT_GROUP_H_

#include <critter/ui/UIGroup.hpp>
#include <critter/ui/UIImage.hpp>
#include <shader/Texture.hpp>
#include <input/KeyListener.hpp>

namespace gamemenu {
namespace ui {

/**
 *  Contains our courses.
 */ 
class CourseSelectGroup : public ::monkeysworld::critter::ui::UIObject {
 public:
  /**
   *  Creates a new CourseSelectGroup.
   */ 
  CourseSelectGroup(::monkeysworld::engine::Context* ctx);

  void Create() override;
  void Update() override;
  void Layout(glm::vec2 size) override;
  bool OnClick(const ::monkeysworld::input::MouseEvent& e) override;
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
  void DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) override;

  /**
   *  Handles the action of hiding the non-selected courses
   *  @param time - time passed in transition.
   *  @returns true if the transition is complete, false otherwise.
   */ 
  bool HideElements(float time);

 private:
  float TransitionFunction(float t);
  // positions the "active" cursor
  glm::vec2 GetSelectorCenter(float pos);

  // calculate dimensions of our input images
  glm::vec2 GetImageDims(const glm::vec2& size);
  // nested group used to achieve behavior
  std::shared_ptr<::monkeysworld::critter::ui::UIGroup> group_;
  std::vector<std::shared_ptr<::monkeysworld::critter::ui::UIImage>> images_;
  std::shared_ptr<const ::monkeysworld::shader::Texture> selector_;

  // stores selector center
  glm::vec2 selector_pos_;

  float local_delta_;

  bool faded;
  bool transition_begin_;
  float target_offset_;

  float select_current_;
  int select_target_;

  ::monkeysworld::input::KeyListener key_l_;
  ::monkeysworld::input::KeyListener key_r_;
  ::monkeysworld::input::KeyListener key_enter_;

  static const float ASPECT_RATIO;
  static const float TRANSITION_START;
  static const float TRANSITION_OUT_DURATION;

  static const int EXCURSION_HEIGHT = 810;
  static const int EXCURSION_WIDTH = 720;

  static const int SELECTOR_HEIGHT = 900;
  static const int SELECTOR_WIDTH = 810;


  static const float EPS;
  static const float SMOOTH_FACTOR;
  static const float MARGIN_SIZE;
};

}
}

#endif