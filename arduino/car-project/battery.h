#ifndef BATTERY_H
#define BATTERY_H

#include "filter.h"
#include "timer.h"

class Battery {
 public:
  explicit Battery(const int pin) : _pin(pin), _timer(250) {}

  ~Battery() = default;

  void begin() {
    // pinMode(_pin, ANALOG_INPUT);
    for (int i = 0; i < 3; ++i) _filter.add(digVoltage());
    _timer.start();
  }

  float voltage() const { return _filter.value() * 5.f / 1023.f; }

  void update() {
    if (_timer.isReady()) _filter.add(digVoltage());
  }

 private:
  const int _pin;
  Filter _filter;
  Timer _timer;

  int digVoltage() const { return analogRead(_pin); }
};

#endif  // BATTERY_H
