#include<iostream>
#include<string>
#include<vector>

#include "DisJointSet.h"

using namespace std;

int main(int argc, char* argv[])
{
	DisJointSet<int> ds;
	for(unsigned int i=1; i<=7; ++i)
		ds.makeSet(i);

	ds.makeUnion(1, 2);
	ds.makeUnion(2, 3);
	ds.makeUnion(3, 4);
	ds.makeUnion(4, 5);
	ds.makeUnion(5, 6);
	ds.makeUnion(6, 7);

	for(unsigned int i=1; i<=7; ++i)
		cout << i << " ---> " << ds.findSet(i) << endl;

	return(0);
}
