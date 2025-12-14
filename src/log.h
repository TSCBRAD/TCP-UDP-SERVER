#ifndef LOG_H
#define LOG_H


#include <iostream>
#include <functional>
#include <string_view>
#include <source_location>


extern const std::function<void(std::string_view, const std::source_location&)> log_message;

inline void log(std::string_view message, const std::source_location& location = std::source_location::current()) {
    log_message(message, location);
}

#endif
