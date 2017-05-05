#ifndef TEAMSTRIKE_PARSER_H
#define TEAMSTRIKE_PARSER_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>


class parser {
public:
    parser(std::string file);
    parser();

    std::string get_name();
    float get_volume();
    void set_name(std::string curr_name);
    void set_volume(float curr_volume);
    std::string name_file;
private:

    boost::property_tree::ptree doc;

    std::string name;
    std::string music_volume;
};



#endif //TEAMSTRIKE_PARSER_H