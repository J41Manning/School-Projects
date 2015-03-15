
// Name :        Graph.h
// Description : Graph class implements Dijstra
//
#ifndef CGRAPH_H
#define CGRAPH_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

/* Class CGraph
*  where all the vertices and edges are laoding into (nested classes)
*/
class CGraph{
public:
	//constructor
	CGraph() {}
	
	//destructor
	~CGraph()
	{
		//deletes all vertices
		for(unsigned i = 0; i < m_vertices.size(); i++){delete m_vertices[i];}
		
		//deletes all edges 
		for(unsigned j = 0; j < m_edges.size(); j++){delete m_edges[j];}
	}

	/* Nested Vertex class
	* Holds all information on each vertex
	*/
	class Vertex{
	public:
		friend class CGraph;

		//default constructor
		Vertex() {}

		//constructor 
		Vertex(int id, string name, string type) {
			m_id = id; 
			m_name = name; 
			m_type = type;
			m_priority=-1; //-1 represents infinity
		}

		//destructor
		~Vertex() {}
		
		void SetPriority(int P){m_priority = P;}

	private:
		int m_id;	        //id of the vertex
		string m_name;		//name of the vertex
		string m_type;		//type of the vertex
		int m_priority; 	//the value in the priority Vector
	};
		
	/* Nested Edge class
	* Holds all information on each edge
	*/
	class Edge{
	public:
		friend class CGraph;

		//default constructor
		Edge() {}

		//constructor
		Edge(int id, Vertex* dest, Vertex* source, string name, float distance, float speed) {
			m_id = id;
			m_destination = dest;
			m_source = source;
			m_name = name;
			m_distance = distance;
			m_speed = speed;
		}

		//destructor
		~Edge() {}

	private:
		int	   m_id;		//id of the edge
		Vertex*    m_destination;	//vertex edge is going to
		Vertex*    m_source;		//vertex edge is going from
		string     m_name;		//name of the edge
		float	   m_distance;	 	//how long the edge is
		float	   m_speed;   		//speed limit of the edge
	};

	/* Adds a vertex to the graph
	*param id the id of the new vertex
	*param name the name of the new vertex
	*param type the type of the new vertex
	*/
	void AddVertex(int id, string name, string type)
	{
		Vertex *vertex = new Vertex(id, name, type);
		m_vertices.push_back(vertex);
	}
	
	/* Adds an edge to the graph 
	*param id the id of the new edge
	*param source the vertex this edge is coming from
	*param dest the vertex this edge is going to
	*param name the name of the new edge
	*param distance the distance or length of the edge
	*param speed the max speed that can be done on this edge
	*/
	void AddEdge(int id, int source, int dest, string name, float distance, float speed )
	{
	
		//Find the appropriate vertex
		Vertex *temp1, *temp2;
		for(unsigned i = 0; i < m_vertices.size(); i++)
		{
			if(m_vertices[i]->m_id == source)
			{
				temp1 = m_vertices[i];
			}
			if(m_vertices[i]->m_id == dest)
			{
				temp2 = m_vertices[i];
			}
		}
		
		Edge *edge = new Edge(id, temp1, temp2, name, distance, speed);
		m_edges.push_back(edge);
	}
		
	/* Finds the vertex with the inputted name
	*param name the name to search for
	*/
	Vertex * FindVertex(string name){
		for(unsigned i = 0; i < m_priorityVector.size(); i++){
			if(m_priorityVector[i]->m_name==name){
				return m_priorityVector[i];
			}
		}
		return NULL;
	}

	/* Resets all the Vertices in the priority list to "inf" and adds them all again
	*/
	void ResetPriority(){
		m_priorityVector.clear();
		for(unsigned j = 0; j < m_vertices.size(); j++){		
			m_priorityVector.push_back(m_vertices[j]);
		}
	}


	/* Finds the adjacent edges going away from a vertex
	*param vertex to search from
	*/
	vector<Edge *> FindAdjEdges(Vertex * V){
		vector<Edge *> found;
		for(unsigned j = 0; j < m_edges.size(); j++){
			if(m_edges[j]->m_source==V){
				found.push_back(m_edges[j]);
			}
		}
		return found;
	}

	/* Finds the vertex with the lowest priority
	*param vector of edges to search from
	*/
	 Edge *FindLowest(vector<Edge *> searching){
		Edge * lowest= searching[0];
		for(unsigned j = 0; j < searching.size(); j++){
			if(searching[j]->m_destination->m_priority < lowest->m_destination->m_priority){
				lowest = searching[j];
			}
		}
		return lowest;
	}

	/* Removes the vertex from the priority that has been searched
	*param vector of edges to search from
	*/
	 void RemovePrev(string name){
		for(unsigned i = 0; i < m_priorityVector.size(); i++){
			if(m_priorityVector[i]->m_name==name){
				m_priorityVector.erase(m_priorityVector.begin()+i);
			}
		}
	}

