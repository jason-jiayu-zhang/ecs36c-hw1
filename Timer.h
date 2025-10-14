/**
 * Timer.h
 * 
 * High-precision timer utility class for measuring code execution time.
 * Uses std::chrono::high_resolution_clock for accurate microsecond-level timing.
 * 
 * Usage:
 *   Timer timer;              // Timer starts automatically
 *   // ... code to measure ...
 *   double us = timer.ElapsedMicroseconds();  // Get elapsed time
 * 
 * Or:
 *   Timer timer;
 *   timer.Reset();            // Restart timer
 *   // ... code to measure ...
 *   std::cout << timer;       // Print elapsed time using operator<<
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

/**
 * Timer - High-precision timer for performance measurement.
 * 
 * Automatically starts timing on construction. Can be reset and queried
 * multiple times. Provides microsecond-level precision.
 */
class Timer {
 public:
  /**
   * Constructor - automatically starts the timer.
   * Equivalent to calling Reset() immediately after construction.
   */
  Timer() { Reset(); }
  
  /**
   * Reset the timer to the current time.
   * Use this to start a new measurement without creating a new Timer object.
   */
  void Reset() { start_ = std::chrono::high_resolution_clock::now(); }
  
  /**
   * Get elapsed time in microseconds since last Reset() or construction.
   * 
   * @return Elapsed time as a double-precision floating point value in microseconds
   */
  double ElapsedMicroseconds() const {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start_).count();
  }
  
  /**
   * Stream output operator for convenient printing.
   * 
   * Outputs formatted string: "CPU time: <microseconds> microseconds"
   * 
   * Example usage:
   *   Timer t;
   *   // ... do work ...
   *   std::cout << t << std::endl;
   * 
   * @param os Output stream
   * @param t Timer object to output
   * @return Reference to output stream (enables chaining)
   */
  friend std::ostream& operator<<(std::ostream& os, const Timer& t) {
    os << "CPU time: " << t.ElapsedMicroseconds() << " microseconds";
    return os;
  }

 private:
  std::chrono::high_resolution_clock::time_point start_;  ///< Start time for timing measurement
};

#endif // TIMER_H
