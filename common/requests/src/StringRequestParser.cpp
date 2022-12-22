#include "StringRequestParser.hpp"
#include "nlohmann/json.hpp"


using nlohmann::json;

std::string ClientRequestStringParser::get_next_change(){
    std::string final_request;

    return final_request;
}

queue ClientRequestStringParser::make_queue(std::string request_string){
    queue changes;
    /////////////////////////////////////////////////////////
    json request_obj = json::parse(request_string);

    return changes;
}

ClientRequestStringParser::ClientRequestStringParser(): RequestStringParser() {

}

bool ClientRequestStringParser::has_changes() const {
    return !change_queue.empty();
}


std::string RoomRequestStringParser::get_next_change(){
    std::string change_description;

    return change_description;
}

queue RoomRequestStringParser::make_queue(std::string request_string){
    queue changes_descriptions;


    return changes_descriptions;
}

RoomRequestStringParser::RoomRequestStringParser(): RequestStringParser() {

}


RequestStringParser::RequestStringParser() {

}
