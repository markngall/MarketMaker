#pragma once
#include "Bot.hpp"

class InferBot : public Bot {

    double m_theo;

    public:

        // Delegate to base constructor
        InferBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_public, int& num_bots);

        int choose_action() override;

        // Adding functionality to base class method
        void add_public_num(int& public_num);

        // Updates theo with a new die roll
        void update_theo(int& num);

};