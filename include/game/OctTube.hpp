#ifndef OCT_TUBE_H_
#define OCT_TUBE_H_

#include <mat/DitheredOctMat.hpp>

#include <engine/Context.hpp>
#include <critter/Model.hpp>
#include <file/CachedFileLoader.hpp>

namespace game {
class OctTube : public ::monkeysworld::critter::Model {

 public:
  OctTube(::monkeysworld::engine::Context* ctx,
         std::shared_ptr<::monkeysworld::file::CachedFileLoader> loader);

  void Update() override;

  /**
   *  Sets the strength of the generated light.
   *  @param fac - the strength of the light emitted from the base of the tube.
   */ 
  void SetLightStrength(float fac);
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
 private:
  mat::DitheredOctMat tube_mat_;
  float rot_;
};
}

#endif