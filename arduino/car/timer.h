#ifndef TIMER_H
#define TIMER_H

#include "timerobserver.h"

class Timer {
 public:
  explicit Timer(const int msec = 1000) : _period(msec), _active(false), _observer(nullptr) {}

  ~Timer() = default;

  void setPeriod(const int msec) { _period = msec; }

  void start() {
    _time = millis();
    _active = true;
  }

  void stop() { _active = false; }

  void restart() { start(); }

  void resume() { _active = true; }

  bool isReady() {
    update();
    bool tmp = _ready;
    _ready = false;
    return tmp;
  }

  void update() {
    if (_active) {
      if (millis() - _time >= _period) {
        _time = millis();
        _ready = true;
        notifyIsReady();
      }
    }
  }

  bool isActive() const { return _active; }

  void registerObserver(TimerObserver *o) {
    if (o) _observer = o;
  }

  void removeObserver() { _observer = nullptr; }

 private:
  void notifyIsReady() {
    if (_observer) _observer->updateIsReady();
  }

  unsigned int _period;
  unsigned int _time;
  TimerObserver *_observer;
  bool _active;
  bool _ready;
};

#endif  // TIMER_H