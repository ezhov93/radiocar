#ifndef TRANSMITER_H
#define TRANSMITER_H

#include "battery.h"
#include "timer.h"

class Transmiter {
 public:
  explicit Transmiter(const Battary &obj) : _battery(obj), _timer(500) {}

  ~Transmiter() = default;

  void begin() { _timer.start(); }

  void update() {
    if (_timer.isReady()) Serial.println(_battery.voltage());
  }

 private:
  const Battery &_battery;
  Timer _timer;
};

#endif  // TRANSMITER_H