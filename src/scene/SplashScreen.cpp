#include <critter/Empty.hpp>
#include <critter/GameCamera.hpp>

#include <scene/SplashScreen.hpp>
#include <game/OctTube.hpp>

#include <glm/gtx/euler_angles.hpp>

#define M_PI_ 3.1415926535897932384626
#define M_PI_2_ 1.57079632679489661923

namespace scene {

using ::monkeysworld::critter::Empty;
using ::monkeysworld::critter::GameCamera;
using ::monkeysworld::engine::Context;
using ::monkeysworld::input::MouseEvent;
using ::game::OctTube;

class MovingCamera : public GameCamera {
 public:
  MovingCamera(Context* ctx) : GameCamera(ctx) {
    // create event which moves the camera
    motion_x = 0;
    motion_z = 0;

    rot_x = 0;
    rot_y = 0;

    ctx->GetEventManager()->RegisterKeyListener(GLFW_KEY_LEFT_ALT, [=](int a, int b, int c) {
      auto cur = ctx->GetEventManager()->GetCursor();
      if (b != GLFW_PRESS) {
        return;
      }

      if (cur->IsCursorLocked()) {
        cur->UnlockCursor();
      } else {
        cur->LockCursor();
      }
    });

    cursor_cache_ = GetContext()->GetEventManager()->GetCursor()->GetCursorPosition();

    auto click_lambda = [&, this](MouseEvent e) {
      BOOST_LOG_TRIVIAL(trace) << "hello: x=" << e.absolute_pos.x << ", y=" << e.absolute_pos.y;
    };

    uint64_t hi = GetContext()->GetEventManager()->RegisterClickListener(click_lambda);

    // ideally: we always pass the context in instead of relying on *this*
    // note also: the creator is responsible for destroying this event handler or else shit will break
    auto event_lambda = [&, this](int key, int action, int mods) {
      int mod = 0;
      if (action == GLFW_PRESS) {
        mod = 5;
      } else if (action == GLFW_RELEASE) {
        mod = -5;
      }

      switch (key) {
        case GLFW_KEY_S:
          motion_z -= mod;
          break;
        case GLFW_KEY_W:
          motion_z += mod;
          break;
        case GLFW_KEY_A:
          motion_x += mod;
          break;
        case GLFW_KEY_D:
          motion_x -= mod;
      }
    };

    auto rotation_lambda = [&, this](int key, int action, int mods) {
      int mod = 0;
      if (action == GLFW_PRESS) {
        mod = 2;
      } else if (action == GLFW_RELEASE) {
        mod = -2;
      }

      switch (key) {
        case GLFW_KEY_DOWN:
          rot_x -= mod;
          break;
        case GLFW_KEY_UP:
          rot_x += mod;
          break;
        case GLFW_KEY_LEFT:
          rot_y += mod;
          break;
        case GLFW_KEY_RIGHT:
          rot_y -= mod;
      }
    };

    // need a way to register multiple events to a single id.
    w_event = GetContext()->GetEventManager()->RegisterKeyListener(GLFW_KEY_W, event_lambda);
    s_event = GetContext()->GetEventManager()->RegisterKeyListener(GLFW_KEY_S, event_lambda);
    a_event = GetContext()->GetEventManager()->RegisterKeyListener(GLFW_KEY_A, event_lambda);
    d_event = GetContext()->GetEventManager()->RegisterKeyListener(GLFW_KEY_D, event_lambda);
  }

  void Update() override {
    // tba: use cursor position to rotate
    auto w = GetPosition();
    double delta = GetContext()->GetDeltaTime();
    auto r = GetRotation();



    glm::mat4 rotation = glm::eulerAngleYXZ(r.y, r.x, r.z);
    glm::vec4 initial(0, 0, -1, 0);
    glm::vec4 initial_x(-1, 0, 0, 0);
    initial = rotation * initial;
    initial_x = rotation * initial_x;
    glm::dvec2 cur_new = GetContext()->GetEventManager()->GetCursor()->GetCursorPosition();
    SetPosition(w + glm::vec3(initial * static_cast<float>(motion_z * delta)) + glm::vec3(initial_x * static_cast<float>(motion_x * delta)));

    if (!GetContext()->GetEventManager()->GetCursor()->IsCursorLocked()) {
      cursor_cache_ = cur_new;
      return;
    }
    rot_y = r.y - delta * (cur_new.x - cursor_cache_.x) * 1.414f;
    rot_x = r.x - delta * (cur_new.y - cursor_cache_.y) * 1.414f;

    cursor_cache_ = cur_new;

    if (rot_x > M_PI_2_) {
      rot_x = M_PI_2_;
    } else if (rot_x < -M_PI_2_) {
      rot_x = -M_PI_2_;
    }


    SetRotation(glm::vec3(rot_x, rot_y, r.z));
  }

  ~MovingCamera() {
    // call from destroy so we can ensure the context is live
    // though it still should be here
    auto manager = GetContext()->GetEventManager();
    manager->RemoveKeyListener(a_event);
    manager->RemoveKeyListener(s_event);
    manager->RemoveKeyListener(w_event);
    manager->RemoveKeyListener(d_event);
  }
 private:
  uint64_t a_event;
  uint64_t d_event;
  uint64_t s_event;
  uint64_t w_event;

  uint64_t u_event;
  uint64_t do_event;
  uint64_t l_event;
  uint64_t r_event;

  uint64_t click_event;

  double motion_x;
  double motion_z;

  double rot_x;
  double rot_y;

  glm::dvec2 cursor_cache_;
};

SplashScreen::SplashScreen() : game_root_(nullptr), ui_root_(nullptr) {}

void SplashScreen::Initialize(Context* ctx) {
  // im not going to fucking texture shit anyway lol
  game_root_ = std::make_shared<Empty>(ctx);
  auto tube = std::make_shared<OctTube>(ctx);
  game_root_->AddChild(tube);
  game_root_->SetPosition(glm::vec3(0, -4, -32));
  auto cam = std::make_shared<MovingCamera>(ctx);
  cam->SetPosition(glm::vec3(0, 0, 0));
  cam->SetFov(45.0f);
  cam->SetActive(true);
  game_root_->AddChild(cam);
}

std::shared_ptr<::monkeysworld::critter::GameObject> SplashScreen::GetGameObjectRoot() {
  return game_root_;
}

std::shared_ptr<::monkeysworld::critter::ui::UIObject> SplashScreen::GetUIObjectRoot() {
  return ui_root_;
}

}