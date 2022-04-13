#include "Bot.hpp"

Bot::Bot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown) 
:
m_id(id),
m_private_num(private_num),
m_sum_nums(private_num),
m_limits({lower_limit, upper_limit}),
m_num_unknown(num_unknown)
{}

void Bot::set_public_num(int& public_num) {
    m_public_nums.push_back(public_num);
    m_sum_nums += public_num;
}

void Bot::set_info(std::array<double, 2>& market, std::vector<int>& positions, std::vector<double>& balances, std::vector<std::array<double, 3>>& history) {
    m_market = market;
    m_positions = positions;
    m_balances = balances;
    m_history = history;
}