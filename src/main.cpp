#include <iostream>
#include <cuda/cuda_runtime.h>

#include "engine/Engine.hpp"

int main(){
  KX::Engine::Engine engine;
  engine.PrintWelcomeScreen();
  // engine.StartServer();
}
