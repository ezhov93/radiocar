#ifndef TIMER_H
#define TIMER_H

#include "timerobserver.h"

// #define USE_TIMER_OVERFLOW_PROTECTION

class Timer {
 public:
  explicit Timer(const int msec = 1000)
      : _period(msec), _active(false), _observer(nullptr) {}

  ~Timer() = default;

  void setPeriod(const int msec) { _period = msec; }

  void start() {
    _time = millis();
    _active = true;
    _ready = false;
  }

  void stop() {
    _active = false;
    _ready = false;
  }

  void restart() { start(); }

  bool isReady() {
    update();
    bool tmp = _ready;
    _ready = false;
    return tmp;
  }

  void update() {
    if (_active) {
      if (millis() - _time >= _period) {
        _ready = true;
        notifyIsReady();
#ifndef USE_TIMER_OVERFLOW_PROTECTION
        _time += _period;
#else
        do {
          _time += _period;
          if (_time < _period) break;
        } while (_time < millis() - _period);
#endif
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

  uint32_t _period;
  uint32_t _time;
  TimerObserver *_observer;
  bool _active;
  bool _ready;
};

#endif  // TIMER_H