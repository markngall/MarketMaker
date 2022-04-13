#include "RandomBot.hpp"

// Random seed is based on the current time
std::default_random_engine RandomBot::random_generator{(unsigned int) time(0)};
std::uniform_int_distribution<int> distribution(-1, 1);

RandomBot::RandomBot(int& id, int& private_num, int& lower_limit, int& upper_limit, int& num_public, int& num_bots)
: Bot(id, private_num, lower_limit, upper_limit, num_public, num_bots)
{}

int RandomBot::choose_action() {
    return distribution(random_generator);
}

