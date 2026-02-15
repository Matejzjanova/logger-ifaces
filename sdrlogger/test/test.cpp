#include "sdrlogger/sdrlogger.h"
#include "gtest/gtest.h"

class TestLoggerF : public ::testing::Test {
protected:
  BaseLogger &logger = BaseLogger::get();
  ColourLogLevel RedLevel = ColourLogLevel("31;1;4");
  ColourLogLevel OtherLevel = ColourLogLevel("42;1;4");
  ColourLogLevel DebugLevel = ColourLogLevel("31;1;4", "DEBUG");
  ColourLogLevel blueLogLevel = ColourLogLevel("34;1;4", "WARN BLUE");
};

TEST(TestLogger, TestLoggerCreate) { BaseLogger &logger = BaseLogger::get(); }

TEST(TestLogger, TestCreateLevel) {
  ASSERT_NO_THROW(ColourLogLevel RedLevel("31;1;4"));
  ASSERT_NO_THROW(ColourLogLevel AnotherLevel("40;1;4"));
}
TEST_F(TestLoggerF, TestAddLevel) {
  ASSERT_NO_THROW(logger.addLogLevel(RedLevel, "Warn"));
}
TEST_F(TestLoggerF, TestGiveMeLevel) {
  ASSERT_NO_THROW(logger.addLogLevel(RedLevel, "Warn"));
  ASSERT_NO_THROW(logger("Warn"));
}
TEST_F(TestLoggerF, TestPrint) {
  ASSERT_NO_THROW(logger.addLogLevel(RedLevel, "Warn"));
  ASSERT_NO_THROW(logger("Warn") << "Smth " << 12);
}
TEST_F(TestLoggerF, TestPrintTwoLevels) {
  ASSERT_NO_THROW(logger.addLogLevel(RedLevel, "Warn"));
  ASSERT_NO_THROW(logger.addLogLevel(OtherLevel, "Info"));
  ASSERT_NO_THROW(logger("Warn") << "Smth " << 12 << "\n");
  ASSERT_NO_THROW(logger("Info") << "Now INFO" << "\n");
}

TEST_F(TestLoggerF, TestLevelOrder) {
  ASSERT_NO_THROW(logger.addLogLevel(blueLogLevel, "Blue"));
  ASSERT_NO_THROW(logger.addLogLevel(DebugLevel, "Debug", "Blue"));

  ASSERT_NO_THROW(logger.setLogLevel("Debug"));
  ASSERT_NO_THROW(logger("Debug") << "Rome fell in " << 456 << "\n");
  ASSERT_NO_THROW(logger("Blue")
                  << "Caesar died in " << 44 << " B. C." << "\n");
  ASSERT_NO_THROW(logger.setLogLevel("Blue"));
  ASSERT_NO_THROW(logger("Blue")
                  << "Ivan the Terrible died in " << 15.84 << "\n");
}
TEST_F(TestLoggerF, TestEndl) {
  ASSERT_NO_THROW(logger.addLogLevel(blueLogLevel, "Blue"));

  ASSERT_NO_THROW(logger.setLogLevel("Debug"));
  ASSERT_NO_THROW(logger("Debug") << "Fallout NW was out in " << 2011 << "\n");
}
TEST_F(TestLoggerF, Test5Levels) {
  ASSERT_NO_THROW(logger.init5Levels());
  ASSERT_NO_THROW(logger.setLogLevel("ERROR"));
  ASSERT_NO_THROW(logger("DEBUG") << "shit\n");
  ASSERT_NO_THROW(logger("INFO") << "info shit\n");
  ASSERT_NO_THROW(logger("ERROR") << "terrible shit\n");
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
// TEST_F(TestLogger, TestLoggerLog) {
//   BaseLogger *logger = BaseLogger.get();
//   logger.level("Info") << "Gay" << "sex" << 5;
// }
// TEST_F(TestLogger, TestLoggerFilter) {
//   BaseLogger *logger = BaseLogger.get();
//   logger.level("Info") << "Gay" << "sex" << 5;
//   logger.setLogLevel("Debug");
//   logger.level("Info") << "Gay" << "sex" << 5;
//   logger.level("Info") << "Gay" << "debug" << 5;
// }
//
// TEST_F(TestLogger, TestAddLogLevel) {
//   BaseLogger *logger = BaseLogger.get;
//   ColourLogLevel *greenLevel = new ColourLogLevel("0FFFFF");
//   logger->addLogLevel(greenLevel, "Green");
//   Logger.level("Green") << "Gay"
// }
