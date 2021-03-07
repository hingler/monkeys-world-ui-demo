#ifndef STAGE_BANNER_H_
#define STAGE_BANNER_H_

#include <critter/ui/UIGroup.hpp>
#include <critter/ui/UIImage.hpp>
#include <critter/ui/UIObject.hpp>

#include <vector>

namespace gamemenu {
namespace ui {

class StageBanner : public ::monkeysworld::critter::ui::UIObject {
 public:
  StageBanner(::monkeysworld::engine::Context* ctx);
  void Update() override;
  void Layout(glm::vec2 size) override;
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc);
  void DrawUI(glm::vec2, glm::vec2, ::monkeysworld::shader::Canvas canvas) override;

  /**
   *  Displays the next banner in sequence.
   *  If the last banner in sequence has already been displayed, this will hide all banners.
   */ 
  void Advance();

  /**
   *  Displays the previous banner in sequence.
   *  If the first banner in sequence is currently displayed, this will hide all banners.
   */ 
  void GoBack();
  const static int BANNER_WIDTH = 1920;
  const static int BANNER_HEIGHT = 200;
 private:
  std::shared_ptr<::monkeysworld::critter::ui::UIGroup> group_;
  std::vector<std::shared_ptr<::monkeysworld::critter::ui::UIImage>> banners_;
  float transition_current_;
  int transition_target_;


};

}
}

#endif