#ifndef LIGHT_H
#define LIGHT_H

#include "lightinterface.h"
#include "timer.h"

class Light : public LightInterface {
 public:
  explicit Light(const int pin) : _pin(pin), _timer(500), _enable(false) {}

  ~Light() = default;

  virtual void begin() final { pinMode(_pin, OUTPUT); }

  virtual void enable(const bool enable = true) final {
    _enable = enable;
    digitalWrite(_pin, enable ? HIGH : LOW);
  }

  virtual void disable(const bool disable = true) final { enable(!disable); }

  virtual void setBlink(const bool enable) final {
    if (enable) {
      _timer.start();
    } else {
      _timer.stop();
      this->enable(_enable);
    }
  }

  virtual bool isBlink() const final { return _timer.isActive(); }

  virtual bool isEnable() const { return _enable; }

  virtual void update() final {
    if (_timer.isReady()) {
      int state = digitalRead(_pin);
      digitalWrite(_pin, state ? LOW : HIGH);
    }
  }

 private:
  const int _pin;
  Timer _timer;
  bool _enable;
  bool _blinkState;
};

#endif  // LIGHT_H