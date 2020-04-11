#ifndef LIGHTINTERFACE_H
#define LIGHTINTERFACE_H

class LightInterface {
 public:
  virtual ~LightInterface() = default;
  virtual void begin() = 0;
  virtual void enable(const bool) = 0;
  virtual void disable(const bool) = 0;
  virtual void setBlink(const bool) = 0;
  virtual bool isBlink() const = 0;
  virtual bool isEnable() const = 0;
  virtual void update() = 0;
};

#endif  // LIGHTINTERFACE_H