//
// Created by pavel on 08.05.17.
//

#include "Parser.h"
#include <string>

parser::parser(std::string file) : name_file(file) {
    boost::property_tree::read_json(name_file, doc);
    std::string name_( doc.get<std::string>("name") );
    std::string music_volume_( doc.get<std::string>("music_volume") );
    name = name_;
    music_volume = music_volume_;
}

std::string parser::get_name() {
    std::string name_( doc.get<std::string>("name") );
    return name_;
}

float parser::get_volume() {
    std::string music_volume_( doc.get<std::string>("music_volume") );
    return boost::lexical_cast<float>(music_volume_);
}

void parser::set_name(std::string curr_name) {
    name = curr_name;
    doc.put("name",name);
    write_json(name_file, doc);
}

void parser::set_volume(float curr_volume) {
    music_volume = boost::lexical_cast<std::string>(curr_volume);
    doc.put("music_volume",music_volume);
    write_json(name_file, doc);
}

parser::parser() {
    name_file = "/home/pavel/Документы/Game/TeamStrike/Classes/file.json";
    boost::property_tree::read_json(name_file, doc);
    std::string name_( doc.get<std::string>("name") );
    std::string music_volume_( doc.get<std::string>("music_volume") );
    name = name_;
    music_volume = music_volume_;
}