#include "model_base.h"

ModelBase::ModelBase(/* args */)
{
}

ModelBase::~ModelBase()
{
}

int ModelBase::test_method(int x)
{
  return x + 1;
}

EMSCRIPTEN_BINDINGS(model_base)
{
  emscripten::class_<ModelBase>("ModelBase")
      .constructor()
      .class_function("test_method", &ModelBase::test_method);
}
