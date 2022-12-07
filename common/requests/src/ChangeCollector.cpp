#include "ChangeCollector.hpp"

void ChangeCollector::add_change(string description, string new_value){

}

ChangeCollector::ChangeCollector() {

}

std::unordered_map<string, string> ChangeCollector::flush() {
    return changed_fields;
}


