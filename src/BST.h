/*

 * Vincent Ha

 * CIS 22C, Winter 2017

 */

#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include "assert.h"
using namespace std;

template <class bstdata>
class BST
{
    private:
        struct Node
        {
                bstdata data;
                Node* left;
                Node* right;

                Node(bstdata newdata): data(newdata), left(NULL), right(NULL) {}
        };

        typedef struct Node* NodePtr;
        NodePtr root;

        /**Private helper functions*/

        void insertHelper(NodePtr root, bstdata value);
        //private helper function for insert
        //recursively inserts a value into the BST

        void destructorHelper(NodePtr root);
        //private helper function for the destructor
        //recursively frees the memory in the BST

        void inOrderPrintHelper(NodePtr root, ostream& os);
        //private helper function for inOrderPrint
        //recursively prints tree values in order from smallest to largest

        void preOrderPrintHelper(NodePtr root, ostream& os);
        //private helper function for preOrderPrint
        //recursively prints tree values in preorder

        void postOrderPrintHelper(NodePtr root, ostream& os);
        //private helper function for postOrderPrint
        //recursively prints tree values in postorder

        bstdata maximumHelper(NodePtr root);
        //recursively searches for the maximum value in the Binary Search Tree

        bstdata minimumHelper(NodePtr root);
        //recursively locates the minimum value in the tree
        //returns this value once it is located

        void getSizeHelper(NodePtr root, int& size);
        //recursively calculates the size of the tree

        int getHeightHelper(NodePtr root);
        //recursively calculates the height of the tree

        bool findHelper(NodePtr root, bstdata value);
        //recursively searches for value in the tree

        NodePtr removeHelper(NodePtr root, bstdata value);
        //recursively removes the specified value from the tree

        void copyHelper(NodePtr copy);
        //recursively makes a deep copy of a binary search tree

        /**Public functions*/

    public:
        BST();
        //Instantiates a new Binary Search Tree
        //post: a new Binary Search Tree object

        BST(const BST& tree);
        //makes a deep copy of tree
        //Calls the copyHelper function to make a copy recursively

        ~BST();
        //frees the memory of the BST object
        //All memory has been deallocated

        bool isEmpty();
        //determines whether the Binary Search Tree is empty

        void insert(bstdata value);
        //inserts a new value into the Binary Search Tree
        //post: a new value inserted into the Binary Search Tree

        bstdata getRoot();
        //returns the value stored at the root of the Binary Search Tree
        //pre: the Binary Search Tree is not empty

        void inOrderPrint(ostream& os);
        //calls the inOrderPrintHelper function to print out the values
        //stored in the Binary Search Tree
        //If the tree is empty, prints nothing

        void preOrderPrint(ostream& os);
        //calls the preOrderPrintHelper function to print out the values
        //stored in the Binary Search Tree
        //If the tree is empty, prints nothing

        void postOrderPrint(ostream& os);
        //calls the postOrderPrintHelper function to print out the values
        //stored in the Binary Search Tree
        //If the tree is empty, prints nothing

        bstdata maximum();
        //finds the maximum value in the Binary Search Tree and returns it
        //calls the maximumHelper function to search for the max recursively
        //pre: !isEmpty()

        bstdata minimum();
        //calls the minimumHelper function to return the minimum value in the tree
        //Pre: the tree is not empty

        int getSize();
        //returns the size of the tree
        //calls the getSizeHelper function to calculate the size recursively

        int getHeight();
        //recursively finds the height of the tree and returns it
        //calls the getHeight helper function to calculate the height recursively
        //returns -1 if the tree is empty

        bool find(bstdata value);
        //returns whether the value is in the tree
        //calls the findHelper function to search for the value recursively
        //Pre: !isEmpty()

        void remove(bstdata value);
        //removes the specified value from the tree
        //Pre: !isEmpty()
        //Pre: The value is contained in the Binary Search Tree
        //If the value is not in the Binary Search Tree, the tree is left unchanged
};



/**Private helper functions*/

template <class bstdata>
void BST<bstdata>::insertHelper(NodePtr root, bstdata value){
	if(value == root->data){
		cout << "The value you tried to add is already in the tree." << endl;
	}

	else if(root->data > value){
		if(root->left == NULL){
			root->left = new Node(value);
		} else{
			insertHelper(root->left, value);
		}
	}

	else{
		if(root->right == NULL){
			root->right = new Node(value);
		} else{
			insertHelper(root->right, value);
		}
	}
}

template <class bstdata>
void BST<bstdata>::destructorHelper(NodePtr root){
	if(root != NULL){
		destructorHelper(root->left);
		destructorHelper(root->right);
		delete root;
	}
}

template <class bstdata>
void BST<bstdata>::inOrderPrintHelper(NodePtr root, ostream& os){
	if(root != NULL){
		inOrderPrintHelper(root->left, os);
		os << root->data << endl;
		inOrderPrintHelper(root->right, os);
	}
}

template <class bstdata>
void BST<bstdata>::preOrderPrintHelper(NodePtr root, ostream& os){
	if(root != NULL){
		os << root -> data << endl;
		preOrderPrintHelper(root->left, os);
		preOrderPrintHelper(root->right, os);
	}
}

