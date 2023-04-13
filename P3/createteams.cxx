#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 
#include "json.hpp"
#include "teamdata.h"
#include "priorityqueue.h"

using namespace std; 
using json = nlohmann::json; 

int main(int argc, char** argv){
    string filename = argv[1];

    TeamData tData(filename);                   // Create TeamData class that stores all the teams in a double vector
    
    int players = tData.numPlayers();           // Stores # of players given in JSON file
    int dictSize = tData.arraySize();           // Stores # of team pairs given by dictionary size of teamStats in JSON file
    
    PriorityQueue heap(dictSize);               // Create a priority heap using the # of teams
    
    // Nested for loop to iterate through all possible combos of teams
    for(int i = 0; i < players; i++){
        for(int j = 0; j < players; j++){
            if(i != j){                                 // Ignoring case of a team w/ the same player 
                float x = tData.winPercentages(i,j);    // Grabbing the win percentage of a team 
                                                        // i is player 1, j is player 2
                
                // This if statement exists to filter out the case of a win percentage being 0 which means
                // a team consisting of those specific players does NOT exist
                if (x != 0){                                    
                    float y = abs(x - 50);                              // Changing the win percentage to the distance it is from 50% 
                    KeyValuePair kv = make_pair(y, make_pair(i,j));     // Creating a key value pair of the new percentage and the two players
                    heap.insert(kv);                                    // Inserting key value pair into heap
                }
            }  
        }
    }

    vector<bool> vect(players, false);    // Initializing bool map vector to figure out which players have been chosen already
    json output;                          // Declaring JSON output object 

    int a = 0;                            // Integer to use as a JSON dictionary position in output file

    // For loop that iterates for how many teams there are given by 'dictSize' 
    // The purpose is to work with the heap to extract teams closest to 50% (top of heap)
    // and rid of duplicate teams with the already chosen players. 
    for(int i = 0; i < dictSize-1; i++){

        KeyValuePair removedTeam = heap.min();          // Take a look at the current minimum node (containing the closest to 50% team)
        int player1 = (removedTeam.second).first;       // Grab the node's first player
        int player2 = (removedTeam.second).second;      // Grab the node's second player
        
        // If statement that checks to make sure the current players in the node we are looking at haven't 
        // been chosen already. If they haven't been chosen, enter the if statement. 
        if(vect[player1] == false && vect[player2] == false){
            output["teams"][a] = removedTeam.second;    // Add current team to the output JSON object 
            vect[player1] = true;                       // Declare player 1 as selected
            vect[player2] = true;                       // Declare player 2 as selected 
            heap.removeMin();                           // Remove node we just used
            a++;                                        // Increment so we can add the next team in the next position in output JSON object
        }else{  // If current node contains players that have been chosen already 
            heap.removeMin();                           // Remove node w/ already chosen players
        }

    } // end for

    cout << output << endl;             // Output the JSON output object


    return 0;                           // End of Code
}
