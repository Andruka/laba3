#include "node.h"

using namespace std;

Node::Node(){left=right=NULL;}

Node::Node(Node *L, Node *R)
{  left =  L;
   right = R;
   freq = L->freq + R->freq;  
}

Node::Node(uint32_t q,unsigned char ch)
{
freq=q;
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
return freq > t.freq;
}
