#include "InferBot.hpp"

InferBot::InferBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_public, int& num_bots)
: Bot(id, private_num, lower_limit, upper_limit, num_public, num_bots),
m_theo(private_num + 0.5 * (lower_limit + upper_limit) * (num_bots + num_public))
{}


int InferBot::choose_action() {
    
    // At the start, guess player's number (assume it's the mid) and use it to improve theo
    if (m_history.size() == 0) {
        m_theo = 0.5 * (m_market[0] + m_market[1]) + m_private_num - 0.5 * (m_limits[0] + m_limits[1]);
    }

    if (m_theo > m_market[1] && m_positions[m_id] < MAX_POSITION) {
        return 1;
    } else if (m_theo < m_market[0] && m_positions[m_id] > -MAX_POSITION)  {
        return -1;
    } else {
        return 0;
    }
}

void InferBot::add_public_num(int& public_num) {
    Bot::add_public_num(public_num);
    InferBot::update_theo(public_num);
}

void InferBot::update_theo(int& num) {
    m_theo += num - 0.5 * (m_limits[0] + m_limits[1]);
}


