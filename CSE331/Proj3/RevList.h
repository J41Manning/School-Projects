//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H

#include <iostream>
using namespace std;

template<class T> class CRevList
{

public:
  // Constructor.  Sets to an empty list.
  CRevList() 
  {
	m_count=0;
	m_reversed=false;
	m_called=false;
	m_head = new Node(NULL);
	m_tail = new Node(NULL);
	m_head->m_next = m_tail;
	m_tail->m_next = NULL;
	m_tail->m_prev = m_head;
	m_head->m_prev = NULL;	
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  {
	Clear();
  	delete m_head;
 	delete m_tail;
 	m_head = NULL;
  	m_tail = NULL;
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {

	T X;
	m_count =0;
	m_reversed=false;
	m_called=false;
	m_head = new Node(NULL);
	m_tail = new Node(NULL);
	m_head->m_next = m_tail;
	m_tail->m_next = NULL;
	m_tail->m_prev = m_head;
	m_head->m_prev = NULL;
	Node * Curr = b.m_head->m_next;

  	for (unsigned I=0; I<b.m_count; I++)
   	{
      		X=Curr->m_payload;
      		PushBack(X);
      		Curr = Curr->m_next;
   	}
  }

  // Assignment operator.  Copies another list.
  void operator=(const CRevList &b);

  // Clear the list.
  void Clear()
  {
	Node* Temp = m_head->m_next;

	while (m_count==0)
	{
		Node* Temp = m_head->m_next;
		delete Temp;
		m_count--;
	}
	m_head->m_next = m_tail;
	m_tail->m_prev = m_head;
  }


  //
  // class Node
  // The nested node class for objects in our linked list.
  //
  // YOU MAY NOT MODIFY THIS CLASS!
  class Node 
  {
  public:
    friend class CRevList;
  
    Node() {m_next = 0;  m_prev = 0;}
    Node(const T &t) {m_payload = t;  m_next = 0;  m_prev = 0;}
  
    T Data() {return m_payload;}
    const T Data() const {return m_payload;}
  
  private:
    Node    *m_next;
    Node    *m_prev;
    T       m_payload;
  };


  
  // Determines if the list is empty
  bool IsEmpty() const {return(m_count==0);}

  //methods to add data to the front or the back of the list
  void PushFront(const T &t) {
	if(!m_reversed || m_called)
 	{
		Node* NewNode = new Node;
		Node* Next = m_head->m_next;
   		m_head->m_next = NewNode;
      		NewNode->m_next = Next;
      		NewNode->m_prev = m_head;
      		Next->m_prev = NewNode;
      		NewNode->m_payload = t;
      		m_count++;
		if(!IsEmpty()){cout<<m_count<<endl;}
	}
	else{
		m_called=true;
		PushBack(t);
		m_called=false;
	}	
  }
  void PushBack(const T &t) {
	if(!m_reversed || m_called){
		Node* NewNode = new Node;
		Node* Prev = m_tail->m_prev;
   		Prev->m_next = NewNode;
      		NewNode->m_next = m_tail;
		NewNode->m_prev = Prev;
      		m_tail->m_prev = NewNode;
      		NewNode->m_payload = t;
      		m_count++;
	}
	else{
		m_called=true;
		PushFront(t);
		m_called=false;
	}	
  }
  void PopFront() {
	if(!m_reversed || m_called){
		if(!IsEmpty()){
			Node * Curr = m_head->m_next;
   			Node * Next = Curr->m_next;
      			m_head->m_next = Next;
      			Next->m_prev = m_head;
			m_count--;
		}
	}
	else{
		m_called=true;
		PopBack();
		m_called=false;
	}	
  }
  void PopBack() {
	if(!m_reversed || m_called){
		if(!IsEmpty()){
			Node * Curr = m_tail->m_prev;
   			Node * Prev = Curr->m_prev;
      			Prev->m_next = m_tail;
      			m_tail->m_prev = Prev;
			m_count--;
		}
	}
	else{
		m_called=true;
		PopFront();
		m_called=false;
	}	
  }

  //Get a pointer to the first node in the list
  const Node *Begin() const {
	if(m_reversed && !m_called){
		m_called=true;
		return End();
	}
	if(!IsEmpty()){
		m_called=false;
		return m_head->m_next;
	}
	return NULL;	
  }
  Node *Begin() {
	if(m_reversed && !m_called){
		m_called=true;
		return End();
	}
	if(!IsEmpty()){
		m_called=false;
		return m_head->m_next;
	}
	return NULL;	
  }

  //get a pointer to the last node in the list
  const Node *End() const {
	if(m_reversed && !m_called){
		m_called=true;
		return Begin();
	}
	if(!IsEmpty()){
		m_called=false;
		return m_tail->m_prev;
	}
	return NULL;
  }
  Node *End() {
	if(m_reversed && !m_called){
		m_called=true;
		return Begin();
	}
	if(!IsEmpty()){
		m_called=false;
		return m_tail->m_prev;
	}
	return NULL;	
  }

  //get a pointer to node next in the list
  //If last element, returns first
  const Node *Next(const Node *n) const {
	if(n==NULL){return NULL;}
	if(m_count<=1){return NULL;}
	if(m_reversed){
		if(n->m_prev==m_head){
			return m_tail->m_prev;
		}
		return n->m_prev;
	}
	if(n->m_next==m_tail){
		return m_head->m_next;	
	}
	return n->m_next;

  }
  Node *Next(const Node *n) {
	if(n==NULL){return NULL;}
	if(m_count<=1){return NULL;}              
	if(m_reversed){
		if(n->m_prev==m_head){
			return m_tail->m_prev;
		}
		return n->m_prev;
	}
	if(n->m_next==m_tail){
		return m_head->m_next;	
	}
	return n->m_next;
  }

  //Find a node with the specified key
  const Node *Find(const T &t) const {

  }
  Node *Find(const T &t) {
	Node* Curr = m_head->m_next;
  	for (unsigned J=0; J<m_count; J++)
   	{
		if(Curr->m_payload==t){
			return Curr;
		}
		Curr=Curr->m_next;
   	}
	return NULL;
  }

  //Delete the given node
  void Delete(Node *n){
	if(IsEmpty() || n==NULL){}
	else{
		Node * Prev = n->m_prev;
		Node * Next = n->m_next;
		Prev->m_next = Next;
		Next->m_prev = Prev;
		delete n;
		m_count--;
	}
  }


  //Reverse the list in O(1) time
  void Reverse() {m_reversed= !m_reversed;}
  

private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation

  Node*    m_head;             // Head node
  Node*    m_tail;             // Tail node
  int 	  m_count;	      //Number of elements in the list
  bool    m_reversed;	       //True if reversed, elsewise false;
  bool    m_called;		//True if called, elsewise false;
};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{
	T X;
	Node * Curr = b.m_head->m_next;	
	if(this != b)
	{
		this.clear();

		while( Curr!=b.m_tail){
	      		X=Curr->m_payload;
	      		PushBack(X);
	      		Curr = Curr->m_next;
	   	}
	}

}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}


#endif
