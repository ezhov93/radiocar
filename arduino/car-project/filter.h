#ifndef FILTER_H
#define FILTER_H

class Filter {
 public:
  Filter() : _counter(0), _value(0) {}

  ~Filter() = default;

  float add(const int value) {
    _array[_counter] = value;
    if (++_counter > 2) _counter = 0;

    int &a = _array[0];
    int &b = _array[1];
    int &c = _array[2];

    if ((a <= b) && (a <= c))
      _value = (b <= c) ? b : c;
    else if ((b <= a) && (b <= c))
      _value = (a <= c) ? a : c;
    else
      _value = (a <= b) ? a : b;

    return _value;
  }

  int value() const { return _value; }

 private:
  int _array[3];
  int _value;
  int _counter;
};

#endif  // FILTER_H