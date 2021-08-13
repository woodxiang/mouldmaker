#pragma once

#include "model_base.h"
#include "test_model_config.h"

class TestModel : public ModelBase
{
private:
  TestModelConfig config_;

public:
  TestModel(TestModelConfig &cfg);
  ~TestModel();

  void UpdateConfig(TestModelConfig& cfg);
};
