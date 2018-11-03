#include "stdafx.h"
#include "RBTree.h"
#include"iostream"
#include"stack"

using namespace std;

RBTree::RBTree()
{
	this->root = 0; // Root -> Null;
}


RBTree::~RBTree()
{
}



void RBTree::print(Node* a) {
	if (a == nullptr)
		return;
	print(a->left);

	print(a->right);

	cout << a->value;
	if (a->color == true)
		cout << "B";
	else
		cout << "R";
	cout << " ";

}



Node* RBTree::uncleOf(Node* currentNode) {
	if (currentNode->parent->parent->right == currentNode->parent)
		return currentNode->parent->parent->left;
	else
		return currentNode->parent->parent->right;
}

bool RBTree::nullIsBlack(Node* a) {
	if (a == nullptr)
		return true;
	else
		return a->color;
}


void RBTree::leftRotate(Node* currentNode) {

	Node* pivot = currentNode->right;
	currentNode->right = pivot->left;
	if (currentNode->right != nullptr)
		currentNode->right->parent = currentNode;
	pivot->parent = currentNode->parent;

	if (currentNode->parent == nullptr) {
		this->root = pivot;
	}
	else if (currentNode->parent->left == currentNode) //if current node is a left child
		currentNode->parent->left = pivot;
	else
		currentNode->parent->right = pivot;

	pivot->left = currentNode;
	currentNode->parent = pivot;

}

void RBTree::rightRotate(Node* currentNode) {
	Node* pivot = currentNode->left;
	currentNode->left = pivot->right;
	if (currentNode->left != nullptr)
		currentNode->left->parent = currentNode;

	pivot->parent = currentNode->parent;

	if (currentNode->parent == nullptr) {
		this->root = pivot;
	}
	else if (currentNode->parent->right == currentNode) //if current node is a right child
		currentNode->parent->right = pivot;
	else
		currentNode->parent->left = pivot;

	pivot->right = currentNode;
	currentNode->parent = pivot;


}

int RBTree::determineRotation(Node* currentNode) {
	if (currentNode->parent->right == currentNode && currentNode->parent->parent->right == currentNode->parent)		//RR
		return 1;
	else if (currentNode->parent->left == currentNode && currentNode->parent->parent->left == currentNode->parent)	//LL
		return 2;
	else if (currentNode->parent->left == currentNode && currentNode->parent->parent->right == currentNode->parent)	//LR
		return 3;
	else																											//RL
		return 4;
}

Node* RBTree::search(int number, Node *n) {	//returns null if element is not found

	if (n == 0)
		return 0;
	else if (n->value == number)
		return n;

	else if (number > n->value)
		return search(number, n->right);
	else
		return search(number, n->left);
}

Node* RBTree::searchForInsertion(int number, Node *n) {

	if (n->left == 0 && number<n->value || n->right == 0 && number>n->value) {
		return n;
	}
	else if (number > n->value) {
		if (n->right == 0)
			return n;
		else
			return searchForInsertion(number, n->right);
	}
	else {
		if (n->left == 0)
			return n;
		else
			return searchForInsertion(number, n->left);
	}
}

void RBTree::colorToggle(Node* insertedNode) {
	if (insertedNode->color == true)
		insertedNode->color = false;
	else
		insertedNode->color = true;
}

void RBTree::recolor(Node* addedNode) {
	//Recolor
	//if (newNode->parent->color == false && newNode->parent->parent->right==false) 		
	addedNode->parent->color = true;	//parent of added Node   --> Black.
	if (addedNode->parent->parent != this->root) {	//if grandparent is the ROOT let it black. ELSE -> //grandparent of added Node  --> Red.
		addedNode->parent->parent->color = false;
	}
	uncleOf(addedNode)->color = true;	//uncle of added node --> Black.

}

void RBTree::insertion(int number) {
	Node *newNode = new Node(number);  //TAKE CARE!! Delete the Node somehow.. somewhen..

									   //Add the Red Node.
	if (this->root == 0) {			// if there's no root, make the new node ROOT
		newNode->color = true;
		root = newNode;
		return;
	}
	else {
		Node *temp; // is used to find in which node, the new node will be added..
		temp = this->searchForInsertion(number, root);
		if (number > temp->value) {
			temp->right = newNode;
			newNode->parent = temp;
		}
		else {
			temp->left = newNode;
			newNode->parent = temp;
		}

		generalRotateRecolor(newNode);

	}
}

//Recolor and Rotate
void RBTree::generalRotateRecolor(Node *newNode) {
	if (newNode->parent == nullptr || newNode->parent->color == true) {
		return;
	}
	else if (newNode->parent->color == false && nullIsBlack(uncleOf(newNode)) == false) {	// if parent==Red && uncle==red
		recolor(newNode);
		try {
			generalRotateRecolor(newNode->parent->parent);
		}
		catch (exception e) {} //will catch if there is null pointer exception.. using this in case of checking for the parent of the root..
	}
	else if (newNode->parent->color == false && nullIsBlack(uncleOf(newNode)) == true) {	// if parent==Red && uncle==black 
		int nm = this->determineRotation(newNode);

		switch (nm)	// 1->RR  2->LL  3->LR  4->RL
		{
		case 1:		//RR
			colorToggle(newNode->parent);
			colorToggle(newNode->parent->parent);
			leftRotate(newNode->parent->parent);
			break;
		case 2:		//LL
			colorToggle(newNode->parent);
			colorToggle(newNode->parent->parent);
			rightRotate(newNode->parent->parent);
			break;
		case 3:		//LR
			rightRotate(newNode->parent);
			colorToggle(newNode);
			colorToggle(newNode->parent);
			leftRotate(newNode->parent);
			break;
		case 4:		//RL
			leftRotate(newNode->parent);
			colorToggle(newNode);
			colorToggle(newNode->parent);
			rightRotate(newNode->parent);

			break;
		default:
			std::cout << "Lol?";
			break;
		}

	}
}













