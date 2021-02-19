#ifndef HORIZONTAL_MENU_GROUP_H_
#define HORIZONTAL_MENU_GROUP_H_

#include <critter/ui/UIObject.hpp>
#include <critter/ui/UIGroup.hpp>
#include <font/UITextObject.hpp>

#include <string>
#include <vector>

namespace ui {

/**
 *  Stores a series of text objects representing menu items.
 *  Enables the user to cycle through these items.
 */ 
class HorizontalMenuGroup : public ::monkeysworld::critter::ui::UIObject {
 public:
  /**
   *  @param ctx - context for this group.
   *  @param text - list of menu items which are displayed by this group.
   *  @param font_path - path to the font we want to load.
   */ 
  HorizontalMenuGroup(::monkeysworld::engine::Context* ctx, const std::vector<std::string>& text, const std::string& font_path);
  
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
  void DrawUI(glm::vec2 minXY, glm::vec2 maxXY, ::monkeysworld::shader::Canvas canvas) override;

  /**
   *  Set the size of all menu elements.
   *  @param size_pt - new size in pt.
   */ 
  void SetTextSize(float size_pt);

  /**
   *  Sets the size of the margins in between elements.
   *  @param size_px - new margin size in pixels
   */ 
  void SetMarginSize(float size_px);

  /**
   *  Sets the offset of our menu items. It is constrained to the range [0, <number of items>].
   *  @param offset - the new menu offset. If a value is supplied outside the range of constraint,
   *                  the offset is limited to the defined range.
   */ 
  void SetMenuOffset(float offset);

  /**
   *  @returns the current menu offset.
   */ 
  float GetMenuOffset();

  /**
   *  @returns a fresh list of const pointers which represent the text objects
   *           stored in this menu group.
   */ 
  std::vector<std::shared_ptr<const ::monkeysworld::font::UITextObject>> GetTextItems();

  // uigroup will be written to once most likely, when we input the menu items
  // to draw: we'll just slide it back and forth
  // menugroup will need to take up the whole horizontal space as a result

  // the alternative could be drawing the group once, and then just sliding this object back and forth
  // however, i don't like that as much tbh
  // it's not as isolated as i would like
 private:
  // contains the inside
  std::shared_ptr<::monkeysworld::critter::ui::UIGroup> text_group_;
  std::vector<std::shared_ptr<::monkeysworld::font::UITextObject>> text_items_;
  float margin_;
  float offset_;
};

}

// nest a ui group inside
// place our menu text inside of that
// pass an array of strings on construction



#endif