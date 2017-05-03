#include <iostream>
#include <fstream>
#include <list>
using namespace std;
class Node
{
    public:
     	int frec;
    	char sim;
    	Node *left, *right;
    	Node(){left=right=NULL;}
   	Node(Node *L, Node *R)
   	{  left =  L;
   	   right = R;
   	   frec = L->frec + R->frec;  
   	}
	Node(int q,char ch)
	{
	a=q;
	c=ch;
	left=right=NULL;
	}
	bool operator < (Node t) const
	{
	frec<t.frec;
	}
};
