#ifndef MONKEY_H_
#define MONKEY_H_

#include <engine/Context.hpp>
#include <file/CachedFileLoader.hpp>
#include <critter/Model.hpp>
#include <shader/materials/MatteMaterial.hpp>

namespace game {
class Monkey : public ::monkeysworld::critter::Model {
 public:
  /**
   *  Creates a new monkey on the screen.
   *  @param ctx - the context associated with this instance.
   *  @param loader - the file loader used to load the monkey.
   */ 
  Monkey(::monkeysworld::engine::Context* ctx,
         std::shared_ptr<::monkeysworld::file::CachedFileLoader> loader);

  void Update() override;
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
 private:
  ::monkeysworld::shader::materials::MatteMaterial mat_;
};

}

#endif