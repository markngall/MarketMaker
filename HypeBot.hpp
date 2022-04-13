#pragma once
#include "Bot.hpp"

class HypeBot : public Bot {

    public:

        // Delegate to base constructor
        HypeBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_public, int& num_bots);

        int choose_action() override;

};