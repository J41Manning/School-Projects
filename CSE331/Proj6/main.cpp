//
//
// Name :        main.cpp
// Description : 
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Graph.h"

using namespace std;


int main(int argc, char *argv[])
{
   ifstream IN;
   IN.open(argv[1]);

   int temp;
   CGraph* Euler = new CGraph();
   CGraph::CVertex * root;

   //add error case for no file
   //return -1 for incorrect euler circuit
   if(!IN.good()){return -1;}

   while( !IN.eof() && IN.good() )//pass each line to parser to add a node
   {

	IN>>temp; //add new vertex
	root =Euler->InsertVertex(temp);
	root->SetGraph(Euler);

   	if( IN.eof() || ! IN.good() )
   	{
	     //return -1;
   	     break;
  	}

	//Add into vertex
	while( IN.peek() != '\n' && ! IN.eof() &&IN.good())
	{
	      IN>>temp;
	      //Euler->InsertVertex(temp);
	      root->AddAdjacent(temp);

	}

    }
    IN.close();
    //This flags everything as not connected for some reason. 
    if(Euler->IsEulers()){
	Euler->FindPath();
    }
    else{
	 return -1;
    }

}


