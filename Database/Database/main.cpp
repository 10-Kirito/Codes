#include "global.h"
#include "tree.h"

#include "Binary_Search_Tree.h"

#include <cstdlib>
#include <ctime>
#include <stddef.h>
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

extern "C" int main()
{
	set<int> data_set;
	vector<int> vec;
	int count_ori, count_after, number;

	// 生成100万个数据
	while (data_set.size() < 30000)
	{
		cout << "data_set.size() = " << data_set.size() << endl;
		count_ori = data_set.size();
		data_set.insert(number = rand());
		count_after = data_set.size();
		if (count_ori != count_after) { vec.push_back(number); }
	}
	cout << vec.size() << endl;

	Tree tree = nullptr;
	BTreeSearch search_result;
	clock_t start = clock();
	for (int key : vec)
	{
		BTree_search(tree, key, &search_result);
		BTree_insert(&tree, search_result._ptrNode_node, search_result._u_keyIndex, key);
	}
	clock_t end = clock();
	printf("BTree insert time=%f\n", (double)(end - start) / CLK_TCK);

	binarySearchTree<int> bst;
	start = clock();
	for (int key : vec)
	{
		bst.insert(key);
	}
	end = clock();
	printf("BSTree insert time=%f\n", (double)(end - start) / CLK_TCK);

	start = clock();
	for (int key : vec)
	{
		bst.find(key);
	}
	end = clock();
	printf("BTree search time=%f\n", (double)(end - start) / CLK_TCK);

	start = clock();
	for (int key : vec)
	{
		BTree_search(tree, key, &search_result);
	}
	end = clock();
	printf("BSTree search time=%f\n", (double)(end - start) / CLK_TCK);

	
}