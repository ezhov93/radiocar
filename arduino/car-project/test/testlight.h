#ifndef TESTLIGHT_H
#define TESTLIGHT_H

#include "../light.h"
#include "testinterface.h"
#include "../timer.h"

class TestLight : public TestInterface {
 public:
  TestLight(const int pin) : _light(pin), _timer(5000), _active(false) {}
  ~TestLight() = default;

  virtual void begin() final {
    _active = true;
    _light.begin();
    _light.enable();
    delay(3000);
    _light.setBlink(true);
    _timer.start();
  }
  virtual void end() final {
    _light.disable(true);
    _active = false;
  }

  virtual void update() final {
    if (!_active) return;
    if (_timer.isReady()) _light.disable(_light.isEnable());
    _light.update();
  }

 private:
  Light _light;
  Timer _timer;
  bool _active;
};

#endif  // TESTLIGHT_H