template <class bstdata>
void BST<bstdata>::postOrderPrintHelper(NodePtr root, ostream& os){
	if(root != NULL){
		postOrderPrintHelper(root->left, os);
		postOrderPrintHelper(root->right, os);
		os << root -> data << endl;
	}
}

template <class bstdata>
bstdata BST<bstdata>::maximumHelper(NodePtr root){
	if(root->right == NULL)
		return root->data;
	else
		return maximumHelper(root->right);
}

template <class bstdata>
bstdata BST<bstdata>::minimumHelper(NodePtr root){
	if(root->left == NULL)
		return root->data;
	else
		return minimumHelper(root->left);
}

template <class bstdata>
void BST<bstdata>::getSizeHelper(NodePtr root, int& size){
	if(root != NULL){
		size++;
		getSizeHelper(root->left, size);
		getSizeHelper(root->right, size);
	}
}

template <class bstdata>
int BST<bstdata>::getHeightHelper(NodePtr root){
	if(root == NULL){
		return -1;
	}

	int leftHeight = getHeightHelper(root->left);
	int rightHeight = getHeightHelper(root->right);

	if(leftHeight > rightHeight){
		return leftHeight + 1;
	} else{
		return rightHeight + 1;
	}
}

template <class bstdata>
bool BST<bstdata>::findHelper(NodePtr root, bstdata value){
	if(root->data == value)
		return true;

	else if(value > root->data){
		if(root->right != NULL)
			return findHelper(root->right, value);
		else
			return false;
	} else{
		if(root->left != NULL)
			return findHelper(root->left, value);
		else
			return false;
	}

}

template <class bstdata>
typename BST<bstdata>::NodePtr BST<bstdata>::removeHelper(NodePtr root, bstdata value){
	if(root == NULL)
		return root;
	if(value > root->data)
		root->right = removeHelper(root->right, value);
	else if(value < root->data)
		root->left = removeHelper(root->left, value);
	else{
		if(root->left == NULL && root->right == NULL){
			delete root;
			root = NULL;
		} else if(root->left != NULL && root->right == NULL){
			NodePtr temp = root;
			root = root->left;
			delete temp;
		} else if(root->left == NULL && root->right != NULL){
			NodePtr temp = root;
			root = root->right;
			delete temp;
		} else{
			root->data = minimumHelper(root->right);
			root->right = removeHelper(root->right, root->data);
		}
	}
	return root;
}

template <class bstdata>
void BST<bstdata>::copyHelper(NodePtr copy){
	if(copy != NULL){
		insert(copy->data);
		copyHelper(copy->left);
		copyHelper(copy->right);
	}
}

/**Public functions*/

template <class bstdata>
BST<bstdata>::BST():root(NULL){}

template <class bstdata>
BST<bstdata>::BST(const BST& tree){
	if(tree.root == NULL){
		root = NULL;
	} else{
		root = NULL;
		copyHelper(tree.root);
	}
}

template <class bstdata>
BST<bstdata>::~BST(){
	destructorHelper(root);
}

template <class bstdata>
void BST<bstdata>::insert(bstdata value){
	if (root == NULL){
		root = new Node(value); //if the tree is empty insert the value at the root
	} else {
		insertHelper(root, value); //otherwise call the helper function, passing it the root
	}
}

template <class bstdata>
bstdata BST<bstdata>::getRoot()
{
   //returns the data contained at the root node
	assert(root != NULL);
	return root->data;
}

template <class bstdata>
bool BST<bstdata>::isEmpty(){
	return root == NULL;
}

template <class bstdata>
void BST<bstdata>::inOrderPrint(ostream& os){
	assert(root != NULL);
	inOrderPrintHelper(root, os);
	os << endl;
}

template <class bstdata>
void BST<bstdata>::preOrderPrint(ostream& os){
	assert(root != NULL);
	preOrderPrintHelper(root, os);
	os << endl;
}

template <class bstdata>
void BST<bstdata>::postOrderPrint(ostream& os){
	assert(root != NULL);
	postOrderPrintHelper(root, os);
	os << endl;
}

template <class bstdata>
bstdata BST<bstdata>::maximum(){
	assert(!isEmpty());
	return maximumHelper(root);
}

template <class bstdata>
bstdata BST<bstdata>::minimum(){
	assert(!isEmpty());
	return minimumHelper(root);
}

template <class bstdata>
int BST<bstdata>::getSize(){
	int size = 0;
	getSizeHelper(root,size);
	return size;
}

template <class bstdata>
int BST<bstdata>::getHeight(){
	if(isEmpty()){
		return -1;
	} else{
		return getHeightHelper(root);
	}
}

template <class bstdata>
bool BST<bstdata>::find(bstdata value){
	assert(!isEmpty());
	return findHelper(root, value);
}

template <class bstdata>
void BST<bstdata>::remove(bstdata value){
	assert(!isEmpty());
	assert(find(value));
	root = removeHelper(root, value);
}

#endif /* BST_H_ */
