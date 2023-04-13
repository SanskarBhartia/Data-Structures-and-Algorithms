#include "AVL.h"

#include <cassert>
#include <iostream>
#include <string>
#include <queue>

#include "json.hpp"
using namespace std; 
using json = nlohmann::json; 

AVLNode::AVLNode(int key) :
	key_(key),
	parent_(std::weak_ptr<AVLNode>()),
	left_(nullptr),
	right_(nullptr) {}

AVLNode::AVLNode(int key, std::weak_ptr<AVLNode> parent) :
	key_(key),
	parent_(parent),
	left_(nullptr),
	right_(nullptr) {}


AVL::AVL() : root_(nullptr), size_(0) {}

// AVL class function that takes in a node and returns the height of it as an int
int AVL::getHeight(std::shared_ptr<AVLNode> node){
	if(node == nullptr){	// Checking if the node exists or not 
		return -1; 			// Advised to set null nodes to -1 in class 
	}else{
		return (max(getHeight(node->left_), getHeight(node->right_)) + 1);	// Returning the max height of left and right nodes and 
																			// adding 1 to account for current node to child connection
	}
}

// AVL class function that takes in a node and returns the balance factor of it as an int
int AVL::getBF(std::shared_ptr<AVLNode> node){
	int x = (getHeight(node->right_) - getHeight(node->left_)); 			// Creating a variable to hold the balance factor 
																			// Which is simply just height of right node - height of left node
	return x; 																// Return the balance factor 
}

// AVL class function that takes in a node and performs a right rotation on it 
std::shared_ptr<AVLNode> AVL::rightRotation(std::shared_ptr<AVLNode> node){
	std::shared_ptr<AVLNode> newNode = node->left_; 	// Shared pointer initially at left 

	node->left_ = newNode->right_; 						// Old node's left node becomes new node's right node 
	newNode->right_ = node; 							// New node's right node becomes the old node (with its children in-tact)
	
	if(node->left_ != nullptr){							// If old node's left child exists 
		node->left_->parent_ = node; 					// Set old node's left parent = node since that node was previously new node's right 
														// and was an orphan that needed to be rehomed 
	}

	newNode->parent_ = node->parent_;					// New node's parent becomes the old node's parent so that is rehomed
														// to the same parents as old node 

	if(node->parent_.lock() != nullptr){				    // Checked to make sure the node's parent isn't null 
		if(node == node->parent_.lock()->left_){			// Checking for left node 
			node->parent_.lock()->left_ = newNode;		    // Switching w/ left node  
		}
		else if(node == node->parent_.lock()->right_)	    // Checking for right node 
		{
			node->parent_.lock()->right_ = newNode;		    // Switching with right node 
		}
	}
	node->parent_ = newNode; 								// New root is set  										
	return newNode; 										// Return new root node 
}

// AVL class function that takes in a node and performs a left rotation on it 
std::shared_ptr<AVLNode> AVL::leftRotation(std::shared_ptr<AVLNode> node){
    std::shared_ptr<AVLNode> newNode = node->right_; 		// Shared pointer initially at right
	node->right_ = newNode->left_; 							// Switching nodes
newNode->left_ = node; 										// Newnode points to the left now

	if(node->right_ != nullptr){ 							// Make node to be rotated on
		node->right_->parent_ = node;						// Changes the pointer
	}

	newNode->parent_ = node->parent_;

	if(node->parent_.lock()){								// Using lock function to set the pointers location
		if(node == node->parent_.lock()->left_){ 			// Checks for left node
			node->parent_.lock()->left_ = newNode; 			// Switches
		}
		else if(node == node->parent_.lock()->right_)		// Checks for right node
		{
			node->parent_.lock()->right_ = newNode;			// Switches
		}
	}
	node->parent_ = newNode; 								// Pointer becomes the new root
	return newNode; 										// Return new root node 
}

// AVL class function that takes in a node and performs a right left rotation on it 
std::shared_ptr<AVLNode> AVL::RLRotation(std::shared_ptr<AVLNode> node){
    node->right_ = rightRotation(node->right_);				// Perform right rotation on right node 
	return leftRotation(node); 								// Return node after rotating it to the left 
}

