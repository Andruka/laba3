#include <inttypes.h>
#include <cstdio>

using namespace std;

class Node
{
    public:
     	uint32_t freq;
    	unsigned char sim;
    	Node *left, *right;
    	Node();
   	Node(Node *L, Node *R);
	Node(uint32_t q,unsigned char ch);
	void DeleteNode();
	bool operator > (Node t) ;
};
