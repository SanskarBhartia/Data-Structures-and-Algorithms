#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	// TODO: complete this function
    size_++;                // Increase size for new node 
    nodes_[size_] = kv;     // Set the new node to key value pair 
    heapifyUp(size_);       // Heapify the node up to sort it in the min heap 
}


KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
    return nodes_[ROOT];    // Return root node which is minimum in min heap 
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
    KeyValuePair x = min();         // Store current minimum 
    removeNode(ROOT);               // Remove the min node which is at root 
    return x;                       // Return the min that got removed
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
    return size()==0;               // Return true if size() returns 0 
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
    return size_;           // Return size of heap 
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {  
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {

	// TODO: complete this function'
    if(i == ROOT){ // If we are at the root
        return;    // Nowhere to heapify to so exit  
    }

    if(nodes_[i].first < nodes_[i/2].first){   // If parent's key is greater than current node's key 
        swap(nodes_[i],nodes_[i/2]);  // Swap the nodes 
        heapifyUp(i/2);               // Heapify new parent 
    }
}

void PriorityQueue::heapifyDown(size_t i) {

	// TODO: complete this function
    bool leftisSmallest; // Variable to determine which child is smallest   

    if(i == size_){      // If we at end of heap
        return;          // Nowhere to heapify to so exit 
    }

    if((2*i > size_) && (2*i+1 > size_)){ // No Children

        return;         // No children, no heapify 

    }else if((2*i <= size_) && (2*i+1 > size_)){ // Only left child exists
        if(nodes_[i].first > nodes_[2*i].first){ // if left child is less than current node then swap otherwise we are in right place
            
            swap(nodes_[i], nodes_[2*i]);        // Swap current node with left child 
            heapifyDown(2*i);                    // Heapify down the new left child 

        }else{ // Only left child exists but it is not less than current node 
            return;                              // Nowhere to heapify so exit 
        }
    }else if((2*i <= size_) && (2*i+1 <= size_)){ // Both children exist
        if(nodes_[2*i].first < nodes_[2*i+1].first){    
            leftisSmallest = true; // Left child is smallest 
        }else if(nodes_[2*i].first > nodes_[2*i+1].first){
            leftisSmallest = false; // Right child is smallest 
        }
        
        if((nodes_[i].first > nodes_[2*i].first) || (nodes_[i].first > nodes_[2*i+1].first)){   // If either left or right child are smaller than current node
            
            if(leftisSmallest == true){ // if left one is smallest of the two 
                swap(nodes_[i], nodes_[2*i]);   // Swap with left child 
                heapifyDown(2*i);               // Heapify down new left child 
            }else{  // right one is smallest 
                swap(nodes_[i], nodes_[2*i+1]); // Swap with right child 
                heapifyDown(2*i+1);             // Heapify down new right child
            }

        }
    }
}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
    nodes_[i]=nodes_[size_];    // Set current node's key to the last node's key
    size_--;                    // Decrease size of heap to remove last node 
    heapifyDown(i);             // Heapify the current node down 
}

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
    return nodes_[i].first;             // Return key of current node 
}
