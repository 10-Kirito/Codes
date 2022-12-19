#pragma once
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>

template <typename T>
struct treeNode {
	T data;
	treeNode<T>* left = nullptr;
	treeNode<T>* right = nullptr;
	treeNode(T data) {
		this->data = data;
	}
};

template<typename T>
class binarySearchTree {
private:
	treeNode<T>* root = nullptr;

public:
	treeNode<T>* find(T data);
	void insert(T data);
	void remove(T data);
	void preorder();
	void inorder();
	void postorder();
private:
	void preorder(treeNode<T>* node);
	void inorder(treeNode<T>* node);
	void postorder(treeNode<T>* node);
};


template<typename T>
treeNode<T>* binarySearchTree<T>::find(T data) {
	treeNode<T>* n = root;
	while (n != nullptr) {
		if (data > n->data)n = n->right;
		else if (data < n->data)n = n->left;
		else return n;
	}
	return nullptr;
}

template<typename T>
void binarySearchTree<T>::insert(T data) {
	if (root == nullptr) {
		root = new treeNode<T>(data);
		return;
	}
	treeNode<T>* n = root;
	while (n != nullptr) {
		if (data > n->data) {
			if (n->right == nullptr) {
				// std::cout << n->data << "->right=" << data << std::endl;
				n->right = new treeNode<T>(data);
				return;
			}
			n = n->right;
		}
		else if (data < n->data) {
			if (n->left == nullptr) {
				// std::cout << n->data << "->left=" << data << std::endl;
				n->left = new treeNode<T>(data);
				return;
			}
			n = n->left;
		}
		else       //如果是相同的值就不用插入了，这里不支持重复值
			return;

	}
}

template<typename T>
void binarySearchTree<T>::remove(T data) {
	if (root == nullptr)return;
	treeNode<T>* n = root, * parent = nullptr;	//n指向要删除的结点，parent是n的父节点
	while (n != nullptr && n->data != data) {
		parent = n;
		if (data > n->data)n = n->right;
		else n = n->left;
	}
	if (n == nullptr) {
		std::cout << "remove() : cant find data=" << data << std::endl;
		return;
	}
	//情况一：要删除的结点n有两个子节点
	if (n->left != nullptr && n->right != nullptr) {
		treeNode<T>* min = n->right;		//min：n右子树中最小的结点
		treeNode<T>* min_parent = n;	//min_parent：min的父节点
		while (min->left != nullptr) {
			min_parent = min;
			min = min->left;
		}
		n->data = min->data;		//这里取巧将min和n的data进行交换
		n = min;							//那么要删除的结点n变成了min
		parent = min_parent;		//注意此时parent已经是min(n)的父节点了
		//注意这里比较巧妙的点：要删除的节点已经从 参数给定的data的节点 转移为 删除min了
		//min是绝对没有左子树的，所以min只能是有一个子节点（右子树）或者没有子节点的，刚好符合下面的情况二和情况三
		//所以接着运行就可以删除min(即n)
	}

	//情况二：要删除的结点n有且只有一个子节点
	treeNode<T>* child;			//n的子节点
	if (n->left != nullptr)
		child = n->left;
	else if (n->right != nullptr)
		child = n->right;
	else		//情况三：要删除的结点n没有子节点
		child = nullptr;

	if (parent == nullptr)		//要删除的是根节点
		root = child;
	else if (parent->left == n)
		parent->left = child;
	else
		parent->right = child;

	delete n;
}

template<typename T>
void binarySearchTree<T>::preorder() {
	if (root == nullptr)return;
	preorder(root);
	std::cout << std::endl;
}

template<typename T>
void binarySearchTree<T>::inorder() {
	if (root == nullptr)return;
	inorder(root);
	std::cout << std::endl;
}

template<typename T>
void binarySearchTree<T>::postorder() {
	if (root == nullptr)return;
	postorder(root);
	std::cout << std::endl;
}

template<typename T>
void binarySearchTree<T>::preorder(treeNode<T>* node) {
	if (node == nullptr)return;
	std::cout << node->data << " ";
	preorder(node->left);
	preorder(node->right);
}

template<typename T>
void binarySearchTree<T>::inorder(treeNode<T>* node) {
	if (node == nullptr)return;
	inorder(node->left);
	std::cout << node->data << " ";
	inorder(node->right);
}

template<typename T>
void binarySearchTree<T>::postorder(treeNode<T>* node) {
	if (node == nullptr)return;
	postorder(node->left);
	postorder(node->right);
	std::cout << node->data << " ";
}


#endif

