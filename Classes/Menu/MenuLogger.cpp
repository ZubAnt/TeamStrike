#include "MenuLogger.h"
#include <ctime>
#include <iostream>

MenuLogger::MenuLogger(const std::string fname_err, const std::string fname_event):
    _fname_err(fname_err),
    _fname_evn(fname_event)
{
    _stream_error.open(_fname_err, std::fstream::out | std::fstream::app);
    _stream_event.open(_fname_evn, std::fstream::out | std::fstream::app);

    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&(now));

    _stream_error << "Start logging" << asctime(timeinfo) << std::endl;
    _stream_event << "Start logging" << asctime(timeinfo) << std::endl;
}

MenuLogger::~MenuLogger()
{
    _stream_error << "Stop logging" << std::endl << std::endl;
    _stream_event << "Stop logging" << std::endl << std::endl;

    _stream_error.close();
    _stream_event.close();
}

void MenuLogger::log_error(const char *text, const char *file, int line)
{
    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&(now));

    _stream_error << asctime(timeinfo) << std::endl;
    _stream_error << "ERROR: " << text << "; FILE = " << file << "; LINE = " << line << std::endl << std::endl;
}

void MenuLogger::log_event(const char *text)
{
    _stream_event << text << std::endl;
}
