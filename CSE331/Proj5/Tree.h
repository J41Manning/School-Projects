#ifndef CTREE_H
#define CTREE_H

#include <iostream>
using namespace std;

template<class T> class CTree
{
public:
    CTree() {m_root = 0;}
    ~CTree() {delete m_root;}

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;  m_height=0;  m_deleted=false;}
        Node(const T &t) {m_payload = t;  m_ll = 0;  m_rl = 0;  m_height=0;  m_deleted=false;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_payload;}
        const T &Data() const {return m_payload;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        int     m_height;
        bool    m_deleted;
        T       m_payload;
    };


    /*Insert function
     * Calls the Insert recusive function on the root node
     \param the payload of the node to be inserted
    */
    void Insert(const T &t) {
	InsertRecursive(t, &m_root);
    }

    /*Insert Recursive function
     \param a double pointer of a node
     \param the payload of the node to be inserted
    */
    void InsertRecursive(const T &t, Node ** node){
	if((*node)==0){*node = (new Node(t));}
	else if( t< (*node)->Data()){
	    InsertRecursive(t, &((*node)->m_ll));
	    if( Height(&((*node)->m_ll))-Height(&((*node)->m_rl))==2){

		if( t<(*node)->m_ll->Data()){	
			//DoubleRotateWithLeft(node, &(*node)->m_ll);
		}
		else{
			//DoubleDoubleWithLeft(node);
		}
            }
 	}
  	else if ((*node)->Data() <t)
	{
	    InsertRecursive(t, &((*node)->m_rl));
	    if( Height(&((*node)->m_rl))-Height(&((*node)->m_ll))==2){

		if((*node)->m_rl->Data()<t){	
			//DoubleRotateWithRight(node, &(*node)->m_rl);
		}
		else{
			//DoubleDoubleWithRight(node);
		}
            }
        }
	else if((*node)->m_deleted==true){
		(*node)->m_deleted=false;
	}
	(*node)->m_height = Max(Height(&((*node)->m_ll)),Height(&((*node)->m_rl))) +1;
    } 

    /* Heigth function
     \param double pointer of node to find height of
     \returns the height of the node or -1 if 0 (null)
    */
    int Height(Node ** node){
	return *node == 0 ? -1 : (*node)->m_height;
    }

    /*Preorder function
     * Calls the Preoder recusive function on the root node
     \param the ostream the preorder will be printed in
    */
    void Preorder(std::ostream &p_str) {
	PreorderRecursive(p_str, &m_root);
    }

    /* Preoder Depth function
     \param double pointer of node to find the preorder of
     \param the ostream the payload of each value will be printed in
    */
    void PreorderRecursive(std::ostream &p_str, Node **node){

	if(!(*node)->m_deleted){
 		p_str<<(*node)->Data() <<" ";
	}
	if((*node)->m_ll!=0)
	    PreorderRecursive(p_str, &((*node)->m_ll));
	if((*node)->m_rl!=0)
	    PreorderRecursive(p_str, &((*node)->m_rl));

    }

    /*Depth function
     * Calls the Depth recusive function on the root node
     \returns the depth
    */
    int Depth() {
	return DepthRecursive(&m_root)-1;
    }

    /* Recursive Depth function
     \param double pointer of node to find depth of
     \returns the depth
    */
    int DepthRecursive( Node **node){
	if((*node)==0){return 0;}

	int left=DepthRecursive( &((*node)->m_ll));
	int right=DepthRecursive(&((*node)->m_rl));

	if(left>right){
		return left +1;
	}
	else{
		return right+1;
	}


    }

    /* Find function
     \param t the payload of the node to be found
     \returns the node if found, 0 otherwise
    */
    const Node *Find(const T &t) const {
        Node** root=&m_root;
        while((t>(*root)->Data())||(t<(*root)->Data())){
    	     if(t>(*root)->Data() && (*root)->m_rl!=0){
		    root=&((*root)->m_rl);
	     }
	     else if(t<(*root)->Data() && (*root)->m_ll!=0){
		    root=&((*root)->m_ll);
	     }
	     else{return 0;}
        }
	if(!(*root)->m_deleted){
	     return *root;
	}
	return 0;

    }

    /* Find function
     \param t the payload of the node to be found
     \returns the node if found, 0 otherwise
    */
    Node *Find(const T &t) {
        Node** root=&m_root;
        while((t>(*root)->Data())||(t<(*root)->Data())){
    	     if(t>(*root)->Data() && (*root)->m_rl!=0){
		    root=&((*root)->m_rl);
	     }
	     else if(t<(*root)->Data() && (*root)->m_ll!=0){
		    root=&((*root)->m_ll);
	     }
	     else{return 0;}
        }
	if(!(*root)->m_deleted){
	     return *root;
	}
	return 0;
    }

    /* Deletes a node using lazy delete
     \param t the payload of the node to be deleted
    */
    void Delete(const T &t)
    {
	Node* found =Find(t);
	if(found!=0){(found)->m_deleted=true;}
    }

    /* Max function
     \param A and B are the values to be compared
     \returns the larger value, if equal returns B
    */
    int Max(int A, int B){
	if(A>B){return A;}
	else{return B;}
    }

//	Everything below this is double pointer rotations

   /* Double Pointer Single Rotation Function
    *Does a single rotation with left child
    \param double pointer to rotation node
   */   
    void DoubleRotateWithLeft(Node** root, Node ** node1){
	Node * tmp1 =(*node1)->m_rl;
	Node * tmp2 = *root;
	*root = *node1;	
	*node1 = tmp2;
	(*root)->m_rl = *node1;	
	(*node1)->m_ll = tmp1;
	tmp1= NULL;
	tmp2= NULL;
	(*root)->m_height = Max(Height(&((*root)->m_ll)),Height(&((*root)->m_rl))) +1;
	(*node1)->m_height = Max(Height(&((*node1)->m_ll)),(*root)->m_height) +1;

   }

   /* Double Pointer Single Rotation Function
    *Does a single rotation with right child
    \param double pointer to rotation node
   */   
   void DoubleRotateWithRight(Node** root, Node** node1){
	Node * tmp1 =(*node1)->m_ll;
	Node * tmp2 = *root;
	*root = *node1;	
	*node1 = tmp2;
	(*root)->m_ll = *node1;	
	(*node1)->m_rl = tmp1;
	tmp1= NULL;
	tmp2= NULL;
	(*root)->m_height = Max(Height(&((*root)->m_rl)),Height(&((*root)->m_ll))) +1;
	(*node1)->m_height = Max(Height(&((*node1)->m_rl)),(*root)->m_height) +1;
   } 

   /* Double Pointer Double Rotation Function
    *Does a double rotation with left child
    \param double pointer to rotation node
   */
   void DoubleDoubleWithLeft(Node** node){
	DoubleRotateWithRight(&((*node)->m_ll),&((*node)->m_ll->m_rl) );
	DoubleRotateWithLeft(node, &(*node)->m_ll);
   }

   /* Double Pointer Double Rotation Function
    *Does a double rotation with right child
    \param double pointer to rotation node
   */
   void DoubleDoubleWithRight(Node** node){
	DoubleRotateWithLeft(&((*node)->m_rl), &((*node)->m_rl->m_ll));
	DoubleRotateWithRight(node, &(*node)->m_rl);
   }


private:
    Node *m_root;




};

#endif
