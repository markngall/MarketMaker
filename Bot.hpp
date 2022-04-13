#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <random>

class Bot {

    // Concerned about using protected – is the way I'm doing inheritance wrong?
    protected:

        // Add hard risk limit
        static const int MAX_POSITION = 5;

        int m_sum_nums, m_id;
        const int m_private_num, m_num_unknown;
        const std::array<int, 2> m_limits;
        std::array<double, 2> m_market;
        std::vector<int> m_positions, m_public_nums;
        std::vector<double> m_balances;
        std::vector<std::array<double, 3>> m_history;
    
    public:
    
        // Constructor
        Bot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown);

        // Pure virtual function (Bot class is abstract and cannot be instantiated)
        virtual int choose_action() = 0;

        // Gets public info from environment
        void set_info(std::array<double, 2>& market, std::vector<int>& positions, std::vector<double>& balances, std::vector<std::array<double, 3>>& history);

        void set_public_num(int& public_num);

};