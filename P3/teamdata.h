#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>
#include <vector> 
using namespace std; 
class TeamData {
 public:
 	TeamData(std::string filename);
 	int numPlayers() const;
	int arraySize() const; 
 	double winPercentages(int i, int j) const { return winPercentages_[i][j]; }

 private:
	// TODO: decide the type of this variable.
	// winPercentages_;
	int numPlayers_;
	int arraySize_; // added a private variable to count the size of "teamStats" in the json file 
					// this array size is equivalent to number of teams 
	vector<vector<float>> winPercentages_; 			// 2D Vector that stores the win percentages
													// The Vector is indexed by winPercentages(player1, player2) and returns the win percentage
};  // class TeamData

#endif  // _TEAMDATA_H_