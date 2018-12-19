// Project 2
// Duyen Pham
// COSC 2030 - 01
// Dec 14, 2018


#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_


#include "utilities.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>

using namespace std;

//***  Binary Tree class  ***//

class BinaryTree
{
protected:

	// Since the BinaryNode class is embedded in the BinaryTree
	//   class, the public data members and methods of
	//   BinaryNode are only visible within the BinaryTree class. 
	//   Client code cannot see BinaryNode object data members
	//   or methods.
	class BinaryNode
	{

	public:
		short entry_;
		BinaryNode * left_;
		BinaryNode * right_;
		size_t ID_;
		size_t parentID_;
		std::string rawEvent_;
		size_t RHASH_;
		size_t LHASH_;
		std::list<size_t> RHIST_;
		std::list<size_t> LHIST_;

	public:
		BinaryNode(
			short entry = 0,
			size_t ID = 0,
			size_t ParentID = 0,
			std::string rawEvent = "NULL",
			size_t RHASH = 0,
			size_t LHASH = 0,
			std::list<size_t> RHIST = list<size_t>(),
			std::list<size_t> LHIST = list<size_t>(),
			BinaryNode * left = NULL,
			BinaryNode * right = NULL)
			: entry_(entry),
			left_(NULL),
			right_(NULL),
			ID_(ID),
			parentID_(ParentID),
			rawEvent_(rawEvent),
			RHASH_(RHASH),
			LHASH_(LHASH),
			RHIST_(RHIST),
			LHIST_(LHIST)
		{}

		// NOTE: The standard BinaryNode destructor code does
		//   NOT delete BinaryNodes in the subtrees of left_ or right_.
		//   See BinaryTree destroy.
		~BinaryNode()
		{
		}

	private:
		// Disable the BinaryNode copy constructor and the assignment
		//   operator.
		BinaryNode(const BinaryNode &);
		const BinaryNode & operator =(const BinaryNode &);
	};


public:
	// The no-parameter constructor creates an empty tree.
	BinaryTree();

	// The destructor deallocates all the nodes in the tree.
	~BinaryTree();


	// Mutators

	// Add a node to the current tree.
	void add();

	// Init parent node.
	void initParent();

	// Search and ID in the current tree
	void searchID(size_t id);

	// Update a node raw event.
	void update(size_t id, std::string event);


	// Accessors

	// Display the tree.
	// The node values are listed using an inorder
	//   traversal.
	// Node values are indented by the depth of the node to
	//   display the shape of the tree.
	// The tree shape is displayed with the left subtree at
	//   the top of the screen.
	void display(std::ostream& outfile) const;


private:
	BinaryNode * tree_;
	static int btEntry_;
	static int level_;

private:
	// Disable operator=
	BinaryTree & operator=(BinaryTree&);

	// Disable the copy constructor
	BinaryTree(const BinaryTree &);


private:
	// helper functions

	// Helper functions process a subtree.
	// Each helper function is called by a public function 
	//   that fulfills a request to process the entire
	//   tree by calling the helper function that processes a
	//   subtree referenced by a pointer to its root node.
	//   The empty subtree is indicated by a NULL pointer.


	// Delete all nodes referenced via subtree.
	// Set subtree to NULL.
	static void destroy(BinaryNode * & subtree);


	// Add a new node to the tree.
	static void newNode(BinaryNode * &subtree);

	// Init first node.
	static void initNode(BinaryNode * &subtree);

	// Search and Print a record.
	static void search_and_print(BinaryNode * subtree, std::ostream & outfile, size_t id, bool &found);

	// Update a raw event.
	static void updateRawEvent(BinaryNode * subtree, size_t id, std::string rawEvent, bool &update_completed);

	// This subtree is a left subtree.
	// Display the nodes connected to subtree on outfile.
	// Use a line by line display, order nodes from left to
	//   right, draw connecting lines.
	// Preface each line of the display with prefix.
	static void displayLeft(std::ostream & outfile,
		BinaryNode * subtree, std::string prefix);

	// This subtree is a right subtree.
	// Display the nodes connected to subtree on outfile.
	// Use a line by line display, order nodes from left to
	//   right, draw connecting lines.
	// Preface each line of the display with prefix.
	static void displayRight(std::ostream & outfile,
		BinaryNode * subtree, std::string prefix);

	// Display IDs
	static void displayID(BinaryNode * subtree, std::ostream& outfile);
};


// Set the initial value of the static binary tree entry.
int BinaryTree::btEntry_ = 1;

