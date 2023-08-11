#include "Binary_Search_Tree.h"

using namespace std;
int main()
{
	binarySearchTree<int> tree;
	int arr[] = { 6,7,8,9,2,3,0,1,4,5 };
	int size = 10;
	for (int i = 0; i < size; i++)
	{
		tree.insert(arr[i]);
	}

	treeNode<int> * p = nullptr;
	p = tree.find(6);

	if (p != nullptr)
	{
		cout << "Find successfully!" << endl;
		cout << p->data<<endl;
	}

	tree.remove(0);

	return 0;
}