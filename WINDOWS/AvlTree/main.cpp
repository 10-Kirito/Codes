#include "AvlTree.h"

int main()
{
    AvlTree<int> tree;
    int value;
    int tmp;
    cout << "Please input numbers to set up the tree(-1 end)：" << endl;
    while (cin >> value)
    {
        if (value == -1)
            break;
        tree.Insert(tree.root,value);
    }
    cout << "中序遍历";
    tree.InorderTraversal(tree.root);
    cout << "\n前序遍历:";
    tree.PreorderTraversal(tree.root);
    cout << "\n请输入要查找的结点：";
    cin >> tmp;
    if (tree.Contains(tree.root, tmp))
        cout << "已查找到" << endl;
    else
        cout << "值为" << tmp << "的结点不存在" << endl;
    cout << "请输入要删除的结点：";
    cin >> tmp;
    tree.Delete(tree.root, tmp);
    cout << "删除后的中序遍历：";
    tree.InorderTraversal(tree.root);
    cout << "\n删除后的前序遍历：";
    tree.PreorderTraversal(tree.root);
}
