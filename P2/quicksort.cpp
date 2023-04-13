// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"


void QuickSort(std::vector<int>* numbers, int& compare, int&MemAccess) { //added compare and memory access parameters to the function heading
   MemAccess = 0; 
   compare = 0; 
   QuickSortRecurse(numbers, 0, numbers->size() - 1, compare, MemAccess);//added compare and memory access parameters to the function heading
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& compare, int&MemAccess) {//added compare and memory access parameters to the function heading
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */

   j = Partition(numbers, i, k, compare, MemAccess); //added compare and memory access parameters to the function heading
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j, compare, MemAccess); //added compare and memory access parameters to the function heading
   QuickSortRecurse(numbers, j + 1, k, compare, MemAccess);//added compare and memory access parameters to the function heading
   
   return;
}

int Partition(std::vector<int>* numbers, int i, int k,int& compare, int&MemAccess) { //added compare and memory access parameters to the function heading
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = (*numbers)[midpoint];

   MemAccess=MemAccess+1;//incrementing memaccess value by 1

   l = i;
   h = k;
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while ((*numbers)[l] < pivot) {
         compare++; //inrementing value by 1
         MemAccess++;// incrementing value by 1
         ++l;
      }
      compare++; //increment outside loop
      MemAccess++;// incrementing outside of loop
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < (*numbers)[h]) {
         compare++; //incrementing
         MemAccess++;//increment 
         --h;
      }
      compare++; //increment outside loop
      MemAccess++;//increment outside loop

      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = (*numbers)[l];
         (*numbers)[l] = (*numbers)[h];
         (*numbers)[h] = temp;
         MemAccess=MemAccess+4; //incrementing memory by 4
         
         ++l;
         --h;
      }
   }
   
   return h;
}