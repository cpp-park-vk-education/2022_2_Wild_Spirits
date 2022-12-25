#include "ClientProcessorEngine.hpp"
#include "Headers.hpp"


string ClientProcessorEngine::getRequestString(std::string action_string, LM::Action::Type header) {
    std::string final_request;
    HeaderSerial serializer;
    final_request = generator -> makeRequestString(action_string ,serializer(header));
    return final_request;
}

setter_queue ClientProcessorEngine::getSetterQueue(string request){
    
    return parser -> make_queue(request);
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

