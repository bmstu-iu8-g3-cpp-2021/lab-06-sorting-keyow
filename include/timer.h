// Copyright 2021 keyow

#ifndef TEMPLATE_TIMER_H
#define TEMPLATE_TIMER_H

#include <chrono>
#include <fstream>
#include <string>

class Timer {
 private:
  std::chrono::time_point<std::chrono::system_clock> begin_time;
  std::chrono::time_point<std::chrono::system_clock> end_time;
  double elapsed_time;
  bool running = false;

 public:
  void start() {
    begin_time = std::chrono::system_clock::now();
    running = true;
  }

  void end() {
    end_time = std::chrono::system_clock::now();
    running = false;
  }

  double elapsed() {
    if (running) {
      end();
    }
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                       end_time - begin_time)
                       .count();
    return elapsed_time;
  }

  void log(std::string filename) {
    std::ofstream fout(filename, std::ios::app);
    fout << elapsed() << std::endl;
    fout.close();
  }

  void unset() {
    elapsed_time = 0;

  }
};

#endif  // TEMPLATE_TIMER_H
