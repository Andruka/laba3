#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string.h>
#include <map>
#include <arpa/inet.h>
#include "node.h"
using namespace std;
class Huff
{
	uint32_t frequency[256];
	map <unsigned char,vector<bool> > optcode;
	vector <bool> code;
	int length;
	Node* parent;
	Node* temp;
   public:
	Huff();
	void CodeForPacker(Node *ob);
	int BuildThree();
	int packer(const char * ifile,const char * ofile);
	int unpacker(const char * ifile,const char * ofile);
};
