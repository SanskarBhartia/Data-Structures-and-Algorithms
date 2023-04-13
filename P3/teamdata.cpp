#include "teamdata.h"
#include <string>
#include <vector> 
#include <iostream> 
#include <fstream> 
#include <cmath> 
#include "json.hpp"

using namespace std; 
using json = nlohmann::json; 

int TeamData::numPlayers() const{
	// TODO: complete this function
    return numPlayers_; 
}

int TeamData::arraySize() const{
	// TODO: complete this function
    return arraySize_; 
}
TeamData::TeamData(string filename){
    ifstream file(filename); 

    json Data = json::parse(file);                      // JSON object w/ file data

    int size = Data["teamStats"].size();                // Declare # of teams in 'size'
    arraySize_ = size;                                  // Give value of # of teams to private variable of TeamData class
                                                        // This is done to give access to that data in createteams.cxx
    
    numPlayers_ = Data["metadata"]["numPlayers"];       // Get # of players from JSON file and set private variable of TeamData to that
    
    int p1, p2; // Integers storing players 1 and 2
    float perc; // Float storing the win percentage of said players

    // For loop that declares our 2D vector w/ empty values of 0.0
    //      Note: Without this, get segmentation fault when trying to fill vector
    for(int x = 0; x < numPlayers_; x++){
        vector<float> empty(numPlayers_, 0.0);          // Declare a vector of 'empty' float values 
        
        winPercentages_.push_back(empty);               // Push float vector into 2D vector
    }

    // For loop that iterates through all teams and stores their data into our 
    // private 2D vector. 'size' is the size of "teamData" i.e. the # of total team combos in the JSON file
    for(int i = 0; i < size; i++){
        p1 = Data["teamStats"][i]["playerOne"];             // Player 1's number
    
        p2 = Data["teamStats"][i]["playerTwo"];             // Player 2's number
         
        perc = Data["teamStats"][i]["winPercentage"];       // Player 1 and 2's combined win percentage
        
        winPercentages_[p1][p2] = perc;                     // Insert into 2D vector
    }
}
