#ifndef RECIVER_H
#define RECIVER_H

#include "reciverobserver.h"
#include "timer.h"

class Reciver {
 public:
  Reciver()
      : _msg(*reinterpret_cast<Msg *>(_data)), _observer(nullptr), _timer(10) {}

  ~Reciver() = default;

  void begin() { Serial.begin(9600); }

  void update() {
    if (Serial.available()) {
      _data[0] = Serial.read();
      if (_msg.key == Key) {
        _timer.start();
        _ready = true;
        while (Serial.available() < 2) {
          if (_timer.isReady()) {
            _ready = false;
            break;
          }
        }
        if (_ready) {
          _data[1] = Serial.read();
          _data[2] = Serial.read();
          notyfyIsReady(_msg.light, _msg.lr, _msg.fb);
        }
      }
    }
    while (Serial.available()) Serial.read();
  }

  void registerObserver(ReceiverObserver *o) {
    if (o) _observer = o;
  }

  void removeObserver() { _observer = nullptr; }

 private:
  static const byte Key = 0xA;
  struct Msg {
    byte key : 4;
    byte : 3;
    bool light : 1;
    byte lr;
    byte fb;
  };
  bool _ready;
  byte _data[sizeof(Msg)];
  Msg &_msg;
  ReceiverObserver *_observer;
  Timer _timer;

  bool notyfyIsReady(bool light, byte lr, byte fb) {
    if (_observer) _observer->updateIsReady(light, lr, fb);
  }
};

#endif  // RECIVER_H