
#include <iostream>

#include "Tree.h"
#include <string>
using namespace std;






void LineInput(CTree<int> & tree, bool &echo , bool &complete);

void Run(CTree<int> & tree );

int main()
{
	
	CTree<int> test;
	/*
	test.Preorder( cout );cout<<"\n"<<endl;
	Build( test );
	test.Preorder(cout);cout<<"\n"<<endl;
	TestDestroy( test);
	*/

	Run(test);
	

}

void Run(CTree<int> & tree )
{
	int cmd_count = 0;
	bool echo = true;
	bool complete = false;
	while( !cin.eof() && ! complete )
	{
		if(echo) cout<<"cmd: "<<cmd_count<<" ";
		LineInput(tree, echo, complete);
		cout<<"\ntree: ";
		tree.Preorder(cout);
		if(echo) cout<<"\n";
		cmd_count++;
	}

}


/////////////////////////////////////////////////////////////////////////////////////////////////

// valid commands
// 
/*
	i X 
		-insert x
	d X
		-delete x
	p
		-print tree
	im N X
		- insert n  folowed by n x numbers
	dm N X
		- delte n  folowed by n x numbers
	echo on
		- turns on echo so can see what commands are
	echo off
		- turns off echo so wont see commands
	

*/

void LineInput(CTree<int> & tree , bool &echo, bool & complete)
{
	string action;
	
	int  temp;
	cin>>action;
	
	if( echo )cout<<action<<" ";
	
	if( action == "i" )
	{
		cout<<"did i make it here?"<<endl;
		cin>>temp;
		cout<<"dfsdfls;df";
		if( echo )cout<<temp;
		tree.Insert(temp);
	
	}
	else if( action =="d")
	{
		cin>>temp;
		if( echo )cout<<temp;
		tree.Delete(temp);
	}
	else if( action == "p" )
	{
		tree.Preorder(cout);
	}
	else if( action == "im" )
	{
		int i;
		cin>>i;
		if( echo ) cout<<i<<" ";
		for( ; i>0 ; i --)
		{
			cin>>temp;
			if( echo ) cout<<temp<<" ";
			tree.Insert(temp);
		}
	}
	else if (action =="dm")
	{
		int i;
		cin>>i;
		if( echo ) cout<<i<<" ";
		for( ; i>0 ; i --)
		{
			cin>>temp;
			if( echo ) cout<<temp<<" ";
			tree.Delete(temp);
		}
	}
	else if( action =="echo" )
	{
		cin>>action;

		if( true )cout<<" "<<action;
		if( action =="off" )
		{
			echo = false;
		}
		else if ( action =="on" )
		{
			echo = true;
		}
		cout<<"???"<<endl;
	}
	else if( action == "end" )
	{
		complete = true;
	}
	else
	{
		cout<<"FAILURE"<<endl;
	}
	cout<<"!";
}


/////////////////////////////////////////////////////////////////////////////////////////////////



void Print( CTree<int> & tree )
{
	

}

void Build( CTree<int> & tree )
{
	tree.Insert(4);
	tree.Insert(2);
	tree.Insert(6);
	tree.Insert(1);
	tree.Insert(3);
	tree.Insert(5);
	tree.Insert(7);

}


void TestDestroy(CTree<int> & tree )
{
	tree.Delete(1);
	tree.Delete(2);
	tree.Delete(6);
	tree.Delete(4);

}
