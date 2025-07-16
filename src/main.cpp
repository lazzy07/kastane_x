#include <iostream>
#include <cuda/cuda_runtime.h>

#include "engine/Engine.hpp"
#include "test/BoxWorldTest.hpp"

int main(){
  KX::Engine::Engine engine;
  engine.PrintWelcomeScreen();

  KX::Test::BoxWorldTest test = KX::Test::BoxWorldTest();
  test.run();
  // engine.StartServer();
}
