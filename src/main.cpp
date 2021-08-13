#include <iostream>

#include <emscripten.h>

int main()
{
  EM_ASM(allReady());

  std::cout << "Hello World." << std::endl;
}