#include "AvlTree.h"

int main()
{
    AvlTree<int> tree;
    int value;
    int tmp;
    cout << "��������������������(-1����)��" << endl;
    while (cin >> value)
    {
        if (value == -1)
            break;
        tree.Insert(tree.root, value);
    }
    cout << "�������";
    tree.InorderTraversal(tree.root);
    cout << "\nǰ�����:";
    tree.PreorderTraversal(tree.root);
    cout << "\n������Ҫ���ҵĽ�㣺";
    cin >> tmp;
    if (tree.Contains(tree.root, tmp))
        cout << "�Ѳ��ҵ�" << endl;
    else
        cout << "ֵΪ" << tmp << "�Ľ�㲻����" << endl;
    cout << "������Ҫɾ���Ľ�㣺";
    cin >> tmp;
    tree.Delete(tree.root, tmp);
    cout << "ɾ��������������";
    tree.InorderTraversal(tree.root);
    cout << "\nɾ�����ǰ�������";
    tree.PreorderTraversal(tree.root);
}