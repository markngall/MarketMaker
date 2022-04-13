#include "EVBot.hpp"

EVBot::EVBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown)
: Bot(id, private_num, lower_limit, upper_limit, num_unknown)
{}

int EVBot::choose_action() {
    double theo = m_sum_nums + 0.5 * (m_limits[0] + m_limits[1]) * (m_positions.size() + m_num_unknown - m_public_nums.size());
    if (theo > m_market[1] && m_positions[m_id] < MAX_POSITION) {
        return 1;
    } else if (theo < m_market[0] && m_positions[m_id] > -MAX_POSITION)  {
        return -1;
    } else {
        return 0;
    }
}

