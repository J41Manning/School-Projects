#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iterator>
#include "Graph.h"

using namespace std;
void LoadVertex(CGraph &graph, string line);
void LoadEdge(CGraph &graph, string line);

int main(int argc, char *argv[])
{
	//Test number of arguements
	if(argc != 3)
	{
		cerr << "Incorrect number of arguments." << endl;
		cerr << "\t<Prompt> dijkstra [datafile] [commandfile]" << endl;
		return 1;
	}
	//Now that everything is good, initilize and declare variables!
	CGraph map;                       //the graph we are adding everything to
	string Line = "";                 //a string to store each line of files in
	string datafile = argv[1];        //the data file inputted, the graph will be extracted from this
	string commandfile = argv[2];     //the command file inputted

	//Test to see good files
	ifstream dStream(datafile.c_str());
	ifstream cStream(commandfile.c_str());
	if(!cStream && !dStream)
	{
		cout << "Unable to open inputted files!"<< endl;
		//cin.get(); ??
		return 1;
	}

	/*Extracting the Graph from the data file!*/
	//Vertices!
	 while(!dStream.eof() && Line != "EDGES")
	 {
		getline(dStream, Line);
		if(Line == "EDGES")
			break;
		if(!(Line == "VERTICES" ||Line == ""))
			LoadVertex(map, Line);
	 }
	 Line = "";
	//Edges!
	 while(!dStream.eof())
	 {
		getline(dStream, Line);
		if(!(Line == "EDGES"||Line == ""))
			LoadEdge(map, Line);	
	 }

	Line = "";	

	/*Extracting the Command file!*/

	int Arg = 0;
	string tripType, city1, city2;

	while(!cStream.eof())
	{
             	getline(cStream, Line);
	     	switch(Arg){
	    	case 0:
			tripType=Line;
			break;
	     	case 1:
			city1 = Line;
			break;
	     	case 2:
			//We now have all the right info, call the functions
			city2 = Line;
			if(tripType == "trip"){map.Trip(city1, city2, cout);}
			else if (tripType =="quicktrip"){map.QuickTrip(city1, city2, cout);}
			else{ cerr << "Incorrect value in data file" << endl;}
			break;
		default:
			cerr<< "??????"<<endl;
			break;
		}
		Arg++;
		Arg=Arg%3;
	}
}

//Change from here down! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/* Function to load the vertex into the graph
*param graph the graph the vertex will be loaded into
*param line the string containing all info about the new vertex
*/
void LoadVertex(CGraph &graph, string line){	
	string::iterator iter;

	//Things to extract into
	int id;
	string name, type;
	string temp=""; //temp string

	iter = line.begin();
	
	//Extract the Id
	for(; *iter != ' '; iter++){
		temp += *iter;
	}
	iter += 2; //skip to name
	id = strtoul(temp.c_str(), NULL, 10);
	
	//Extract the Name
	for(; *iter != '"'; iter++){
		name += *iter;
	}
	iter += 2; //skip to type

	//Extract the type
	for(; iter != line.end(); iter++){
		type += *iter;
	}	

	//Add the Vertex to the graph!	
	graph.AddVertex(id, name, type);
}

/* Function to load the edge into the graph
*param graph the graph the edge will be loaded into
*param line the string containing all info about the new edge
*/
void LoadEdge(CGraph &graph, string line){
	string::iterator iter;

	//Elements of an Edge
	int id, source, destination;
	string name;
	float distance, speed;
	
	iter = line.begin();
	string temp;

	//Extract the id
	for(temp=""; *iter != ' '; iter++){
		temp += *iter;
	}
	iter += 1; //skip ahead
	id = strtoul(temp.c_str(), NULL, 10);

	//Extract the source vertex
	for(temp = ""; *iter != ' '; iter++)
	{
		temp += *iter;
	}
	source = strtoul(temp.c_str(), NULL, 10);
	iter += 1; //skip ahead
	
	//Extract the destination
	for(temp=""; *iter != ' '; iter++){
		temp += *iter;
	}
	destination = strtoul(temp.c_str(), NULL, 10);
	iter += 2; //skip ahead
	
	//Extract the name
	for(; *iter != '"'; iter++)
	{
		name += *iter;
	}
	iter += 2; //skip ahead
	
	//Extract the distance
	for(temp=""; *iter != ' '; iter++){
		temp += *iter;
	}
	distance = atof(temp.c_str());
	
	//grab the speedlimit
	for(temp=""; iter != line.end(); iter++){
		temp += *iter;
	}
	speed = atof(temp.c_str());
	
	//Add the Edge to the graph!
	graph.AddEdge(id, source, destination, name, distance, speed);
}






