#ifndef MENUERROR_H
#define MENUERROR_H

#include <fstream>

class MenuLogger
{
public:

    MenuLogger(const std::string fname_err, const std::string fname_event);
    ~MenuLogger();
    void log_error(const char *text, const char *file, int line);
    void log_event(const char *text);

private:

    const std::string _fname_err;
    const std::string _fname_evn;
    std::ofstream _stream_error;
    std::ofstream _stream_event;
};

#endif // MENUERROR_H
