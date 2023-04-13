// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
using namespace std;

void InsertionSort(std::vector<int>* numbers, int& compare, int&MemAccess) { //added compare and memory access parameters to the heading
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   compare = 0; //initialize to be 0
   MemAccess = 0;  //initialize to be 0
   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (++compare && ++MemAccess && ++MemAccess && (*numbers)[j] < (*numbers)[j - 1]) ){ //loop goes through compare and memory access and gets incremented and loop runs
         
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         MemAccess++; //incrementing value
         (*numbers)[j] = (*numbers)[j - 1];
         MemAccess=MemAccess+2; //incrementing value
         (*numbers)[j - 1] = temp;
         MemAccess++; //incrementing value

         --j;
      }
   }
   
   return;
}