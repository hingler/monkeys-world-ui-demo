#ifndef GAME_MENU_H_
#define GAME_MENU_H_

#include <engine/Scene.hpp>


namespace gamemenu {

class GameMenu : public ::monkeysworld::engine::Scene {

 public:
  GameMenu();

  /**
   *  Pass a texture to this scene representing the last frame generated by the previous scene.
   *  @param color - the GLuint which contains the desired frame.
   * 
   *  Does nothing if the scene has not yet completed initializing.
   */ 
  void SetLastFrameTexture(GLuint color);
  void Initialize(::monkeysworld::engine::Context* ctx) override;
  std::string GetSceneIdentifier() override;
};

}

#endif