/** main.cpp
 *  Nghia Dao
 *  Banker's Algorithm
 *  CS33211
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
}
