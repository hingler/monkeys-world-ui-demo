#include <gamemenu/ui/StageBanner.hpp>

namespace gamemenu {
namespace ui {

namespace {
  const float EPS = 0.00001f;
  const float SMOOTH_FACTOR = 0.003f;
}

using namespace ::monkeysworld::critter::ui;
using namespace layout;

StageBanner::StageBanner(::monkeysworld::engine::Context* ctx) : UIObject(ctx) {
  banners_.push_back(std::make_shared<UIImage>(ctx, "resources/gamemenu/img/banners/stage_banner_A.png"));
  banners_.push_back(std::make_shared<UIImage>(ctx, "resources/gamemenu/img/banners/stage_banner_B.png"));

  group_ = std::make_shared<UIGroup>(ctx);
  group_->SetPosition(glm::vec2(0));
  auto margins = banners_[0]->GetLayoutParams();

  margins.left.anchor_id = margins.right.anchor_id = group_->GetId();
  margins.left.margin = margins.right.margin = 0;
  margins.left.anchor_face = Face::LEFT;
  margins.right.anchor_face = Face::RIGHT;

  for (auto banner : banners_) {
    banner->SetLayoutParams(margins);
    group_->AddChild(banner);
  }

  transition_current_ = 0;
  transition_target_ = 0;
  // group ought to maintain aspect ratio
}

void StageBanner::Update() {
  float cur_offset = transition_current_;
  if (!(std::abs(cur_offset - transition_target_) < EPS)) {
    float t = static_cast<float>(1 - std::pow(SMOOTH_FACTOR, GetContext()->GetDeltaTime()));
    transition_current_ = (1 - t) * cur_offset + (t * transition_target_);
    Invalidate();
  }

  glm::vec2 dims_group = GetDimensions();
  // ensure that we maintain aspect ratio
  dims_group.y = std::floor(dims_group.x * (static_cast<float>(BANNER_HEIGHT) / BANNER_WIDTH));
  SetDimensions(dims_group);
}

void StageBanner::Layout(glm::vec2 size) {
  glm::vec2 dims_group = size;
  BOOST_LOG_TRIVIAL(trace) << "dims: " << size.x << ", " << size.y;
  BOOST_LOG_TRIVIAL(trace) << "dims: " << dims_group.x << ", " << dims_group.y;
  BOOST_LOG_TRIVIAL(trace) << "position: " << GetPosition().x << ", " << GetPosition().y;
  dims_group.y = dims_group.x * (static_cast<float>(BANNER_HEIGHT) / BANNER_WIDTH);
  // ensure that group maintains aspect ratio
  group_->SetDimensions(dims_group);
  group_->Invalidate();
  float t_fract = (transition_current_ - std::floor(transition_current_));
  for (int i = 0; i < banners_.size(); i++) {
    auto child = banners_[i];
    if (i == transition_target_) {
      // 0 if 1, offscreen if 0
      float pos_y = 1.3f * (-dims_group.y * (t_fract));
      child->SetPosition(glm::vec2(0, pos_y));
    } else if (i == transition_target_ - 1) {
      // 0 if 0, offscreen if 1
      float pos_y = 1.3f * (-dims_group.y * (1 - t_fract));
      child->SetPosition(glm::vec2(0, pos_y));
    } else {
      // keep child out of visibility
      child->SetPosition(glm::vec2(0, -1.3f * dims_group.y));
    }

    child->SetDimensions(glm::vec2(dims_group.x, dims_group.y));

    BOOST_LOG_TRIVIAL(trace) << "child " << i << ": " << child->GetPosition().x << ", " << child->GetPosition().y;
    BOOST_LOG_TRIVIAL(trace) << "dims: " << child->GetDimensions().x << ", " << child->GetDimensions().y;
  }

  group_->PreLayout();
}

void StageBanner::RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) {
  // if layout is called, group is invalidated
  if (!IsValid()) {
    group_->Invalidate();
    group_->RenderMaterial(rc);
  }

  UIObject::RenderMaterial(rc); 
}

void StageBanner::DrawUI(glm::vec2 a, glm::vec2 b, ::monkeysworld::shader::Canvas canvas) {
  group_->DrawUI(a, b, canvas);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, group_->GetFramebuffer());
  auto dims = static_cast<glm::ivec2>(GetDimensions());
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GetFramebuffer());
  auto group_dims = static_cast<glm::ivec2>(group_->GetDimensions());
  BOOST_LOG_TRIVIAL(trace) << group_dims.x << ", " << group_dims.y;
  glBlitFramebuffer(0, 0, group_dims.x, group_dims.y, 0, 0, dims.x, dims.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_FRAMEBUFFER, GetFramebuffer());
}

void StageBanner::Advance() {
  transition_target_++;
}

}
}