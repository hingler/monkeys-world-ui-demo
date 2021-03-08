#include <gamemenu/ui/CourseSelectGroup.hpp>

#include <critter/ui/UIImage.hpp>

#include <engine/Scene.hpp>

#include <gamemenu/GameMenu.hpp>

#include <input/KeyListener.hpp>

namespace gamemenu {
namespace ui {

using ::monkeysworld::engine::Context;
using ::monkeysworld::critter::ui::UIImage;
using ::monkeysworld::critter::ui::UIGroup;
using ::monkeysworld::audio::AudioFiletype;
using namespace ::monkeysworld::critter::ui::layout;

using ::monkeysworld::input::KeyListener;

const float CourseSelectGroup::ASPECT_RATIO = 0.9f;
const float CourseSelectGroup::TRANSITION_START = 1.8f;

const float CourseSelectGroup::EPS = 0.00001f;
const float CourseSelectGroup::SMOOTH_FACTOR = 0.0005f;

CourseSelectGroup::CourseSelectGroup(Context* ctx) : UIObject(ctx), local_delta_(0.0f) {
  faded = false;
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
  margins.right.margin = 64.0f;
  margins.right.anchor_face = Face::LEFT;

  image_a->SetLayoutParams(margins);
  image_a->SetDimensions(glm::vec2(360, 400));

  image_a->z_index = -10;

  std::shared_ptr<UIImage> image_c = std::make_shared<UIImage>(ctx, "resources/gamemenu/img/excursionC.png");
  margins.left.anchor_id = image_b->GetId();
  margins.left.margin = 64.0f;
  margins.left.anchor_face = Face::RIGHT;

  margins.right.anchor_id = 0;
  margins.right.margin = 0.0f;

  image_c->SetLayoutParams(margins);
  image_c->SetDimensions(glm::vec2(360, 400));

  image_c->z_index = -10;

  images_.push_back(image_a);
  images_.push_back(image_b);
  images_.push_back(image_c);

  selector_ = GetContext()->GetCachedFileLoader()->LoadTexture("resources/gamemenu/img/selector_box.png");

  group_->AddChild(image_a);
  group_->AddChild(image_b);
  group_->AddChild(image_c);

  SetPosition(glm::vec2(0, 0));
  select_target_ = 0;
  select_current_ = 0.0f;
}

void CourseSelectGroup::Create() {
  auto margins = GetLayoutParams();
  margins.bottom.anchor_id = 0;
  SetLayoutParams(margins);

  auto banner = std::dynamic_pointer_cast<UIObject>(GetContext()->GetScene()->GetWindow()->GetChild(GameMenu::BANNER_ID));
  auto win_dims = GetContext()->GetScene()->GetWindow()->GetDimensions();
  SetDimensions(glm::vec2(win_dims.x, win_dims.y - banner->GetDimensions().y));
}

void CourseSelectGroup::Update() {
  local_delta_ += static_cast<float>(GetContext()->GetDeltaTime());

  auto banner = std::dynamic_pointer_cast<UIObject>(GetContext()->GetScene()->GetWindow()->GetChild(GameMenu::BANNER_ID));
  auto win_dims = GetContext()->GetScene()->GetWindow()->GetDimensions();
  auto new_dims = glm::vec2(win_dims.x, win_dims.y - banner->GetDimensions().y);
  SetDimensions(new_dims);
  float fade = TransitionFunction(local_delta_);
  // update select
  // once this state is reached we're good
  
  if (!(std::abs(select_current_ - select_target_) < EPS)) {
    float t = static_cast<float>(1 - std::pow(SMOOTH_FACTOR, GetContext()->GetDeltaTime()));
    select_current_ = (1 - t) * select_current_ + (t * select_target_);
  }

  if (!faded && fade < 0.01) {
    faded = true;
    key_l = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_A, [&] (int, int action, int) {
      if (action == GLFW_PRESS) {
        select_target_ = std::max(select_target_ - 1, 0);
        GetContext()->GetAudioManager()->AddFileToBuffer("resources/tick.ogg", AudioFiletype::OGG);
      }
    });

    key_r = GetContext()->GetEventManager()->CreateKeyListener(GLFW_KEY_D, [&] (int, int action, int) {
      if (action == GLFW_PRESS) {
        select_target_ = std::min(select_target_ + 1, static_cast<int>(images_.size()) - 1);
        GetContext()->GetAudioManager()->AddFileToBuffer("resources/tick.ogg", AudioFiletype::OGG);
      }
    });
  }

  auto margins = GetLayoutParams();
  margins.bottom.anchor_id = 0;
  margins.top.margin = fade * GetDimensions().y * 1.5f;
  SetLayoutParams(margins);
  Invalidate();
}

float CourseSelectGroup::TransitionFunction(float t) {
  float flip_t = 1 - std::max(t - TRANSITION_START, 0.0f);
  if (flip_t < 0.0f) {
    return 0.0;
  } else {
    return flip_t * flip_t * flip_t * flip_t;
  }
}

void CourseSelectGroup::Layout(glm::vec2 size) {
  // calculate size of each icon
  // min of (width / 3.2) and (height * 0.9).
  int width = static_cast<int>(std::floor(std::min((size.x - 128) / 3.2, (size.y * ASPECT_RATIO) * 0.9)));
  int height = static_cast<int>(width / ASPECT_RATIO);
  glm::vec2 image_dims(width, height);
  for (auto child : group_->GetChildren()) {
    std::dynamic_pointer_cast<UIObject>(child)->SetDimensions(image_dims);
  }

  group_->SetDimensions(size);
  group_->PreLayout();

  glm::vec2 selector_center = GetSelectorCenter(select_current_);
  selector_pos_ = selector_center;
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
  glm::vec2 test = GetSelectorCenter(select_current_);
  float scale = (images_[0]->GetDimensions().x / EXCURSION_WIDTH);
  glm::vec2 selector_dims(SELECTOR_WIDTH * scale, SELECTOR_HEIGHT * scale);
  selector_dims *= ((1 + sin(local_delta_ * 4.0f)) / 35.0f) + 1.0f;
  canvas.DrawImage(selector_, static_cast<glm::vec2>(selector_pos_) - (selector_dims / 2.0f), selector_dims);
}

glm::vec2 CourseSelectGroup::GetSelectorCenter(float pos) {
  glm::vec2 dims = GetImageDims(GetDimensions());
  glm::vec2 res = glm::vec2(0);
  if (pos <= 0) {
    res = images_[0]->GetPosition() + (images_[0]->GetDimensions() / 2.0f);
  } else if (pos >= (images_.size() - 1)) {
    auto image = images_[images_.size() - 1];
    res = image->GetPosition() + (image->GetDimensions() / 2.0f);
  } else {
    auto i_base = images_[static_cast<int>(std::floor(pos))];
    auto i_ceil = images_[static_cast<int>(std::ceil(pos))];
    float t_fract = pos - std::floor(pos);

    // fall in between base and ceil
    res = t_fract * (i_ceil->GetPosition() + (i_ceil->GetDimensions() / 2.0f));
    res += (1 - t_fract) * (i_base->GetPosition() + (i_base->GetDimensions() / 2.0f));
  }

  return res;
}

glm::vec2 CourseSelectGroup::GetImageDims(const glm::vec2& size) {
  int width = static_cast<int>(std::floor(std::min((size.x - 128) / 3.2, (size.y * ASPECT_RATIO) * 0.9)));
  int height = static_cast<int>(width / ASPECT_RATIO);
  return glm::vec2(width, height);
}

}
}