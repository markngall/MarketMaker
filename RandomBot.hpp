#pragma once
#include "Bot.hpp"

class RandomBot : public Bot {

    // For generating random numbers
	static std::default_random_engine random_generator;

    public:

        // Delegate to base constructor
        RandomBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown);

        int choose_action() override;

};