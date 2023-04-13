#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include"quicksort.h"
#include"insertionsort.h"
#include"mergesort.h"
#include"json.hpp"

int main(int argc, char* argv[]) {
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json json_object;
    if(file.is_open()){
        file >> json_object;
    }
    file.close();
    const int MAX_ARRAY_SIZE = json_object["metadata"]["arraySize"];
 
    std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTIme,QuickSortCompares,QuickSortMemaccess" << std::endl;

    // std::ofstream output("FILENAME.csv", std::ios::out);
    // if(output.is_open()){
    // output << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTIme,QuickSortCompares,QuickSortMemaccess" << std::endl;
    // }
    for (auto itr = json_object.begin(); itr != std::prev(json_object.end()); ++itr){

        std::vector<int> to_be_sorted;

        for (auto i = 0; i < MAX_ARRAY_SIZE; i++){
            to_be_sorted.push_back(itr.value()[i]);
        }
        std::vector<int> insertion_sorted = to_be_sorted;
        std::vector<int> merge_sorted = to_be_sorted;
        std::vector<int> quick_sorted = to_be_sorted;

        int insertion_compares = 0;
        int insertion_mem_access = 0;
        auto start = std::chrono::high_resolution_clock::now();
        InsertionSort(&insertion_sorted,insertion_mem_access,insertion_compares);
        auto end = std::chrono::high_resolution_clock::now();
        double insert_time = std::chrono::duration<double, std::micro>(end - start).count();


        int merge_compares = 0;
        int merge_mem_access = 0;
        start = std::chrono::high_resolution_clock::now();
        MergeSort(&merge_sorted,merge_mem_access,merge_compares);
        end = std::chrono::high_resolution_clock::now();
        double merge_time = std::chrono::duration<double, std::micro>(end - start).count();


        int quick_compares = 0;
        int quick_mem_access = 0;
        start = std::chrono::high_resolution_clock::now();
        QuickSort(&quick_sorted,quick_mem_access,quick_compares);
        end = std::chrono::high_resolution_clock::now();
        double quick_time = std::chrono::duration<double, std::micro>(end - start).count();

        std::cout << itr.key() << ',' << insert_time << ',' << insertion_compares << ',' << insertion_mem_access
                               << ',' << merge_time << ','  << merge_compares << ',' << merge_mem_access
                               << ',' << quick_time << ','  << quick_compares << ',' << quick_mem_access << std::endl;


    // if(output.is_open()){
    //     output << itr.key() << ',' << insert_time << ',' << insertion_compares << ',' << insertion_mem_access
    //                            << ',' << merge_time << ','  << merge_compares << ',' << merge_mem_access
    //                            << ',' << quick_time << ','  << quick_compares << ',' << quick_mem_access << std::endl;
    // }


        // std::cout << "=============SAMPLE START============" << sample_number << std::endl;
        // for(int x : *quick_sorted){
        //     std::cout << x << std::endl;
        //  }
        //  std::cout << "=============SAMPLE ENDED============" << std::endl;
        //  std::cout << comparison_count << " " << mem_access_count << std::endl;


    }
    
    //std::cout << new_json_object.dump(2) << std::endl;



   






    // std::ofstream output("FILENAME.csv", std::ios::out);
    // if(output.is_open()){
    //     output << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTIme,QuickSortCompares,QuicksortMemaccess" << std::endl;
    //     }
    // output.close();

return 0;
}