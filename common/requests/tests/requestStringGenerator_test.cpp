#include "gtest/gtest.h"
#include "RequestStringGenerator.hpp"
#include "ActionHandler.hpp"
#include "Action.hpp"


TEST(requestTest, requestTransformationsTest){


    RequestStringGenerator generator;
    ActionHandler handler;

    std::string action_string = handler.actionString()
}