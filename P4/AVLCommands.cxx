#include "AVL.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "json.hpp"
using namespace std; 
using json = nlohmann::json; 


int main(int argc, char** argv) {
    AVL tree;                           // Declare tree
    string filename = argv[1];          // Grab filename from terminal 

    ifstream file(filename);            // Open file 
    json Data = json::parse(file);      // Parse file into json Object
    
    // For loop that iterates until the JSON object ends 
    for(auto itr = Data.begin(); itr != Data.end(); ++itr) {
        if(itr.key() != "metadata"){                // Making sure we aren't in metadata because it is not applicable to our assignment
            if((Data[itr.key()]["operation"]) == "Insert"){ // if insert is requested 
                int num = Data[itr.key()]["key"];   // Grab the key from the json file using the iterator's key 
                tree.Insert(num);                   // Insert the key that needs to be inserted into AVL 
            }
        }
    } 
    json output;                        // Creating output JSON object
    output = tree.JSON();               // Calling JSON function of AVL class to convert to output JSON 
    cout << output.dump(2) << endl;     // Output to terminal 

    return 0;                           // Done 
} 