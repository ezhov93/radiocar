#ifndef TESTFRONTLIGHT_H
#define TESTFRONTLIGHT_H

#include "../frontlight.h"
#include "../light.h"
#include "testinterface.h"
#include "../timer.h"

class TestFrontLight : public TestInterface {
 public:
  explicit TestFrontLight(const int left, const int right)
      : _left(left), _right(right), _frontLights(_left, _right), _timer(3000) {}
  ~TestFrontLight() = default;

  virtual void begin() final {
    Serial.begin(9600);
    Serial.println("*** TEST Front Lights class ***");
    _frontLights.begin();
    _timer.start();

    // exec(_left);
    // exec(_right);
    // exec(_frontLights);

    _frontLights.enable();
    while (!_timer.isReady()) _frontLights.update();
    _left.setBlink(true);
    while (!_timer.isReady()) _frontLights.update();
    _left.setBlink(false);
    _right.setBlink(true);
    while (!_timer.isReady()) _frontLights.update();
    _frontLights.disable();
    while (!_timer.isReady()) _frontLights.update();
    _frontLights.enable();
  }

  virtual void end() final {}

  virtual void update() final { _frontLights.update(); }

 private:
  void exec(LightInterface &light) {
    light.enable(true);
    while (!_timer.isReady()) light.update();
    light.setBlink(true);
    while (!_timer.isReady()) light.update();
    light.disable(true);
    light.setBlink(false);
  }

  Light _left;
  Light _right;
  FrontLight _frontLights;
  Timer _timer;
};

#endif  // TESTFRONTLIGHT_H