#ifndef LERP_MENU_H_
#define LERP_MENU_H_

#include <ui/HorizontalMenuGroup.hpp>
#include <input/KeyListener.hpp>
#include <engine/SceneSwap.hpp>
#include <gamemenu/GameMenu.hpp>

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
  const double SMOOTH_FACTOR = 0.0003;
  const double LERP_EPS = 0.0001;
  void UpdateMenuOffset();
  void UpdateConfirmationOpacity();
  void UpdateSceneSwap();
  int lerp_target_;

  bool confirmed_;
  double confirmed_timer_;
  std::shared_ptr<::monkeysworld::engine::SceneSwap> swap_;

  const double CONFIRMED_DURATION = 0.4;

  ::monkeysworld::input::KeyListener listener_l_;
  ::monkeysworld::input::KeyListener listener_r_;
  ::monkeysworld::input::KeyListener listener_enter_;

  int music_handle_;

};

}

#endif