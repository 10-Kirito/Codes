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
		else       //�������ͬ��ֵ�Ͳ��ò����ˣ����ﲻ֧���ظ�ֵ
			return;

	}
}

template<typename T>
void binarySearchTree<T>::remove(T data) {
	if (root == nullptr)return;
	treeNode<T>* n = root, * parent = nullptr;	//nָ��Ҫɾ���Ľ�㣬parent��n�ĸ��ڵ�
	while (n != nullptr && n->data != data) {
		parent = n;
		if (data > n->data)n = n->right;
		else n = n->left;
	}
	if (n == nullptr) {
		std::cout << "remove() : cant find data=" << data << std::endl;
		return;
	}
	//���һ��Ҫɾ���Ľ��n�������ӽڵ�
	if (n->left != nullptr && n->right != nullptr) {
		treeNode<T>* min = n->right;		//min��n����������С�Ľ��
		treeNode<T>* min_parent = n;	//min_parent��min�ĸ��ڵ�
		while (min->left != nullptr) {
			min_parent = min;
			min = min->left;
		}
		n->data = min->data;		//����ȡ�ɽ�min��n��data���н���
		n = min;							//��ôҪɾ���Ľ��n�����min
		parent = min_parent;		//ע���ʱparent�Ѿ���min(n)�ĸ��ڵ���
		//ע������Ƚ�����ĵ㣺Ҫɾ���Ľڵ��Ѿ��� ����������data�Ľڵ� ת��Ϊ ɾ��min��
		//min�Ǿ���û���������ģ�����minֻ������һ���ӽڵ㣨������������û���ӽڵ�ģ��պ÷��������������������
		//���Խ������оͿ���ɾ��min(��n)
	}

	//�������Ҫɾ���Ľ��n����ֻ��һ���ӽڵ�
	treeNode<T>* child;			//n���ӽڵ�
	if (n->left != nullptr)
		child = n->left;
	else if (n->right != nullptr)
		child = n->right;
	else		//�������Ҫɾ���Ľ��nû���ӽڵ�
		child = nullptr;

	if (parent == nullptr)		//Ҫɾ�����Ǹ��ڵ�
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

