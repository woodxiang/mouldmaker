#pragma once

#include <emscripten.h>
#include <emscripten/bind.h>
class ModelBase
{
private:
  /* data */
public:
  ModelBase(/* args */);
  ~ModelBase();

  static int test_method(int x);
};
