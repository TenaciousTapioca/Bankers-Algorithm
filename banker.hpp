/**
 *  Nghia Dao
 *  Banker's Algorithm
 *  CS
 */

#ifndef BANKER_HPP
#define BANKER_HPP

#include <vector>
#include <fstream>

std::vector<std::vector<int>> getState(const std::string&);
void getData(std::vector<int>&, std::ifstream&, char&);
std::string getSafetySeq(const std::vector<std::vector<int>>&);

#endif