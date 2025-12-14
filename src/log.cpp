#include "log.h"

// Define the lambda and assign it to log_message
const std::function<void(std::string_view, const std::source_location&)> log_message = 
    [](std::string_view message, const std::source_location& location = std::source_location::current()) {
                std::cout << "LOG: " << location.file_name() << " | " << location.line() << " | "
                                      << location.function_name() << " | " << message << "\n";
                    };

