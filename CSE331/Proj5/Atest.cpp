//
//All files writen by C. Owen for CSE331 FS06
//Modified by A.W. Covert III 
//
//
// Name :        main.cpp
// Description : Demonstration program that shows how to load the data from the 
//               Internet Movie Database actors list file.  
//

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Tree.h"

using namespace std;



int main()
{
	cout << "Leroooooooooooooooooooooooooooooooy" << endl << endl;

	CTree<int> intree;

	cout << "Inserting several nodes now..." << endl << endl;

	intree.Insert(50);
	cout << "Inserting duplicate item, should be ignored." << endl << endl;
	intree.Insert(50);
	cout << "\nAfter second 50" << endl << endl;
	intree.Preorder(cout);	
	intree.Insert(75);
	cout << "\nAfter 75" << endl << endl;
	intree.Preorder(cout);
	intree.Insert(25);
	cout << "\nAfter 25" << endl << endl;
	intree.Preorder(cout);
	intree.Insert(10);
	cout << "\nAfter 10" << endl << endl;
	intree.Preorder(cout);
	intree.Insert(100);
	cout << "\nAfter 100" << endl << endl;
	intree.Preorder(cout);
	intree.Insert(0);
/*	cout << "\nAfter 10" << endl << endl;
	intree.Preorder(cout);
	intree.Insert(20);
	cout << "\nAfter 20" << endl << endl;
	intree.Preorder(cout);
	intree.Insert(40);
	cout << "\nAfter 40" << endl << endl;	
	intree.Preorder(cout);
	intree.Insert(30);
	cout << "\nAfter 30" << endl << endl;	
	intree.Preorder(cout);
	intree.Insert(80);
	cout << "\nAfter 80" << endl << endl;	
*/	intree.Preorder(cout);
	cout << "Deleting nonexisting node, should be ignored." << endl << endl;
	intree.Delete(-100);//deleting non existing node ignored

	cout << "Initial preorder:" << endl;
	intree.Preorder(cout);
	cout << endl;
	cout << "Depth: " << intree.Depth() << endl;

	cout << endl << endl;

	cout << "Deleting double child root 50" << endl;
	intree.Delete(50);
	intree.Preorder(cout);
	cout << endl;
	cout << "Depth: " << intree.Depth() << endl;

	cout << endl << endl;

	cout << "Deleting double child nonroot 25" << endl;
	intree.Delete(25);
	intree.Preorder(cout);
	cout << endl;
	cout << "Depth: " << intree.Depth() << endl;

	cout << endl << endl;

	cout << "Deleting single child 100" << endl;
	intree.Delete(100);
	intree.Preorder(cout);
	cout << endl;
	cout << "Depth: " << intree.Depth() << endl;

	cout << endl << endl;

	cout << "Deleting leaf 20" << endl;
	intree.Delete(20);
	intree.Preorder(cout);
	cout << endl;
	cout << "Depth: " << intree.Depth() << endl;

	cout << endl << endl;
	cout << "Finding node with value 14, should be ignored.\
\n(I return NULL on invalid finds, so I check for it in the test code)" << endl << endl;
	if(intree.Find(14))
		cout << (intree.Find(14))->Data() << endl;
	cout << "Finding node 30, printing its value (will show 30 if successful)" << endl;
	cout << (intree.Find(30))->Data() << endl;

	cout << endl << endl << "Jeeeeeeeeeeeeeeeeeeeenkiiiiiiiiiiiiins" << endl << endl;
}

