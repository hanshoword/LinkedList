#include <iostream>
#include <string>
#include "CLinkedList.h"

using namespace std;

int main()
{
	CLinkedList<int>	L;

	for (int i = 0; i < 100; i++)
	{
		L.push_back(i);
	}

	L.printList();
	cout << "Size : " << L.size() << endl;
		
	return 0;
}