#ifndef FRONTLIGHT_H
#define FRONTLIGHT_H

#include "lightinterface.h"

class FrontLight : public LightInterface {
 public:
  FrontLight(LightInterface &left, LightInterface &right)
      : _left(left), _right(right) {}

  ~FrontLight() = default;

  virtual void begin() final {
    _left.begin();
    _right.begin();
    helloBlink();
  }

  virtual void enable(const bool enable = true) final {
    _left.enable(enable);
    _right.enable(enable);
  }

  virtual void disable(const bool disable = true) final {
    _left.disable(disable);
    _right.disable(disable);
  }

  virtual void setBlink(const bool enable) final {
    _left.setBlink(enable);
    _right.setBlink(enable);
  }

  virtual bool isBlink() const final {
    return _left.isBlink() && _right.isBlink();
  }

  virtual bool isEnable() const final {
    return _left.isEnable() && _right.isEnable();
  }

  virtual void update() final {
    _left.update();
    _right.update();
  }

 private:
  void helloBlink() {
    int cnt = 8;
    while (cnt--) {
      enable(!isEnable());
      delay(250);
    }
    disable();
  }

  LightInterface &_left;
  LightInterface &_right;
};

#endif  // FRONTLIGHT_H