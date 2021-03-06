#ifndef COURSE_SELECT_GROUP_H_
#define COURSE_SELECT_GROUP_H_

#include <critter/ui/UIGroup.hpp>

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

  void Update() override;
  void Layout(glm::vec2 size) override;
  bool OnClick(const ::monkeysworld::input::MouseEvent& e) override;
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
  void DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) override;

 private:
  float TransitionFunction(float t);
  // nested group used to achieve behavior
  std::shared_ptr<::monkeysworld::critter::ui::UIGroup> group_;
  float local_delta_;
  static const float ASPECT_RATIO;
  static const float TRANSITION_START;
};

}
}

#endif