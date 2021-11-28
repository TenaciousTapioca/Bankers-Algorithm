/** banker.hpp
 *  Nghia Dao
 *  Banker's Algorithm
 *  CS33211
 */

#ifndef BANKER_HPP
#define BANKER_HPP

#include <vector>
#include <fstream>

std::vector<std::vector<int>> getState(const std::string&);     // obtains the state given by the text file
void getData(std::vector<int>&, std::ifstream&, char&);         // parses text file so that the state is organized
std::string getSafetySeq(const std::vector<std::vector<int>>&); // determines safe sequence if possible

#endif
