/**
 *  Nghia Dao
 *  Banker's Algorithm
 *  CS
 */
#include "banker.hpp"
#include <iostream>

int main() {
    std::string n;
    std::cout << "Enter txt file name to load the system state: ";
    std::cin >> n;
    
    // obtain the system state
    std::vector<std::vector<int>> state = getState(n);

    // obtain the safe sequence
    std::string safetySeq = getSafetySeq(state);

    std::cout << "The safe sequence of the given system state is: " << safetySeq << std::endl;
    /*
    // printing test
    std::cout << "System State Size is: " << state.size() << std::endl;
    std::cout << "Amount of resource types: " << state[0].size() << std::endl;
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state[0].size(); ++j) {
            std::cout << state[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
}