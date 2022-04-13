#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <random>
#include <algorithm>
#include "RandomBot.hpp"
#include "EVBot.hpp"
#include "HypeBot.hpp"
#include "InferBot.hpp"

int main() {

    int settlement_val = 0, lower_limit, upper_limit, num_public, num_bots, max_trades;
    std::vector<int> public_nums, positions;
    std::vector<double> balances;
    std::vector<Bot*> bots;

    // For generating random numbers
    // Random seed is based on the current time
	std::default_random_engine random_generator{(unsigned int) time(0)};

    // Ask of user input to configure game
    std::cout << std::endl << "Welcome to Market Making Simulator!" << std::endl << std::endl;
    std::cout << "Each player will be given an integer in a specified range (inclusive)." << std::endl << std::endl;
    std::cout << "What is the lower limit of the range?" << std::endl;
    std::cin >>  lower_limit;
    std::cout << "What is the upper limit of the range?" << std::endl;
    std::cin >>  upper_limit;
    std::cout << "How many public numbers do you want?" << std::endl;
    std::cin >> num_public;
    std::cout << "How many bots do you want?" << std::endl;
    std::cin >> num_bots;
    std::cout << "What is the maximum number of trades per round? The cap is 100." << std::endl; 
    std::cin >> max_trades;

    // Force round to end after 100 trades
    if (max_trades > 100) {
        max_trades = 100;
    }

    // Store public information (balances, positions)
    for (unsigned int i = 0; i < num_bots+1; ++i) {
        balances.push_back(0);
        positions.push_back(0);
    }

    // Get player's number
    std::uniform_int_distribution<int> distribution(lower_limit, upper_limit);
    int num = distribution(random_generator);
    settlement_val += num;
    std::cout << std::endl << "Your number is: " << num << std::endl;

    // Initialise bots and get their numbers
    int type;
    std::uniform_int_distribution<int> select_dist(1, 4);
    for (int i = 0; i < num_bots; ++i) {
        num = distribution(random_generator);
        settlement_val += num;
        type = select_dist(random_generator);
        if (type == 1) {
            bots.push_back(new RandomBot(i, num, lower_limit, upper_limit, num_public, num_bots));
        } else if (type == 2) {
            bots.push_back(new EVBot(i, num, lower_limit, upper_limit, num_public, num_bots));
        } else if (type == 3) {
            bots.push_back(new HypeBot(i, num, lower_limit, upper_limit, num_public, num_bots));
        } else if (type == 4) {
            bots.push_back(new InferBot(i, num, lower_limit, upper_limit, num_public, num_bots));
        }
    }

    // Roll public numbers in advance
    for (unsigned int i = 0; i < num_public; ++i) {
        num = distribution(random_generator);
        settlement_val += num;
        public_nums.push_back(num);
    }

    std::cout << "There'll be " << num_public+1 << " rounds." << std::endl << std::endl;

    // Declare variables relevant to main game loop
    int num_trades = 0, bot, guess;
    std::array<double, 2> market;
    std::array<double, 3> trade = {0, 0, 0};
    std::vector<int> actions, active_bots;
    std::vector<std::array<double, 3>> history;
    std::string side;

    // Main game loop
    unsigned int i = 0; 
    while (i < num_public+1) {

        std::cout << "Round " << i+1 << std::endl << std::endl;
        
        // Send new public number to bots at the start of each round (except Round 1)
        if (i != 0) {
            std::cout << "The new public number is: " << public_nums[i-1] << std::endl;
            for (unsigned int j = 0; j < num_bots; ++j) {
                bots[j]->add_public_num(public_nums[i-1]);
            }
        }

        // Trading
        for (unsigned int k = 0; k < max_trades; ++k) {

            // Reset active_bots and actions
            active_bots = {};
            actions = {};

            // Ask for market
            std::cout << "Please make a market." << std::endl;
            std::cout << "What is your bid?" << std::endl;
            std::cin >> market[0];
            std::cout << "What is your ask?" << std::endl;
            std::cin >> market[1];

            // Send current observation (market, positions, balances, historical trades) to bots
            // Get decisions and choose one at random (eventually, according to bot speed)
            for (unsigned int j = 0; j < num_bots; ++j) {
                bots[j]->set_info(market, positions, balances, history);
                
                actions.push_back(bots[j]->choose_action());
                if (actions[j] != 0) {
                    active_bots.push_back(j);
                }
            }

            // Process trade and update positions/balances
            if (active_bots.size() > 0) {

                // Choose bot that trades
                std::uniform_int_distribution<int> distribution(0, active_bots.size()); // Might keep choosing the same number
                bot = active_bots[distribution(random_generator)];

                // Process trade
                trade[0] = actions[bot];
                if (trade[0] == 1) {
                    side = " buys ";
                    trade[1] = market[1];
                } else if (trade[0] == -1) {
                    side = " sells ";
                    trade[1] = market[0];
                }

                // Update positions/balances
                positions[bot] += trade[0];
                balances[bot] -= trade[0] * trade[1];

                // Update history
                trade[2] = bot;
                history.push_back(trade);

                // Player's position/balance is at the back
                positions.back() -= trade[0];
                balances.back() += trade[0] * trade[1];
                
                std::cout << std::endl << "Bot " << bot+1 << side << "at " << trade[1] << "." << std::endl << std::endl;

                ++num_trades;

            } else {
                std::cout << std::endl << "Nobody wants to trade." << std::endl;
                break;
            }
        }
        std::cout << "That was the final trade of that round." << std::endl << std::endl;
        ++i;
    }

    // Settle contracts
    for (unsigned int i = 0; i < num_public+1; ++i) {
        balances[i] += positions[i] * settlement_val;
    }

    // Quiz user
    std::cout << "What is your position?" << std::endl;
    std::cin >> guess;
    if (guess == positions.back()) {
        std::cout << "That is correct!" << std::endl << std::endl;
    } else {
        std::cout << "That is incorrect. Your final position is " << positions.back() << "." << std::endl << std::endl;
    }

    // Output results
    std::cout << "The settlement value is " << settlement_val << "." << std::endl;
    std::cout << "You made " << balances.back() << "." << std::endl << std::endl;
    std::cout << "The highest performing bot was Bot " << std::max_element(balances.begin(), balances.end()-1) - balances.begin() + 1 << ". ";
    std::cout << "It made " << *std::max_element(balances.begin(), balances.end()-1) << ". " << std::endl << std::endl;

    return 0;
}