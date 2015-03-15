
// Name :        Graph.h
// Description : Graph class that has the euler circuit in it
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

class CGraph{
public:
	class CVertex //vertex class
	{
	public:

  	        friend class CGraph;

		CVertex(int arg) //constructor
		{
			value = arg;
			known = false;
		}

		//Add Vertex to the adjacent list
		void AddAdjacent(int arg){
			CVertex * v = Euler->InsertVertex(arg);
			adj.push_back(v);
		}

		int Data(){return value;}
		void SetGraph(CGraph* E) {Euler=E;}
		bool IsKnown(){return known;}
		void SetKnown(bool k){known=k;}
		int AdjSize() {return adj.size();}

		void RemoveFromAdjacent(CVertex* remove){
			for(unsigned i=0; i<adj.size(); i++){
				if(remove->Data()==adj[i]->Data()){ //
					adj.erase(adj.begin()+i);
					break;
				}
			}
		}
 
	private:
		vector<CVertex*> adj; //adjacent list
		bool known; //has it been found in BFS?
		int value; //the nodes "label"
		CGraph * Euler;
	};

	//constructor
	CGraph(){;}

	CVertex * InsertVertex(int arg){
		CVertex * V = Find(arg);
		if (V==NULL){
		    CVertex * adding = new CVertex(arg);
		    m_vertices.push_back(adding);
		    return adding;
		}
		return V;
	}

/*	bool IsInList( int arg){
		if(Find(arg)!=NULL){
			return true;
		}
		return false;	
	}*/
	CVertex * Find(int arg){
		for(unsigned i=0; m_vertices.size()>i; i++)
		{
			if(m_vertices[i]->Data()==arg)
				return m_vertices[i];
		}
		return NULL;
	}

	bool HasNeighbors(CVertex * V){
		for(unsigned i=0; m_vertices.size()>i; i++)
		{
			if(m_vertices[i]->adj.size()!=0)
				V= m_vertices[i];
				return false;
		}
		return true;
	}

	bool IsEulers(){
		BreadthFirstSearch(m_vertices[0]);
	     	for(unsigned i=0; m_vertices.size()>i; i++)
		{
			if(m_vertices[i]->IsKnown()==false)
				return false; //this doesn't...
			if(m_vertices[i]->AdjSize()%2!=0)
				return false; //this works
		}
	    //check for connected (BFS/DFS) and all vertices have even degree
	    return true;
	}
	/*//Add function for path and BFS!
	vector<CVertex*>  BreadthFirstSearch(){
		vector<CVertex*> Temp = m_vertices;
		vector<CVertex*> List;
		CVertex* vert;
		for(unsigned i=0; m_vertices.size()>i; i++)
		{
			m_vertices[i]->SetKnown(false);
		}
		while(!Temp.empty()){
			vert= Temp.back();
			Temp.pop_back();
			if(!vert->IsKnown()){
				List.push_back(vert);
				vert->SetKnown(true);
				for(unsigned i=0; m_vertices.size()>i; i++) 
				//such that (vert, vertice[i]) is an element of E???
				{
					if(!m_vertices[i]->IsKnown()){
						Temp.push_back(m_vertices[i]);
					}
				}
			}
		}
		return List;
	}*/

	void BreadthFirstSearch(CVertex* vert){
		for(unsigned i=0; m_vertices.size()>i; i++)
		{
			m_vertices[i]->SetKnown(false);
		}

		queue<CVertex*> Q;
		CVertex* t;
		CVertex* u;
		Q.push(vert);
		vert->SetKnown(true);

		while(!Q.empty()){
			t= Q.back();
			Q.pop();

			for(unsigned i=0; vert->adj.size()>i; i++) {
				u=vert->adj[i];
				if(!u->IsKnown()){
				    u->SetKnown(true);	
				    Q.push(u);
				}
			}			

		}
		
	}

	//Find Euler Path
	void FindPath(){
		CVertex* vert = m_vertices[0];
		list<CVertex*> MainPathList;
		list<CVertex*> SidePathList;
		vector<CVertex*> Temp = m_vertices;
		CVertex* current = vert;
		CVertex* previous = vert;
		//Q.push(vert);
		MainPathList.push_back(vert);	
		bool simple=false;
			

		while(!simple){
			if(vert->adj.size()==0){break;}
			for(unsigned i=0; previous->adj.size()>i; i++) {
				current=vert->adj[i];
				if(current==vert){
					simple=true;
					break;
				}
			}
			if(simple){break;}
			previous=current;	
			MainPathList.push_back(current);
			current->RemoveFromAdjacent(previous);
			previous->RemoveFromAdjacent(current);	

		}
	
		while(HasNeighbors(vert)){
			SidePathList.push_back(vert);//comment this out?
			previous=vert;
			current=NULL;
			while(current!=vert){
				current=previous->adj[0];
				previous=current;
				SidePathList.push_back(current);
				//This causes a seg fault
				current->RemoveFromAdjacent(previous);
				previous->RemoveFromAdjacent(current);					
			}
			for(list<CVertex*>::iterator it = MainPathList.begin(); it!= MainPathList.end(); ++it)
			{
				if((*it)->Data()==vert->Data()){
					MainPathList.splice(it, SidePathList);
					break;
				}
			}
			
			SidePathList.clear();
		}
		for(list<CVertex*>::iterator it = MainPathList.begin(); it!= MainPathList.end(); ++it)
		{
			cout<<*it;
		}	
	}


private:
	vector<CVertex*> m_vertices; //the nodes in the graph


};
#endif
