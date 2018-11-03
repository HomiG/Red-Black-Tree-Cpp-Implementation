#pragma once

using namespace std;

typedef struct node Node;
struct node {
	int value;	//		 -------   	       -----
	bool color; //true-> |Black|. False->  |Red|
	Node* left; //		 -------		   -----
	Node* right;
	Node* parent;

	node(int number) {			//constructor for Node. 
		value = number;
		color = false;
		left = right = parent = 0;
	}
	node() {					//constructor for Node. 
		color = false;
		left = right = parent = 0;
	}
	node(int number, bool color) {
		value = number;
		this->color = color;
		left = right = parent = 0;
	}
};
class RBTree
{
public:
	RBTree();
	~RBTree();

	Node* uncleOf(Node*);		//returns a pointer to the "uncle" of the node.
	bool nullIsBlack(Node*);	//treats null pointers as color "BLACK"

	void insertion(int);
	int determineRotation(Node*);
	Node* search(int, Node*);
	Node* searchForInsertion(int, Node*);
	void recolor(Node*);
	void colorToggle(Node*);
	void leftRotate(Node*);	//performs a right rotation
	void rightRotate(Node*);	// performs a left rotation
	void generalRotateRecolor(Node*);	//smart Tool to determine what kind of rotations are needed ( comments in function definition )
	void print(Node*); // prints the values of the nodes of the redBlackTree
	

	Node* root;


private:


	//Node* root;
};

