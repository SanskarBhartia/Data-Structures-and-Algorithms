// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<int>* numbers, int& compare, int&MemAccess) { //added compare and memory access parameters to the function heading
   int i = 0; 
   compare = 0; //initialize as 0
   MemAccess = 0; //initialize as 0
   MergeSortRecurse(numbers, 0, numbers->size() - 1, compare, MemAccess); //added compare and memory access parameters to the function heading
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& compare, int&MemAccess) { //added compare and memory access parameters to the function heading
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j,compare,MemAccess); //added compare and memory access parameters to the function heading
      MergeSortRecurse(numbers, j + 1, k,compare,MemAccess); //added compare and memory access parameters to the function heading
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, compare, MemAccess); //added compare and memory access parameters to the function heading
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int&compare, int& MemAccess) { //added compare and memory access parameters to the function heading
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   
   while (leftPos <= j && rightPos <= k) {
      MemAccess=MemAccess+2;// incrementing value by 2
      compare++; //gets incremented by 1 every time loop runs instead of calling it in each loop

      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++leftPos;
         MemAccess=MemAccess+2; //incrementing values
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         ++rightPos;
         MemAccess=MemAccess+2; //incrementing values
      


      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;
      MemAccess=MemAccess+2; //incrementing values

   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;
      MemAccess=MemAccess+2; //incrementing values
      
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      MemAccess=MemAccess+2; //incrementing values
   }
}