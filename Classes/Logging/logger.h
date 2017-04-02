#ifndef LOGGER_H
#define LOGGER_H

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <ctime>

#define FILE_NAME_ERROR "error.log"
#define FILE_NAME_EVENT "event.log"

void log_error(const char* file, int line, const char *error);
void log_event(const char* file, int line, const char *event);
void log_exception_error(const char* file, int line, std::exception &error);


void print_error(const char* file, int line, const char *error);
void print_event(const char* file, int line, const char *event);
void print_exception_error(const char* file, int line, std::exception &error);

#endif // LOGGER_H
