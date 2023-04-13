#include <iostream> 
#include <fstream> 
#include <string> 
#include "json.hpp"
#include "priorityqueue.h"
#include <typeinfo> 
using namespace std; 
using json = nlohmann::json; 
 
int main(int argc, char** argv) {
    string filename = argv[1];          // Grab filename from terminal 

    ifstream file(filename);            // Open file 
    json Data = json::parse(file);      // Parse file into json Object
    
    size_t size = Data["metadata"]["maxHeapSize"];      // Grab max heap size from JSON file 
    size_t ops = Data["metadata"]["numOperations"];     // Grab # of operations from JSON file 
    
    PriorityQueue heap(size);           // Declare min heap using size from JSON file

    // For loop that iterates through JSON object
    for(auto itr = Data.begin(); itr != Data.end(); ++itr) {
        // Key is OP01, OP02, etc... 
        // Value is {key: XXXX, operation:XXXX}
        if(itr.key() != "metadata"){ // Making sure we iterate through the file contents only 

            if((Data[itr.key()]["operation"]) == "insert"){ // if insert is requested 
                Key num = Data[itr.key()]["key"];   // Grab the key from the json file using the iterator's key 
                heap.insert(num);                   // Insert the key that needs to be inserted
            }

            if((Data[itr.key()]["operation"]) == "removeMin"){ // if remove minimum is requested 
                heap.removeMin();                   // Call remove min on the heap 
            }

        }       
    }

    json result = heap.JSON();                    // Output json object defined by .JSON() constructor in class 
    result["metadata"]["maxHeapSize"] = size;     // Declaring necessary metadata value maxHeapSize in output JSON object
    result["metadata"]["numOperations"] = ops;    // Declaring necessary metadata value numOperations in output JSON object
    cout << result << endl;                       // Output JSON object
    
    return 0;   // End of program
}
