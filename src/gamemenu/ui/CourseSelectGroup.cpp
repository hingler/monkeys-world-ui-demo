#include <gamemenu/ui/CourseSelectGroup.hpp>

#include <critter/ui/UIImage.hpp>



namespace gamemenu {
namespace ui {

using ::monkeysworld::engine::Context;
using ::monkeysworld::critter::ui::UIImage;
using ::monkeysworld::critter::ui::UIGroup;
using namespace ::monkeysworld::critter::ui::layout;

const float CourseSelectGroup::ASPECT_RATIO = 0.9f;

CourseSelectGroup::CourseSelectGroup(Context* ctx) : UIObject(ctx) {
  group_ = std::make_shared<UIGroup>(ctx);
  std::shared_ptr<UIImage> image_b = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionB.png");
  auto margins = image_b->GetLayoutParams();

  margins.left.anchor_id = margins.right.anchor_id = margins.top.anchor_id = margins.bottom.anchor_id = group_->GetId();
  margins.left.margin = margins.right.margin = margins.top.margin = margins.bottom.margin = MarginType::AUTO;
  margins.top.anchor_face = Face::TOP;
  margins.bottom.anchor_face = Face::BOTTOM;
  margins.left.anchor_face = Face::LEFT;
  margins.right.anchor_face = Face::RIGHT;

  image_b->z_index = -10;

  image_b->SetLayoutParams(margins);
  image_b->SetDimensions(glm::vec2(360, 400));

  std::shared_ptr<UIImage> image_a = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionA.png");
  margins.left.anchor_id = 0;
  margins.left.margin = 0.0f;

  margins.right.anchor_id = image_b->GetId();
  margins.right.margin = 16.0f;
  margins.right.anchor_face = Face::LEFT;

  image_a->SetLayoutParams(margins);
  image_a->SetDimensions(glm::vec2(360, 400));

  image_a->z_index = -10;

  std::shared_ptr<UIImage> image_c = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionC.png");
  margins.left.anchor_id = image_b->GetId();
  margins.left.margin = 16.0f;
  margins.left.anchor_face = Face::RIGHT;

  margins.right.anchor_id = 0;
  margins.right.margin = 0.0f;

  image_c->SetLayoutParams(margins);
  image_c->SetDimensions(glm::vec2(360, 400));

  image_c->z_index = -10;

  group_->AddChild(image_a);
  group_->AddChild(image_b);
  group_->AddChild(image_c);
}

void CourseSelectGroup::Layout(glm::vec2 size) {
  // calculate size of each icon
  // min of (width / 3.2) and (height * 0.9).
  int width = static_cast<int>(std::floor(std::min((size.x - 32) / 3.2, (size.y * ASPECT_RATIO) * 0.9)));
  int height = static_cast<int>(width / ASPECT_RATIO);
  glm::vec2 image_dims(width, height);
  for (auto child : group_->GetChildren()) {
    std::dynamic_pointer_cast<UIObject>(child)->SetDimensions(image_dims);
  }

  BOOST_LOG_TRIVIAL(trace) << "hello";
  group_->SetDimensions(size);
  group_->PreLayout();
}

bool CourseSelectGroup::OnClick(const ::monkeysworld::input::MouseEvent& e) {
  // extremely weirdchamp
  return group_->HandleClickEvent(e);
}

void CourseSelectGroup::RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) {
  if (!IsValid()) {
    group_->Invalidate();
    group_->RenderMaterial(rc);
  }

  UIObject::RenderMaterial(rc);
}

void CourseSelectGroup::DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, group_->GetFramebuffer());
  auto dims = static_cast<glm::ivec2>(GetDimensions());
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GetFramebuffer());
  glBlitFramebuffer(0, 0, dims.x, dims.y, 0, 0, dims.x, dims.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_FRAMEBUFFER, GetFramebuffer());
}

}
}