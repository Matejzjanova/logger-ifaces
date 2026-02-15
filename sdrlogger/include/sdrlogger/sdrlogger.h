#include "logger/logger.h"
#include <atomic>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#ifndef BASE_LOGGER_H
#define BASE_LOGGER_H

class BaseLogger : Logger {
public:
  void init5Levels();
  void setAllOutput(std::initializer_list<std::ostream *> streams);
  LogLevel &operator()(std::string levelName);
  void addLogLevel(LogLevel &level, std::string name,
                   std::string prev) override;
  void addLogLevel(LogLevel &level, std::string name) override;
  void setLogLevel(std::string level) override;
  static BaseLogger &get();

private:
  bool isInit = false;
  BaseLogger() = default;
  static BaseLogger *logger;
  std::map<std::string, LogLevel *> levels;
  std::vector<std::string> logLevelsOrder;
  std::vector<std::string>::iterator currentLevel;
  std::string currentLevelName = "\0";
};

class ColourLogLevel : public LogLevel {
public:
  void setLevelOutput(std::initializer_list<std::ostream *> streams) override;
  ColourLogLevel &operator<<(std::string msg) override;
  ColourLogLevel &operator<<(double msg) override;
  ColourLogLevel &operator<<(int msg) override;

  void off() override;
  void on() override;

  ColourLogLevel(std::string escape, std::string levelName);
  explicit ColourLogLevel(std::string escape);
  ColourLogLevel();

private:
  std::size_t operatorCounter = 0;
  const std::string escape;
  std::vector<std::ostream *> streams;
  std::vector<std::ostream *> streamsStore;
  std::string levelName = "LOG";
  std::atomic_flag flag = false;
};

#endif //! BASE_LOGGER_H