// AVL class function that takes in a node and performs a left right rotation on it 
std::shared_ptr<AVLNode> AVL::LRRotation(std::shared_ptr<AVLNode> node){
	node->left_ = leftRotation(node->left_);				// Perform left rotation on left node 
	return rightRotation(node); 							// Return node after rotating it to the right 
}

// AVL class function that takes in a node and balances it using getBF and the respective rotation functions 
void AVL::balance(std::shared_ptr<AVLNode> node){
	if(getBF(node) > 1 || getBF(node) < -1){				// Checking if current node is unbalaned using bounds 
		if(getBF(node) > 1 && getBF(node->right_) <= -1){ 	// right left rotation (right left heavy)
			//cout << "right left heavy" << endl; 
			node = RLRotation(node); 
		}
		if(getBF(node) > 1 && getBF(node->right_) >= 1){ 	// left left rotation (right right heavy)
			//cout << "right right heavy" << endl; 
			node = leftRotation(node); 
		}
		if(getBF(node) < -1 && getBF(node->left_) <= -1){ 	// right right rotation (left left heavy)
			//cout << "left left heavy" << endl; 
			node = rightRotation(node); 
		}
		if(getBF(node) < -1 && getBF(node->left_) >= 1){ 	// left right rotation (left right heavy)
			//cout << "left right heavy" << endl; 
			node = LRRotation(node); 
		}
		if(node->parent_.lock() == nullptr){
			root_ = node; 
		}
	}
	if (node->parent_.lock() == nullptr){	// If the current node is the root
        return;								// Return because we balanced everything
    }else{
        balance(node->parent_.lock());  	// If current node is not the root call balance on its parent to balance the ENTIRE tree
    } 
	return; 
}	

// AVL class function that inserts a key where it needs to be inserted (mostly pre-coded and given to us)
void AVL::Insert(int key) {
	if (root_ == nullptr) {
		root_ = std::make_shared<AVLNode>(key);	
		size_++;
		return;
	}
	std::shared_ptr<AVLNode> currentNode = root_, lastNode = nullptr;
	while (currentNode != nullptr) {
		
		lastNode = currentNode;
		currentNode = (key < currentNode->key_) ?
			currentNode->left_: currentNode->right_;
	} 
	if (key < lastNode->key_) {
		lastNode->left_ = std::make_shared<AVLNode>(key, lastNode);		
		balance(lastNode->left_); 	// Balance the newly inserted node 
	} else {
		lastNode->right_ = std::make_shared<AVLNode>(key, lastNode);	
		balance(lastNode->right_);  // Balanced the newly inserted node 
	}		
	size_++;
}


size_t AVL::size() const {
	return size_;
}

bool AVL::empty() const {
	return size_ == 0;
}

// AVL class function that was altered to return a json object w/ the tree content
json AVL::JSON(){
	nlohmann::json result;
	std::queue< std::shared_ptr<AVLNode> > nodes;
	if (root_ != nullptr) {
		result["root"] = root_->key_;
		nodes.push(root_);
		while (!nodes.empty()) {
			auto v = nodes.front();
			nodes.pop();
			std::string key = std::to_string(v->key_);	
			result[key]["height"] = getHeight(v);  		// Creating a key for the height of the current node 
			result[key]["balance factor"] = getBF(v);  	// Creating a key for the BF of the current node 
			if (v->left_ != nullptr) {
				result[key]["left"] = v->left_->key_;
				nodes.push(v->left_);
			}
			if (v->right_ != nullptr) {
				result[key]["right"] = v->right_->key_;
				nodes.push(v->right_);
			}
			if (v->parent_.lock() != nullptr) {
				result[key]["parent"] = v->parent_.lock()->key_;
			} else {
				result[key]["root"] = true;
			}
		}
	}
	result["height"] = getHeight(root_);				// Creating key for max height in tree which is the height of the root always 
	result["size"] = size_;									
	return result;
}