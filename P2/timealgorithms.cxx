#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "json.hpp"
#include<fstream>


#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"


using namespace std;
using namespace std::chrono;

/*
class Clock{
public: 
  std::chrono::high_resolution_clock::time_point Start;
  std::chrono::high_resolution_clock::time_point End;
  double TimeTaken = std::chrono::duration<double, std::micro>(End - Start).count();
};
*/

//creating a clock function to measure time
class Clock{ 
    chrono::high_resolution_clock::time_point Start; //start point for clock
    public:
        void Reset(){ 
            Start = chrono::high_resolution_clock::now(); //timer starts
        }
        double Time(){ 
            auto End = chrono::high_resolution_clock::now(); //timer ends
            double TimeTaken = chrono::duration<double,micro>(End - Start).count();//time calculated
            return TimeTaken;//printing the time
        }
};



int main(int argc, char** argv) { //calling main function 
    Clock timer; //calling clock function
    std::ifstream file; //opening a file in c++
    file.open(argv[1]);//opening a file in c++
    
    nlohmann::json jsonObject; //declare a JSON object
    if (file.is_open()) { //checking if file is open
        file>>jsonObject; //place content from file to the json object
    }
    file.close(); // closing the file

    cout<<"Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess"<<std::endl;// sample output taken from pdf document

    int SizeOfArray=jsonObject["metadata"]["arraySize"]; //declare json object to parse metadata
    int Sample=0; //initialize as 0
    int InsertionSortTime=0; //initialize as 0
    int InsertionSortCompares=0; //initialize as 0
    int InsertionSortMemaccess=0; //initialize as 0

    int MergeSortTime=0; //initialize as 0
    int MergeSortCompares=0; //initialize as 0
    int MergeSortMemaccess=0; //initialize as 0

    int QuickSortTime=0; //initialize as 0
    int QuickSortCompares=0; //initialize as 0
    int QuickSortMemaccess=0; //initialize as 0

    for (auto itr=jsonObject.begin();itr!=jsonObject.end();++itr){   //code taken from file to go through a json object  
        vector<int> vector1; // declaring a vector
        if (itr.key()!="metadata"){ //checking if not in metadata
            for(int i=0; i<SizeOfArray;i++){ //running loop to place objects in vector

                vector1.push_back(itr.value()[i]); //pushback function to place in itr.value

            }

               
            vector<int> mergesort=vector1; //declare vector
            vector<int> insertionsort=vector1; //declare vector
            vector<int> quicksort= vector1; //declare vector

            timer.Reset(); // calling timer function
            InsertionSort(&insertionsort, InsertionSortCompares, InsertionSortMemaccess); //calling sorting function
            double TimeTaken1=timer.Time();//printing time in clock fucntion
            cout<< itr.key() << "," <<TimeTaken1<<","<<InsertionSortCompares<<"," << InsertionSortMemaccess; //output format



            timer.Reset(); // calling timer function
            MergeSort(&mergesort, MergeSortCompares, MergeSortMemaccess); //calling sorting function
            double TimeTaken2=timer.Time(); //printing time in clock fucntion

            cout<< "," << TimeTaken2<< "," << MergeSortCompares << "," <<MergeSortMemaccess; //output format

            timer.Reset(); // calling timer function
            QuickSort(&quicksort, QuickSortCompares, QuickSortMemaccess); //calling sorting function
            double TimeTaken3=timer.Time(); //printing time in clock fucntion

            cout<< "," << TimeTaken3<< "," << QuickSortCompares << "," << QuickSortMemaccess << endl; //output format
        }
    }
return 0; //returns 0 at the end of program
}
