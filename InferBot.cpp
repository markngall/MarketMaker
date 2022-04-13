#include "InferBot.hpp"

InferBot::InferBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown)
: Bot(id, private_num, lower_limit, upper_limit, num_unknown),
m_adjust(0)
{}

// Guesses player's number and uses it to improve its theo
int InferBot::choose_action() {
    
    // Better way is to store the theo and update it dynamically when new information arrives (could have an update_theo method)
    double theo;
    if (m_history.size() == 0) {
        theo = 0.5 * (m_market[0] + m_market[1]) + m_private_num - 0.5 * (m_limits[0] + m_limits[1]);
        m_adjust = theo - (m_sum_nums + 0.5 * (m_limits[0] + m_limits[1]) * (m_positions.size() + m_num_unknown - m_public_nums.size()));
    } else {
        theo = m_adjust + m_sum_nums + 0.5 * (m_limits[0] + m_limits[1]) * (m_positions.size() + m_num_unknown - m_public_nums.size());
    }

    if (theo > m_market[1] && m_positions[m_id] < MAX_POSITION) {
        return 1;
    } else if (theo < m_market[0] && m_positions[m_id] > -MAX_POSITION)  {
        return -1;
    } else {
        return 0;
    }
}

