#ifndef ELECTRICMOTOR_H
#define ELECTRICMOTOR_H

class ElectricMotor {
 private:
  enum State { Stop, Forward, Backward };
  const int _frd;
  const int _bck;
  int _power;
  byte _dig;
  mutable State _state;

  int powerToDig(const int val) const {
    static const float coef = 255 / 100;
    return val * coef;
  }

 public:
  ElectricMotor(const int forwardPin, const int backPin)
      : _frd(forwardPin), _bck(backPin), _power(0), _dig(0), _state(Stop) {}

  ~ElectricMotor() = default;

  void begin() {
    pinMode(_frd, OUTPUT);
    pinMode(_bck, OUTPUT);
    stop();
  }

  void forward() const {
    _state = Forward;
    analogWrite(_bck, 0);
    analogWrite(_frd, _dig);
  }

  void backward() const {
    _state = Backward;
    analogWrite(_frd, 0);
    analogWrite(_bck, _dig);
  }

  void stop() const {
    _state = Stop;
    analogWrite(_frd, 0);
    analogWrite(_bck, 0);
  }

  void setPower(const int val) {
    _power = val;
    _dig = powerToDig(val);
    if (val <= 0)
      stop();
    else if (_state == Forward)
      forward();
    else if (_state == Backward)
      backward();
  }

  int power() const { return _power; }

  bool isStop() const { return _state == Stop; }
};

#endif  // ELECTRICMOTOR_H