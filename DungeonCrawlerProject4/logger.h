/**
 * \author Michael Roth
 * \date 11.03.2020
 * \brief Logging Facility
 *
 *  This is a simple Logging Facility which writes logs to a text file.
 *
 * Logging is achieved via a template function inside the class, which takes a
 * loggable argument as parameter. This argument must have a << operator to
 * write to a stream.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
using std::ofstream;
using std::string;

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
//#include "Singleton.h"
#include <array>
using std::flush;
using std::localtime;
using std::put_time;
using std::chrono::system_clock;

namespace logging {
class Logger {

private:
    std::array<std::string,3> levels;
    ofstream m_file;
    // Explicit Construtctors are prefered to non-explicit Constructors, because they
    // prevent the compiler from performing unexpected type conversions
    // quelle : Effective_Modern_C++ - Scott Meyers
    explicit Logger(const string &fname);

public:
    enum Level {
        ERROR , WARN , INFO
    };

    // Prefer deleted functions to private/undefined ones - Item 11 - Effective_Modern_C++
    // Secondly it's essential to delete the copy functions since we need to have a singleton
    Logger(const Logger& log) = delete;
    Logger& operator =(const Logger& log) = delete;

    ~Logger();

    static Logger& Get(std::string fileName){
        static Logger Logger_Instance(fileName);
        return Logger_Instance;
    }


    template <typename T>
    void log(Level l, const T &info) {
        auto time = system_clock::to_time_t(system_clock::now());
        if (m_file.is_open() && l<3 && l>=0){
            m_file << levels[static_cast<int>(l)] << " - "<< std::put_time(std::localtime(&time), "[%F %T] ") << info << std::endl;
        }
    }


};
} // namespace logging

#endif // LOGGER_H
