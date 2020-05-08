#ifndef RECIVEROBSERVER_H
#define RECIVEROBSERVER_H

class ReceiverObserver {
 public:
  virtual ~ReceiverObserver() = delete;
  virtual void updateIsReady(bool light, byte lr, byte fb) = 0;
};

#endif  // RECIVEROBSERVER_H