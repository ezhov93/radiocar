#ifndef TIMEROBSERVER_H
#define TIMEROBSERVER_H

class TimerObserver {
 public:
  virtual ~TimerObserver() = default;
  virtual void updateIsReady() = 0;
};

#endif  // TIMEROBSERVER_H