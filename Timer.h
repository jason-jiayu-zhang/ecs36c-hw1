#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class Timer {
 public:
  Timer() { Reset(); }
  void Reset() { start_ = std::chrono::high_resolution_clock::now(); }
  // return microseconds as double
  double ElapsedMicroseconds() const {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start_).count();
  }
  friend std::ostream& operator<<(std::ostream& os, const Timer& t) {
    os << "CPU time: " << t.ElapsedMicroseconds() << " microseconds";
    return os;
  }

 private:
  std::chrono::high_resolution_clock::time_point start_;
};

#endif // TIMER_H