	/*Find the trip with shortest distance
	*param city1 the city we are come from
	*param city2 the city we are going to
	*param p_str the output stream
	*/
	void Trip(string city1, string city2, std::ostream &p_str){
		vector<Edge *> AdjEdges;

		//Reset the priority vector and find the begining and end in it
		ResetPriority();
		Vertex *vSource = FindVertex(city1);
		Vertex *vDestin = FindVertex(city2);
		Vertex *Current = vSource;
		Edge * edge = &(Edge(0, NULL, NULL, "", 0, 0));
		Edge * prevEdge;
		int totalDist =0;
		int currentDist=0;
		bool active = false;

		if(vSource==NULL || vDestin ==NULL){cerr << "The city inputted does not appear on the map"<<endl;}
		p_str<<"\nTrip from " << city1 << " to " <<city2 <<endl;

		while(m_priorityVector.size()!=0 && Current!=vDestin){
			Current->SetPriority(0);

			AdjEdges = FindAdjEdges(Current);
			
			//sets the priority value for each adjacent vertex
			for(unsigned j = 0; j < AdjEdges.size(); j++){
				Vertex * temp =AdjEdges[j]->m_destination;
				if(temp->m_priority ==-1 || AdjEdges[j]->m_distance < temp->m_priority){
					temp->SetPriority(AdjEdges[j]->m_distance);
				}
			}
			prevEdge= edge;
			edge =FindLowest(AdjEdges);
			Current = edge->m_destination;
			totalDist += edge->m_distance;

			//Printing all the trip instructions
			if (active && prevEdge->m_name != edge->m_name){
				p_str << prevEdge->m_destination->m_name << " (" << currentDist << ")\n";
				active =false;
			}
			if(Current==vDestin && !active){
				p_str<<"Take "<<edge->m_name << " from "<< edge->m_source->m_name <<" to " 
				     << edge->m_destination->m_name << " (" << edge->m_distance <<")"<<endl;	
			}else if(Current==vDestin && active){
				p_str<< edge->m_destination->m_name << " (" << currentDist <<")"<<endl;	
			}else if(!active && prevEdge->m_name != edge->m_name){
				p_str<<"Take "<<edge->m_name << " from "<< edge->m_source->m_name <<" to ";
				active=true;
				currentDist+=edge->m_distance;
			}else if (prevEdge->m_name == edge->m_name){
				currentDist+=edge->m_distance;
				active =true;
			}				

			RemovePrev(edge->m_source->m_name);
		
		}
		p_str <<"Total Distance: " << totalDist <<endl;		
	}

	/*Find the trip with shortest time
	*param city1 the city we are come from
	*param city2 the city we are going to
	*param p_str the output stream
	*/
	void QuickTrip(string city1, string city2, std::ostream &p_str){
		vector<Edge *> AdjEdges;

		//Reset the priority vector and find the begining and end in it
		ResetPriority();
		Vertex *vSource = FindVertex(city1);
		Vertex *vDestin = FindVertex(city2);
		Vertex *Current = vSource;
		Edge * edge = &(Edge(0, NULL, NULL, "", 0, 0));
		Edge * prevEdge;
		int totalTime =0;
		int currentTime=0;
		bool active = false;

		if(vSource==NULL || vDestin ==NULL){cerr << "The city inputted does not appear on the map"<<endl;}
		p_str<<"\nQuick Trip from " << city1 << " to " <<city2 <<endl;

		while(m_priorityVector.size()!=0 && Current!=vDestin){
			Current->SetPriority(0);

			AdjEdges = FindAdjEdges(Current);
			
			//sets the priority value for each adjacent vertex
			for(unsigned j = 0; j < AdjEdges.size(); j++){
				Vertex * temp =AdjEdges[j]->m_destination;
				if(temp->m_priority ==-1 || AdjEdges[j]->m_distance/AdjEdges[j]->m_speed < temp->m_priority){
					temp->SetPriority(AdjEdges[j]->m_distance/AdjEdges[j]->m_speed);
				}
			}
			prevEdge= edge;
			edge =FindLowest(AdjEdges);
			Current = edge->m_destination;
			totalTime += edge->m_distance/edge->m_speed;

			//Printing all the trip instructions
			if (active && prevEdge->m_name != edge->m_name){
				p_str << prevEdge->m_destination->m_name << " (" << currentTime << ")\n";
				active =false;
			}
			if(Current==vDestin && !active){
				p_str<<"Take "<<edge->m_name << " from "<< edge->m_source->m_name <<" to " 
				     << edge->m_destination->m_name << " (" << edge->m_distance/edge->m_speed <<")"<<endl;	
			}else if(Current==vDestin && active){
				p_str<< edge->m_destination->m_name << " (" << currentTime <<")"<<endl;	
			}else if(!active && prevEdge->m_name != edge->m_name){
				p_str<<"Take "<<edge->m_name << " from "<< edge->m_source->m_name <<" to ";
				active=true;
				currentTime+=edge->m_distance/edge->m_speed;
			}else if (prevEdge->m_name == edge->m_name){
				currentTime+=edge->m_distance/edge->m_speed;
				active =true;
			}				

			RemovePrev(edge->m_source->m_name);
		
		}
		p_str <<"Total Time: " << totalTime <<endl;		
	}

		
	

private:
	vector<Vertex *> m_vertices;		//all vertices in the graph
	vector<Vertex *> m_priorityVector;	//priority queue equilavent
	vector<Edge *> m_edges;			//all edges in the graph
		
};

#endif
