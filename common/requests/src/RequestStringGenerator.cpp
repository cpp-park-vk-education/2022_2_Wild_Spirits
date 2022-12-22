#include "RequestStringGenerator.hpp"
#include "nlohmann/json.hpp"


std::string RequestStringGenerator::makeRequestString(std::unordered_map<std::string, std::string> changes, std::string request_header){
    using nlohmann::json;
    std::string final_request;

    return final_request;
}

RequestStringGenerator::RequestStringGenerator() {

}

std::string RequestStringGenerator::makeRequestString(std::string change, std::string header) {
    using nlohmann::json;
    json request;
    request[header] = change;
    return request.dump();
}
