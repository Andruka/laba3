#include "node.h"

using namespace std;

Node::Node(){left=right=NULL;}

Node::Node(Node *L, Node *R)
{  left =  L;
   right = R;
   frec = L->frec + R->frec;  
}

Node::Node(int q,unsigned char ch)
{
frec=q;
sim=ch;
left=right=NULL;
}

void Node::DeleteNode()
{
if(left!=NULL)
	{
	(*left).DeleteNode();
	delete left;
	}
if(right!=NULL)
	{
	(*right).DeleteNode();
	delete right;
	}	
}

bool Node::operator > (Node t)
{
return frec > t.frec;
}
