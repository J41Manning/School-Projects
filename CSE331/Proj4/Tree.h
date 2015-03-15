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

        Node() {m_ll = 0;  m_rl = 0;m_active = true;}
        Node(const T &t) {m_payload = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_payload;}
        const T &Data() const {return m_payload;}

    private:
        Node    *m_ll;   //pointer to left node
        Node    *m_rl;   //pointer to right node
        T       m_payload;  //data stored in node

	bool m_active;
    };

    void Insert(const T &t) {
	Node* adding =  new Node(t);
	if(m_root==0){m_root=adding;}
       	else{
		Node* root=m_root;
		while(root!=0){
	    	     if(adding->Data()>root->Data()){
			if(root->m_rl==0){
			    root->m_rl=adding;}
			else{
			    root=root->m_rl;}
		     }
		     else if(adding->Data()<root->Data()){
			if(root->m_ll==0){
			    root->m_ll=adding;}
			else{
			    root=root->m_ll;}
		     }
		     else{break;}
		}
	}
    }
    void Preorder(std::ostream &p_str) {
	PreorderRecursive(p_str, m_root);
    }

    void PreorderRecursive(std::ostream &p_str, const Node *node){
 	p_str<<node->m_payload <<" ";
	if(node->m_ll!=0)
	    PreorderRecursive(p_str, node->m_ll);
	if(node->m_rl!=0)
	    PreorderRecursive(p_str, node->m_rl);

    }

    int Depth() {
	return DepthRecursive(m_root)-1;
    }

    //Recursive function for depth 
    int DepthRecursive( const Node *node){
	if(node==NULL){return 0;}

	int left=DepthRecursive( node->m_ll);
	int right=DepthRecursive(node->m_rl);

	if(left>right){
		return left +1;
	}
	else{
		return right+1;
	}


    }

    const Node *Find(const T &t) const {
        Node* root=m_root;
        while((t>root->Data())||(t<root->Data())){
    	     if(t>root->Data() && root->m_rl!=0){
		    root=root->m_rl;
	     }
	     else if(t<root->Data() && root->m_ll!=0){
		    root=root->m_ll;
	     }
	     else{return 0;}
        }
	return root;

    }
    Node *Find(const T &t) {
        Node* root=m_root;
        while((t>root->Data())||(t<root->Data())){
    	     if(t>root->Data() && root->m_rl!=0){
		    root=root->m_rl;
	     }
	     else if(t<root->Data() && root->m_ll!=0){
		    root=root->m_ll;
	     }
	     else{return 0;}
        }
	return root;

    }

    void Delete(const T &t)
    {
        Node* node=m_root;
	Node* parent =0;
	bool found = true;
        while((t>node->Data())||(t<node->Data())){
    	     if(t>node->Data() && node->m_rl!=0){
		    parent=node;
		    node= node->m_rl;
	     }
	     else if(t<node->Data() && node->m_ll!=0){
		    parent=node;
		    node= node->m_ll;
	     }
	     else{
		found=false;  //flag to show that it wasn't found
		break;
	     } 
        }
	if(found){
		//case 1-Leaf node
		if(node->m_ll==0 && node->m_rl==0){
			if(node==parent->m_ll)
			     parent->m_ll=0;
			else if(node==parent->m_rl)
			     parent->m_rl=0;
			delete node;
		}
		//case 2-1 one child to the left
		else if(node->m_ll!=0 && node->m_rl==0){
			if(node==parent->m_ll){
			     parent->m_ll=node->m_ll;	
			}
			else if(node==parent->m_rl){
			     parent->m_rl=node->m_ll;
			}
			if(parent==0){
			     m_root=node->m_ll;
			}
			node->m_ll=0;
			delete node;
		}
		//case 2-2 one child to the right
		else if(node->m_ll==0 && node->m_rl!=0){
			if(node==parent->m_ll){
			     parent->m_ll=node->m_rl;	
			}
			else if(node==parent->m_rl){
			     parent->m_rl=node->m_rl;
			}
			if(parent==0){
			     m_root=node->m_rl;
			}
			node->m_rl=0;
			delete node;

		}
		//case 3 - two children 
		else if(node->m_ll!=0 && node->m_rl!=0){
		  	
		    //See function below
		        ShiftLeft(node);		
			if(node==parent->m_ll){
			     parent->m_ll=node->m_ll;
			     node->m_ll->m_rl=node->m_rl;	
			}
			else if(node==parent->m_rl){
			     parent->m_rl=node->m_ll;
			}
			else if(parent==0){
			     m_root=node->m_ll;
			     m_root->m_rl=node->m_rl;
			}
			node->m_rl=0;
			node->m_ll=0;
			delete node;
		}

		//This should never happen.
		else{}

	}
	
    }

//Function that will reorder the tree to the left
bool ShiftLeft(Node* node){
    Node *left = node->m_ll;
    if(left->m_rl==0){return true;}
    while(node->m_ll->m_rl!=0){
	RotateCounter(node, node->m_ll);
    }
    return true;

}
    
//This rotates the left side counter-clockwise    
Node* RotateCounter(Node *parent, Node *shifted){
	Node * toMove = shifted->m_rl;
   	if(toMove->m_ll!=0){shifted=Rotate(shifted, toMove);}
	toMove = shifted->m_rl;
	parent->m_ll=toMove;
	toMove->m_ll=shifted;
	shifted->m_rl=0;
	shifted=toMove;
}

//This rotates a node clockwise
Node* Rotate(Node *parent, Node *shifted){
	Node * toMove = shifted->m_ll;
   	if(toMove->m_rl!=0){shifted=RotateCounter(shifted, toMove);}
	toMove = shifted->m_rl;
	parent->m_rl=toMove;
	toMove->m_rl=shifted;
	shifted->m_ll=0;
	shifted=toMove;
}



private:
    Node *m_root;


};


#endif
