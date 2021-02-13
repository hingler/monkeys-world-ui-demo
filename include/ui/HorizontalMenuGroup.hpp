#ifndef HORIZONTAL_MENU_GROUP_H_
#define HORIZONTAL_MENU_GROUP_H_

#include <critter/ui/UIObject.hpp>
#include <critter/ui/UIGroup.hpp>

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
   */ 
  HorizontalMenuGroup(::monkeysworld::engine::Context* ctx, const std::vector<std::string>& text);
  void DrawUI(glm::vec2 minXY, glm::vec2 maxXY) override;

  // sets/gets the menu offset -- whole numbers represent entries.
  void SetMenuOffset(float offset);
  float GetMenuOffset();

  /**
   *  @returns the index of the currently visible menu item.
   */ 
  int GetActiveMenuItem();

  // uigroup will be written to once most likely, when we input the menu items
  // to draw: we'll just slide it back and forth
  // menugroup will need to take up the whole horizontal space as a result

  // the alternative could be drawing the group once, and then just sliding this object back and forth
  // however, i don't like that as much tbh
  // it's not as isolated as i would like
 private:
  // contains the inside
  ::monkeysworld::critter::ui::UIGroup text_group_;
};

}

// nest a ui group inside
// place our menu text inside of that
// pass an array of strings on construction



#endif