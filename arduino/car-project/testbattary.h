#ifndef TESTBATTERY_H
#define TESTBATTERY_H

#include "battery.h"
#include "testinterface.h"
#include "timer.h"

class TestBattery : public TestInterface {
 public:
  explicit TestBattery(const int pin) : _battery(pin), _timer(1000) {}
  ~TestBattery() = default;

  virtual void begin() final {
    Serial.begin(9600);
    Serial.println("*** TEST Battary class ***");
    _battery.begin();
    _timer.start();
  }
  virtual void end() final {}

  virtual void update() final {
    _battery.update();
    if (_timer.isReady()) {
      Serial.print("Voltage: ");
      Serial.print(_battery.voltage());
      Serial.println("V");
    }
  }

 private:
  Battery _battery;
  Timer _timer;
};

#endif  // TESTBATTERY_H