#include <memory>
#include <string>
#include "json.hpp"
class AVL;

class AVLNode {
 public:
 	AVLNode(int key);
 	AVLNode(int key, std::weak_ptr<AVLNode> parent);

 private:
  int key_;
  std::weak_ptr<AVLNode> parent_;
  std::shared_ptr<AVLNode> left_;
  std::shared_ptr<AVLNode> right_;
  
  friend AVL;
}; // class AVLNode

class AVL {
 public:
 	AVL();
	void balance(std::shared_ptr<AVLNode> node); 
	std::shared_ptr<AVLNode> LRRotation(std::shared_ptr<AVLNode> node);
	std::shared_ptr<AVLNode> RLRotation(std::shared_ptr<AVLNode> node);
	std::shared_ptr<AVLNode> leftRotation(std::shared_ptr<AVLNode> node);
	std::shared_ptr<AVLNode> rightRotation(std::shared_ptr<AVLNode> node);
	int getHeight(std::shared_ptr<AVLNode> node); // added 
	int getBF(std::shared_ptr<AVLNode> node); // added 
 	void Insert(int key);
 	nlohmann::json JSON();
 	size_t size() const;
 	bool empty() const;

 private:

 	std::shared_ptr<AVLNode> root_;
 	size_t size_;
}; // class AVL