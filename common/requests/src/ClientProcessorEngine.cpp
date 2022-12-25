#include "ClientProcessorEngine.hpp"
#include "Headers.hpp"
#include "deque"


string ClientProcessorEngine::getRequestString(std::string action_string, LM::Action::Type header) {
    std::string final_request;
    HeaderSerial serializer;
    final_request = generator -> makeRequestString(action_string ,serializer(header));
    return final_request;
}

setter_queue ClientProcessorEngine::getSetterQueue(string request){
    
    return parser -> make_queue(request);
}

std::deque<nlohmann::json> ClientProcessorEngine::getAnotherSetterQueue(string request_string){
    using queue = std::deque<nlohmann::json>;
    using nlohmann::json;
    queue changes;
    std::cout << "trying to parse in make_queue : " << request_string << std::endl;
    json request_obj = json::parse(request_string);
    HeaderSerial ser;
    // json setters_obj = json::parse(std::string(request_obj[ser(Header::apply_request)]));
    json setters_obj = request_obj;
    for(auto& [key, val] : setters_obj.items()){
        
        if (val != NULL){
            // std::cout << "val printing:  " << val << std::endl;
            // std::cout << "val items printing:  " << val.items() << std::endl;
            // for (auto& obj : val){
            //     for (auto& element : obj.items()){
            //         std::cout << "Got change object :  " << element << std::endl;
            //         changes.push_back(element);
            //     }
            // }
            for(auto& obj : val){
                changes.push_back(obj);
            }
        }
        
    }
    return changes;
}

ClientProcessorEngine::ClientProcessorEngine(): generator(std::make_shared<RequestStringGenerator>()), parser(std::make_shared<ClientRequestStringParser>()) {

}

string ClientProcessorEngine::getRequestString(std::string request_string, Header header) {
    HeaderSerial serializer;
    return generator->makeRequestString(request_string, serializer(header));
}

bool ClientProcessorEngine::hasChanges() const {
    return parser -> has_changes();
}

