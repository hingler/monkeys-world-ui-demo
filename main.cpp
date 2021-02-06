#include <engine/BaseEngine.hpp>
#include <engine/Context.hpp>
#include <scene/SplashScreen.hpp>
#include <GLFW/glfw3.h>

using namespace ::monkeysworld::engine::baseengine;
using ::monkeysworld::engine::Context;

int main(int, char**) {
  std::cout << "Hello, world!\n";
  GLFWwindow* win = InitializeGLFW(1280, 720, "i see pussy sex intercouse in your future");
  auto scene = new ::scene::SplashScreen();
  auto ctx = std::make_shared<Context>(win, scene);

  GameLoop(ctx, win);

  glfwDestroyWindow(win);
  glfwTerminate();
  return 0;
}
