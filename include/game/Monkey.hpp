#ifndef MONKEY_H_
#define MONKEY_H_

#include <engine/Context.hpp>
#include <critter/Model.hpp>
#include <shader/materials/MatteMaterial.hpp>

namespace game {
class Monkey : public ::monkeysworld::critter::Model {
 public:
  Monkey(::monkeysworld::engine::Context* ctx);

  void Update() override;
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
 private:
  ::monkeysworld::shader::materials::MatteMaterial mat_;
};

}

#endif