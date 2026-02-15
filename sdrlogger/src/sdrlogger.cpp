#include "sdrlogger/sdrlogger.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

BaseLogger *BaseLogger::logger = nullptr;

BaseLogger &BaseLogger::get() {
  if (BaseLogger::logger == nullptr) {
    logger = new BaseLogger();
  }
  return *logger;
}

void BaseLogger::addLogLevel(LogLevel &level, std::string name,
                             std::string prev) {
  levels.insert(std::pair{name, &level});
  auto iter = std::find(logLevelsOrder.begin(), logLevelsOrder.end(), prev);
  logLevelsOrder.insert(iter, name);
}

void BaseLogger::addLogLevel(LogLevel &level, std::string name) {
  this->addLogLevel(level, name, "\0");
  currentLevel =
      std::find(logLevelsOrder.begin(), logLevelsOrder.end(), currentLevelName);
  if (currentLevel == logLevelsOrder.end()) {
    // std::cout << "Last level" << std::endl;
  }
}
void BaseLogger::setLogLevel(std::string name) {
  currentLevel = std::find(logLevelsOrder.begin(), logLevelsOrder.end(), name);
  currentLevelName = name;
}

LogLevel &BaseLogger::operator()(std::string name) {
  auto iter = std::find(logLevelsOrder.begin(), logLevelsOrder.end(), name);
  // if (iter != logLevelsOrder.end()) {
  //   std::cout << "Level found" << std::endl;
  // }

  if (currentLevel < iter) {
    levels.at(name)->off();
  } else {
    levels.at(name)->on();
  }
  return *levels.at(name);
}
void ColourLogLevel::off() {
  streamsStore = std::move(streams);
  this->setLevelOutput({});
}

void ColourLogLevel::on() {
  operatorCounter = 0;
  if (streams.size() == 0)
    streams = std::move(streamsStore);
}

ColourLogLevel::ColourLogLevel(std::string escape, std::string levelName)
    : escape(escape), levelName(levelName) {
  streams.push_back(&std::cout);
}

ColourLogLevel::ColourLogLevel(std::string escape) : escape(escape) {
  streams.push_back(&std::cout);
}

ColourLogLevel::ColourLogLevel() : escape("32") {
  streams.push_back(&std::cout);
}

void ColourLogLevel::setLevelOutput(
    std::initializer_list<std::ostream *> streams) {
  this->streams.assign(streams);
}

ColourLogLevel &ColourLogLevel::operator<<(std::string msg) {
  // if (streams.size() == 0) {
  //   // std::cout << "where is stream" << std::endl;
  //   return *this;
  // }
  std::time_t time = std::time(nullptr);
  if (operatorCounter == 0) {
    for (std::ostream *stream : streams) {
      *stream << "\033[" << escape << "m"
              << "[" << levelName << "] "
              << std::put_time(std::localtime(&time), "%c") << " \033[0m";
    }
  }
  operatorCounter++;
  for (std::ostream *stream : streams) {
    *stream << "\033[" << escape << "m" << msg << "\033[0m";
  }
  return *this;
}

ColourLogLevel &ColourLogLevel::operator<<(double msg) {
  for (std::ostream *stream : streams) {
    *stream << "\033[" << escape << "m" << msg << "\033[0m";
  }
  return *this;
}

ColourLogLevel &ColourLogLevel::operator<<(int msg) {

  flag.wait(true);
  flag.test_and_set();
  for (std::ostream *stream : streams) {
    *stream << "\033[" << escape << "m" << msg << "\033[0m";
  }

  flag.clear();
  return *this;
}

void BaseLogger::init5Levels() {
  if (!isInit) {
    isInit = true;
    ColourLogLevel *error = new ColourLogLevel("31;2;4", "ERROR");
    logger->addLogLevel(*error, "ERROR");
    ColourLogLevel *warn = new ColourLogLevel("33;2;4", "WARN");
    logger->addLogLevel(*warn, "WARN", "ERROR");
    ColourLogLevel *info = new ColourLogLevel("32;2;4", "INFO");
    logger->addLogLevel(*info, "INFO", "WARN");
    ColourLogLevel *debug = new ColourLogLevel("37;2;4", "DEBUG");
    logger->addLogLevel(*debug, "DEBUG", "INFO");
  }
}
