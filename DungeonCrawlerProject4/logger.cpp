#include "logger.h"

logging::Logger::Logger(const std::string &fname) {
  m_file.open(fname);
  levels[0] = "ERROR";
  levels[1] = "WARN";
  levels[2] = "INFO";

  if (!m_file.is_open()){
    throw std::runtime_error("Log file could not be opened!");
      }
  else {
      log(Level::INFO , "STARTING LOGGING SYSTEM");
      }
}

logging::Logger::~Logger() {
    log(Level::INFO , "STOPPED LOGGING SYSTEM");
  m_file << flush;
  m_file.close();
}