// Set level
int BinaryTree::level_ = 0;

// Code for public methods of BinaryTree
// **********************************

// The no-parameter constructor creates an empty tree.
BinaryTree::BinaryTree()
	: tree_(NULL)
{
}

// The destructor deallocates all the nodes in the tree.
BinaryTree:: ~BinaryTree()
{
	destroy(tree_);
}

// Add a new node to the tree.
void
BinaryTree::add()
{
	level_ = btEntry_;
	newNode(tree_);
}

// Init parent node.
void
BinaryTree::initParent()
{
	initNode(tree_);
}

// Search a user specified ID in the tree and display values.
void BinaryTree::searchID(size_t id)
{
	bool found = false;
	search_and_print(tree_, cout, id, found);
}

// Update a node.
void BinaryTree::update(size_t id, std::string event)
{
	bool update_completed = false;
	updateRawEvent(tree_, id, event, update_completed);
}

// Display the tree.
// The node values are ordered using an inorder traversal.
// Node values are indented by the depth of the node to display
//   the shape of the tree.
void
BinaryTree::display(std::ostream& outfile) const
{
	std::string prefix;
	if (tree_ == NULL)
	{
		outfile << "-" << std::endl;
	}
	else
	{
		displayRight(outfile, tree_->right_, "    ");
		outfile << "---" << tree_->entry_ << std::endl;
		displayLeft(outfile, tree_->left_, "    ");
		
	}

	cout << "\nID Records: " << std::endl;
	if (tree_ == NULL)
	{
		outfile << "-> No Record Found" << std::endl;
	}
	else
	{
		displayID(tree_, outfile);
		outfile << std::endl;
	}
}

// Display IDs
void
BinaryTree::displayID(BinaryNode * subtree, std::ostream& outfile)
{
	if (subtree == NULL) {
		return;
	}
	else {
		outfile << subtree->entry_ << ":\t" << subtree->ID_ << std::endl;
		displayID(subtree->left_, outfile);
		displayID(subtree->right_, outfile);
	}
}

// Init parent node
void
BinaryTree::initNode(BinaryNode * & subtree)
{
	subtree = new BinaryNode(btEntry_);
	btEntry_++;

	// Parent node fields
	subtree->parentID_ = rand() % 100;
	subtree->rawEvent_ = "Root Node";
	subtree->ID_ = IdHash(subtree->parentID_, subtree->rawEvent_);
}


// Build a random shaped tree of size nodes.
// Construct the BinaryNodes in preorder sequence.
void
BinaryTree::newNode(BinaryNode * &subtree)
{
	if ((level_ >> 1) == 1) {
		if (level_ & 1) {
			subtree->right_ = new BinaryNode(btEntry_);

			// Update the fields
			subtree->right_->parentID_ = subtree->ID_;
			subtree->right_->rawEvent_ = "New Node Right";
			subtree->right_->ID_ = IdHash(subtree->right_->parentID_, subtree->right_->rawEvent_);

			subtree->RHASH_ = LRHash(
				subtree->right_->ID_,
				subtree->right_->parentID_,
				subtree->right_->rawEvent_,
				subtree->right_->LHASH_,
				subtree->right_->RHASH_
			);
			subtree->RHIST_.push_front(subtree->RHASH_);
		}
		else {
			subtree->left_ = new BinaryNode(btEntry_);

			// Update the fields
			subtree->left_->parentID_ = subtree->ID_;
			subtree->left_->rawEvent_ = "New Node Left";
			subtree->left_->ID_ = IdHash(subtree->left_->parentID_, subtree->left_->rawEvent_);

			subtree->LHASH_ = LRHash(
				subtree->left_->ID_,
				subtree->left_->parentID_,
				subtree->left_->rawEvent_,
				subtree->left_->LHASH_,
				subtree->left_->RHASH_
			);
			subtree->LHIST_.push_front(subtree->LHASH_);
		}
		btEntry_++;
	}
	else {
		if (level_ & 1) {
			level_ = level_ >> 1;
			newNode(subtree->right_);

			// Percolate changes.
			if (subtree->right_ != NULL) {
				subtree->RHASH_ = LRHash(
					subtree->right_->ID_,
					subtree->right_->parentID_,
					subtree->right_->rawEvent_,
					subtree->right_->LHASH_,
					subtree->right_->RHASH_
				);
				subtree->RHIST_.push_front(subtree->RHASH_);
			}
		}
		else {
			level_ = level_ >> 1;
			newNode(subtree->left_);

			// Percolate changes.
			if (subtree->left_ != NULL) {
				subtree->LHASH_ = LRHash(
					subtree->left_->ID_,
					subtree->left_->parentID_,
					subtree->left_->rawEvent_,
					subtree->left_->LHASH_,
					subtree->left_->RHASH_
				);
				subtree->LHIST_.push_front(subtree->LHASH_);
			}
		}
	}

}


