#include "EVBot.hpp"

EVBot::EVBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_public, int& num_bots)
: Bot(id, private_num, lower_limit, upper_limit, num_public, num_bots),
m_theo(private_num + 0.5 * (lower_limit + upper_limit) * (num_bots + num_public))
{}

int EVBot::choose_action() {
    if (m_theo > m_market[1] && m_positions[m_id] < MAX_POSITION) {
        return 1;
    } else if (m_theo < m_market[0] && m_positions[m_id] > -MAX_POSITION)  {
        return -1;
    } else {
        return 0;
    }
}

void EVBot::add_public_num(int& public_num) {
    Bot::add_public_num(public_num);
    EVBot::update_theo(public_num);
}

void EVBot::update_theo(int& num) {
    m_theo += num - 0.5 * (m_limits[0] + m_limits[1]);
}

