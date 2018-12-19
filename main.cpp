// Project 2
// Duyen Pham
// COSC 2030 - 01
// Dec 15, 2018


#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <vector>

// Prototype functions.
void getRequest(string & request);

int
main()
{
	randomizeSeed();
	BinaryTree theTree;

	// Init parent node
	theTree.initParent(); 

	string request;
	getRequest(request);

	while ((request != "quit") && (request != "exit"))
	{
		if (request == "display")
		{
			theTree.display(cout);
		}

		else if (request == "id")
		{
			size_t ID;
			cin >> ID;
			theTree.searchID(ID);
		}

		else if (request == "new")
		{
			theTree.add();
		}

		else if (request == "update")
		{
			size_t ID;
		    std::string event;
			cin >> ID >> event;
			theTree.update(ID, event);
		}

		else
		{
			cout << "display \t- visualize tree as a set of ID values.\n \
				\rid <node ID>\t- see entire record for ID value entered.\n \
                \rnew \t\t- add a new node.\n \
                \rupdate <node ID> <raw event>\n \
                \rquit\t\t- exit the program.\n" << endl;
		}

		getRequest(request);
	}

	return 0;
}

void
getRequest(string & request)
{
	cout << "Enter request: ";
	cin >> request;
}