// Display the nodes connected to subtree.
// This is a right subtree.
// Use a line by line display, order nodes from left to
//   right, draw connecting lines.
void
BinaryTree::displayRight(std::ostream & outfile,
	BinaryNode * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "/" << std::endl;
	}
	else
	{
		displayRight(outfile, subtree->right_, prefix + "     ");
		outfile << prefix + "/---" << subtree->entry_ << std::endl;
		displayLeft(outfile, subtree->left_, prefix + "|    ");
	} 
}


// Display the nodes connected to subtree.
// This is a left subtree.
// Use a line by line display, order nodes from left to
//   right, draw connecting lines.
void
BinaryTree::displayLeft(std::ostream & outfile,
	BinaryNode * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "\\" << std::endl;
	}
	else
	{
		displayRight(outfile, subtree->right_, prefix + "|    ");
		outfile << prefix + "\\---" << subtree->entry_ << std::endl;
		displayLeft(outfile, subtree->left_, prefix + "     ");
	}
}

// Search and Print a record.
void
BinaryTree::search_and_print(BinaryNode * subtree, std::ostream & outfile, size_t id, bool &found)
{
	if (subtree == NULL) {
		return;
	}
	else {
		if (subtree->ID_ == id) {
			outfile << endl <<
				"ID:          " << subtree->ID_ << endl <<
				"Parent  ID:  " << subtree->parentID_ << endl <<
				"Raw  Event:  " << subtree->rawEvent_ << endl <<
				"Left  Hash:  " << subtree->LHASH_ << endl <<
				"Right Hash:  " << subtree->RHASH_ << endl <<
				"Left  Hist:  " << endl;

			// Print all items in LHIST.
			for (list<size_t>::iterator i = subtree->LHIST_.begin(); i != subtree->LHIST_.end(); i++) {
				outfile << "\t" << *i << endl;
			}

			// Print all items in RHIST.
			outfile << "Right Hist:  " << endl;
			for (list<size_t>::iterator i = subtree->RHIST_.begin(); i != subtree->RHIST_.end(); i++) {
				outfile << "\t" << *i << endl;
			}
			found = true;
		}
		else {
			search_and_print(subtree->left_, outfile, id, found);
			if (found) return;
			search_and_print(subtree->right_, outfile, id, found);
			if (found) return;
		}
	}
}


// Update a raw event.
void
BinaryTree::updateRawEvent(BinaryNode * subtree, size_t id, std::string rawEvent, bool &update_completed) {
	if (subtree == NULL) {
		return;
	}
	else {
		if (subtree->ID_ == id) {
			subtree->rawEvent_ = rawEvent;
			subtree->ID_ = IdHash(subtree->parentID_, subtree->rawEvent_);
			cout << "New ID: " << subtree->ID_ << endl;
			update_completed = true;
		}
		else {
			updateRawEvent(subtree->left_, id, rawEvent, update_completed);
			
			// Percolate changes
			if (update_completed) {
				subtree->LHASH_ = LRHash(
					subtree->left_->ID_,
					subtree->left_->parentID_,
					subtree->left_->rawEvent_,
					subtree->left_->LHASH_,
					subtree->left_->RHASH_
				);
				subtree->LHIST_.push_front(subtree->LHASH_);
				return;
			}

			updateRawEvent(subtree->right_, id, rawEvent, update_completed);
			if (update_completed) {
				// Percolate changes
				subtree->RHASH_ = LRHash(
					subtree->right_->ID_,
					subtree->right_->parentID_,
					subtree->right_->rawEvent_,
					subtree->right_->LHASH_,
					subtree->right_->RHASH_
				);
				subtree->RHIST_.push_front(subtree->RHASH_);
				return;
			}
		}
	}
}

// code for helper functions

// Delete all nodes connected to subtree
void
BinaryTree::destroy(BinaryNode * & subtree)
{
	if (subtree != NULL)
	{
		destroy(subtree->left_);
		destroy(subtree->right_);
		delete subtree;
		subtree = NULL;
	}
}
#endif
