#include "HypeBot.hpp"

HypeBot::HypeBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_unknown)
: Bot(id, private_num, lower_limit, upper_limit, num_unknown)
{}

int HypeBot::choose_action() {
    if (m_history.size() >= 2 && m_history[-1][0] == m_history[-2][0] != 0 && !(m_history[-1][2] == m_id && m_history[-2][2] != m_id) && (m_history[-1][0] * m_positions[m_id] < MAX_POSITION)) {
        return m_history[-1][0];
    }
    return 0;
}

