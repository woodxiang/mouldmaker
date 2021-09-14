#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

int main()
{
  EM_ASM(allReady());

  std::cout << "Hello World." << std::endl;
}

float lerp(float a, float b, float t)
{
  return (1 - t) * a + t * b;
}

extern "C"
{
  int Sum(int x, int y)
  {
    return x + y;
  }
}

EMSCRIPTEN_BINDINGS(my_module)
{
  function("lerp", &lerp);
}