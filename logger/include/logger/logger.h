#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>

#ifndef LOGGER
#define LOGGER
class LogLevel {
public:
  virtual LogLevel &operator<<(std::string msg) = 0;
  virtual LogLevel &operator<<(int msg) = 0;
  virtual LogLevel &operator<<(double msg) = 0;
  virtual void
  setLevelOutput(std::initializer_list<std::ostream *> streams) = 0;
  virtual void off() = 0;
  virtual void on() = 0;
  virtual ~LogLevel() = default;
};

class Logger {
public:
  virtual void addLogLevel(LogLevel &level, std::string name,
                           std::string prev) = 0;

  virtual void addLogLevel(LogLevel &level, std::string name) = 0;

  virtual void setLogLevel(std::string level) = 0;

  virtual ~Logger() = default;
};
#endif // !LOGGER
