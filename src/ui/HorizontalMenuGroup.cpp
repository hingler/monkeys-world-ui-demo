#include <ui/HorizontalMenuGroup.hpp>
#include <font/UITextObject.hpp>
#include <font/TextFormat.hpp>

namespace ui {
using ::monkeysworld::engine::Context;
using ::monkeysworld::critter::ui::UIGroup;
using ::monkeysworld::font::UITextObject;
using ::monkeysworld::font::AlignmentH;
using ::monkeysworld::font::AlignmentV;
using ::monkeysworld::engine::RenderContext;
HorizontalMenuGroup::HorizontalMenuGroup(Context* ctx, const std::vector<std::string>& text, const std::string& font_path) 
  : UIObject(ctx) {
  text_group_ = std::make_shared<UIGroup>(ctx);
  text_group_->SetPosition(glm::vec2(0, 0));
  text_group_->SetDimensions(this->GetDimensions());
  offset_ = 0.0f;
  margin_ = 64.0f;
  for (auto item : text) {
    auto ui_text = std::make_shared<UITextObject>(ctx, font_path);
    ui_text->SetText(item);
    // TODO: middle doesnt work as one would expect. figure that out at some point lol
    ui_text->SetVerticalAlign(AlignmentV::TOP);
    ui_text->SetHorizontalAlign(AlignmentH::CENTER);
    ui_text->SetTextSize(16.0f);
    ui_text->SetTextColor(glm::vec4(1.0));
    ui_text->SetDimensions(ui_text->GetMinimumBoundingDims());
    text_group_->AddChild(ui_text);
    text_items_.push_back(ui_text);
  }
}

void HorizontalMenuGroup::SetTextSize(float size_pt) {
  for (auto item : text_items_) {
    item->SetTextSize(size_pt);
  }

  Invalidate();
}

void HorizontalMenuGroup::SetMarginSize(float size_px) {
  margin_ = size_px;
  Invalidate();
}

void HorizontalMenuGroup::RenderMaterial(const RenderContext& rc) {
  // only go through these steps if something has invalidated
  if (!IsValid()) {
    text_group_->SetDimensions(this->GetDimensions());
    for (auto item : text_items_) {
      auto min_dims = item->GetMinimumBoundingDims();
      item->SetDimensions(min_dims);
    }

    // record offset thus far.
    float offset_x = 0.0f;
    float rolling_offset = 0.0f;
    float t_offset = GetMenuOffset();

    for (int i = 0; i < text_items_.size(); i++) {
      auto item = text_items_[i];
      auto min_dims = item->GetDimensions();
      item->SetPosition(glm::vec2(rolling_offset, GetDimensions().y / 2 - min_dims.y / 2));
      if (i + 1 == text_items_.size()) {
        break;
      }
      
      if (i < t_offset && t_offset <= i + 1) {
        // here we interpolate between two values.
        // rolling_offset is the start of text box i -- we're somewhere between i's center and i+1's center
        float lo_offset = rolling_offset + item->GetDimensions().x / 2;
        float hi_offset = lo_offset + item->GetDimensions().x / 2 + margin_ + text_items_[i + 1]->GetDimensions().x / 2;
        float local_offset = t_offset - i;
        offset_x = (lo_offset * (1 - local_offset)) + (hi_offset * local_offset);
      }
      
      rolling_offset += text_items_[i]->GetDimensions().x + margin_;
    }

    // center items relative to the shit
    offset_x -= GetDimensions().x / 2;

    for (auto i : text_items_) {
      auto dims_old  = i->GetPosition();
      dims_old.x -= offset_x;
      i->SetPosition(dims_old);
      i->Invalidate();
    }

    // then, invalidate and draw the container.
    text_group_->Invalidate();
    text_group_->RenderMaterial(rc);
  }

  UIObject::RenderMaterial(rc);
}

void HorizontalMenuGroup::DrawUI(glm::vec2 minXY, glm::vec2 maxXY) {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, text_group_->GetFramebuffer());
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GetFramebuffer());
  glm::ivec2 dims = static_cast<glm::ivec2>(GetDimensions());
  glBlitFramebuffer(0, 0, dims.x, dims.y, 0, 0, dims.x, dims.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
  // restore old state
  // TODO: no fade -- add that later? :)
  glBindFramebuffer(GL_FRAMEBUFFER, GetFramebuffer());
}

void HorizontalMenuGroup::SetMenuOffset(float offset) {
  if (offset > text_items_.size()) {
    offset_ = static_cast<float>(text_items_.size());
  } else if (offset < 0.0f) {
    offset_ = 0.0f;
  } else {
    offset_ = offset;
  }
}

float HorizontalMenuGroup::GetMenuOffset() {
  return offset_;
}

std::vector<std::shared_ptr<const UITextObject>> HorizontalMenuGroup::GetTextItems() {
  std::vector<std::shared_ptr<const UITextObject>> res;
  for (auto item : text_items_) {
    res.push_back(std::const_pointer_cast<const UITextObject>(item));
  }

  return res;
}

}