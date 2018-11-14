#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<algorithm>

#include "DisJointSet.h"

using namespace std;

DisJointSet<int> ds;

void runMakeUnions(const int& option)
{
	switch(option)
	{
		case 0 : ds.makeUnion(1, 2);
			 	 ds.makeUnion(2, 3);
			     break;
		case 1 : ds.makeUnion(3, 4);
				 ds.makeUnion(4, 5);
				 break;
		case 2 : ds.makeUnion(5, 6);
				 ds.makeUnion(6, 7);
				 break;
		default : break;
	}
}

int main(int argc, char* argv[])
{
	vector<thread> threadPool;
	constexpr size_t poolSize = 3;
	threadPool.reserve(poolSize);

	for(unsigned int i=1; i<=7; ++i)
		ds.makeSet(i);

	for(unsigned int i=0; i<poolSize; ++i)
		threadPool.emplace_back(thread(runMakeUnions, i));

	for_each(threadPool.begin(), threadPool.end(), [&](thread& threadItem){ threadItem.join(); });

	for(unsigned int i=1; i<=7; ++i)
		cout << i << " ---> " << ds.findSet(i) << endl;

	return(0);
}
