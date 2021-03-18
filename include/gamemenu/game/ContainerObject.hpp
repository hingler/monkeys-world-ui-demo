#ifndef CONTAINER_OBJECT_H_
#define CONTAINER_OBJECT_H_

#include <critter/Model.hpp>
#include <shader/materials/MatteMaterial.hpp>

namespace gamemenu {
namespace game {

/**
 *  A container which will contain monkeys :)
 */ 
class ContainerObject : public ::monkeysworld::critter::Model {
 public:
  ContainerObject(::monkeysworld::engine::Context* ctx);

  /**
   *  Draw the container onto the screen.
   */ 
  void RenderMaterial(const ::monkeysworld::engine::RenderContext& rc) override;
 private:
  ::monkeysworld::shader::materials::MatteMaterial mat_;
};

}
}

#endif