#pragma once
#include "Bot.hpp"

class InferBot : public Bot {

    double m_adjust;

    public:

        // Delegate to base constructor
        InferBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown);

        int choose_action() override;

};