#include <inttypes.h>
#include <cstdio>

using namespace std;

class Node
{
    public:
     	int frec;
    	unsigned char sim;
    	Node *left, *right;
    	Node();
   	Node(Node *L, Node *R);
	Node(int q,unsigned char ch);
	void DeleteNode();
	bool operator > (Node t) ;
};
