#ifndef TESTINTERFACE_H
#define TESTINTERFACE_H

class TestInterface {
 public:
  virtual ~TestInterface() = default;
  virtual void begin() = 0;
  virtual void end() = 0;
  virtual void update() = 0;
};

#endif  // TESTINTERFACE_H