#pragma once
#include <deque>
#include <string>
#include <tuple>


class InterlayerBuffer{
public:
    InterlayerBuffer():changes_buffer(), changes_flag(false), apply_flag(false) {

    }
    void setChanges(std::deque<std::tuple<std::string, std::string>> changes){
        for(auto change: changes){
            changes_buffer.emplace_back(std::get<0>(change), std::stoll(std::get<1>(change)));
        }
        setApplyFLag();
    }
    std::pair<std::string, long long> getNextChange(){
        std::pair<std::string, long long> change;
        change = changes_buffer.front();
        changes_buffer.pop_front();
        if (changes_buffer.empty()){
            apply_flag = false;
        }
        return change;
    }

    bool hasUnseenChanges() const{
        return apply_flag;
    }
    bool hasUnappliedChanges() const{
        return changes_flag;
    }
    void setApplyFLag(){
        apply_flag = true;
    }
    void setChangesFlag(){
        changes_flag = true;
    }
    void setUpToDate(){
        changes_flag = false;
    }
private:
    std::deque<std::pair<std::string, long long>> changes_buffer;
    //Flags for client check
    bool changes_flag;
    bool apply_flag;
};