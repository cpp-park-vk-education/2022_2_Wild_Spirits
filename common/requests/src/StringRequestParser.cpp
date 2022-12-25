#include "StringRequestParser.hpp"
#include "nlohmann/json.hpp"
#include "Headers.hpp"
#include "string"


using nlohmann::json;

std::string ClientRequestStringParser::get_next_change(){
    std::string final_request;

    return final_request;
}

queue ClientRequestStringParser::make_queue(std::string request_string){
    queue changes;
    /////////////////////////////////////////////////////////
    std::cout << "trying to parse in make_queue : " << request_string << std::endl;
    json request_obj = json::parse(request_string);
    HeaderSerial ser;
    // json setters_obj = json::parse(std::string(request_obj[ser(Header::apply_request)]));
    json setters_obj = request_obj;
    for(auto& [key, val] : setters_obj.items()){
        
        if (val != NULL){
            std::cout << "val printing:  " << val << std::endl;
            std::cout << "val items printing:  " << val.items() << std::endl;
            for (auto& obj : val){
                for (auto& element : obj.items()){
                    std::cout << "Got change object :  " << element << std::endl;
                    if(element.value().is_string()){
                        changes.emplace_back(std::string(key) + std::string(":") + std::string(element.key()), std::string(element.value()));
                    }
                    else{
                        changes.emplace_back(std::string(key) + std::string(":") + std::string(element.key()), std::to_string(std::size_t(element.value())));
                    }
                }
            }
        }
        
    }
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
