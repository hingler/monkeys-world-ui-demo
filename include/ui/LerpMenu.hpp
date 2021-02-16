#ifndef LERP_MENU_H_
#define LERP_MENU_H_

#include <ui/HorizontalMenuGroup.hpp>
#include <input/KeyListener.hpp>

namespace ui {

class LerpMenu : public HorizontalMenuGroup {
 public:
  LerpMenu(::monkeysworld::engine::Context* ctx, const std::vector<std::string>& text, const std::string& font_path);
  
  void Create() override;
  void Update() override;

  /**
   *  @returns the item which will currently be selected by this menu
   */ 
  int GetSelectedItem();
 private:
  // moves menu offset towards lerp target
  const double SMOOTH_FACTOR = 0.01f;
  const double LERP_EPS = 0.0001;
  void UpdateMenuOffset();
  int lerp_target_;
  ::monkeysworld::input::KeyListener listener_l_;
  ::monkeysworld::input::KeyListener listener_r_;

};

}

#endif