#include "StringRequestParser.hpp"



std::string ClientRequestStringParser::get_next_change(){
    std::string final_request;

    return final_request;
}

queue ClientRequestStringParser::make_queue(std::string request_string){
    queue requests;


    return requests;
}

ClientRequestStringParser::ClientRequestStringParser(): RequestStringParser() {

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
