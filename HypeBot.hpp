#pragma once
#include "Bot.hpp"

class HypeBot : public Bot {

    public:

        // Delegate to base constructor
        HypeBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown);

        int choose_action() override;

};