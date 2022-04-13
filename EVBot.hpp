#pragma once
#include "Bot.hpp"

class EVBot : public Bot {

    public:

        // Delegate to base constructor
        EVBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown);

        int choose_action() override;

};