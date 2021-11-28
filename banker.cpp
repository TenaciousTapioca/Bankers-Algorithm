/**
 *  Nghia Dao
 *  Banker's Algorithm
 *  CS
 */
#include "banker.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// obtain system state data from text file
std::vector<std::vector<int>> getState(const std::string& input) {
    std::ifstream file(input);

    // check if the file opened successfully
    if (!file) {
        std::cerr << "Error(1): Unable to open " << input << " containing system state." << std::endl;
        exit(1);
    }

    // parse and insert data for ALLOCATION, MAX, and AVAILABLE into the state
    char ch;
    std::vector<int> available;
    std::vector<std::vector<int>> state;

    // fetch each character and obtain appropriate data
    while (file >> ch) {

        // fetch the ALLOCATION and MAX data of a process or the AVAILABLE data
        if (ch == '(') {
            std::vector<int> resource;
            getData(resource, file, ch);
            state.push_back(resource);
        } else if (ch == '{') {
            getData(available, file, ch);
        }

    }

    // replace each process's MAX data with NEED data
    for (int i = 1; i < state.size(); (i += 2)) {
        for (int j = 0; j < state[0].size(); ++j) {

            // NEED = MAX - ALLOCATION
            state[i][j] = state[i][j] - state[i - 1][j];
        }
    }

    // AVAILABLE data is the last element
    state.push_back(available);

    // close file
    file.close();
    return state;
}

// inserts integer data into the state
void getData(std::vector<int> &vec, std::ifstream& file, char &ch) {
    while ((ch != ')') && (ch != '}') && (file >> ch)) {

        // an integer has been found
        if ((ch >= int('0')) && (ch <= int('9'))) {

            // convert char to int
            int tempInt = ch - '0';
            file >> ch;

            // if next char is an integer, the integer is 2 digits or more long
            while ((ch >= int('0')) && (ch <= int('9'))) {
                tempInt *= 10;
                tempInt += (ch - '0');
                file >> ch;
            }
            vec.push_back(tempInt);
        }
    }
}

// determines the safe sequence if the system is safe; safe if NEED <= WORK
std::string getSafetySeq(const std::vector<std::vector<int>>& state) {
    int finishAmt = 0;
    int prevFinishAmt = 0;
    std::string safetySeq = "<";
    std::vector<int> work = state[state.size() - 1];            // Work = AVAILABLE
    std::vector<bool> finish(((state.size() - 1) / 2), false);

    for (int i = 1; i < (state.size() - 1);) {
        for (int j = 0; ((j < state[0].size()) && !finish[(i - 1) / 2]); ++j) {

            // if (NEED <= WORK) is false, that process must wait
            if (state[i][j] > work[j]) {
                break;
            } else if (j == (state[0].size() - 1)) {

                // current process can be satisfied, so it's resources will be deallocated
                ++finishAmt;
                for (int k = 0; k < state[0].size(); ++k) {

                    // work += ALLOCATION
                    work[k] += state[i - 1][k];
                }

                finish[(i - 1) / 2] = true;
                safetySeq += char(((i - 1) / 2) + '0');
                if (finishAmt != finish.size()) { safetySeq += ", "; } 
                else { safetySeq += '>'; }
            }
        }

        i += 2;
        // if finishAmt == prevFinishAmt after one full traversal of the state, the system is unsafe
        if ((i > (state.size() - 1)) && (prevFinishAmt == finishAmt)) {
            std::cerr << "Error(2): This system state has no safe sequence." << std::endl;
            exit(2);
        } else if ((i > (state.size() - 1)) && (prevFinishAmt != finishAmt)) {    // reset and attempt the search again
            i = 1;
            prevFinishAmt = finishAmt;
        } else if (finishAmt == finish.size()) {
            return safetySeq;
        }
    }

    // if invalid system state is given, exit with error
    std::cerr << "Error(3): Invalid system state. Make sure the input file has the correct format.";
    exit(3);
}