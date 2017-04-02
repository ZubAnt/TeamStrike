#include "logger.h"


void log_error(const char *file, int line, const char *error)
{
    std::fstream stream_error;
    stream_error.open(FILE_NAME_ERROR, std::fstream::out | std::fstream::app);

    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&(now));

    stream_error << "TIME: " << asctime(timeinfo)
                 << "; LINE: " << line
                 << "; ERROR: " << error
                 << " FILE: " << file
                 << std::endl;

    stream_error.close();
}

void log_event(const char *file, int line, const char *event)
{
    std::fstream stream_event;
    stream_event.open(FILE_NAME_EVENT, std::fstream::out | std::fstream::app);

    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&(now));

    stream_event << "TIME: " << asctime(timeinfo)
                 << "; LINE: " << line
                 << "; EVENT: " << event
                 << " FILE: " << file
                 << std::endl;

    stream_event.close();
}

void log_exception_error(const char *file, int line, std::exception &error)
{
    std::fstream stream_error;
    stream_error.open(FILE_NAME_EVENT, std::fstream::out | std::fstream::app);

    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&(now));

    stream_error << "TIME: " << asctime(timeinfo)
                 << "; LINE: " << line
                 << "; ERROR: " << error.what()
                 << " FILE: " << file
                 << std::endl;

    stream_error.close();
}

void print_error(const char *file, int line, const char *error)
{
    std::cout << "LINE: " << line
              << "; ERROR: " << error
              << " FILE: " << file
              << std::endl;
}

void print_event(const char *file, int line, const char *event)
{
    std::cout << "LINE: " << line
              << "; EVENT: " << event
              << " FILE: " << file
              << std::endl;
}

void print_exception_error(const char *file, int line, std::exception &error)
{
    std::cout << "LINE: " << line
              << "; ERROR: " << error.what()
              << " FILE: " << file
              << std::endl;
}
