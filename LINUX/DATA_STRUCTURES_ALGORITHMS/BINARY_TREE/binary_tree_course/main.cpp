#include "BinTreeNode.h"
#include "BinaryTree.h" // 二叉链表类

int main(void) {
  BinTreeNode<char> *p;
  char pre[] = {'A', 'B', 'D', 'E', 'G', 'H', 'C', 'F', 'I'}; // 先序序列
  char in[] = {'D', 'B', 'G', 'E', 'H', 'A', 'C', 'F', 'I'};  // 中序序列
  int n = 9;                                                  // 结点个数
  BinaryTree<char> bt;
  char c = 'x', e;

  bt = CreateBinaryTree(pre, in, n); // 构造二叉树

  cout << "由先序：A,B,D,E,G,H,C,F,I和中序：D,B,G,E,H,A,C,F,I构造的二叉树:"
       << endl;
  DisplayBTWithTreeShape<char>(bt);
  cout << endl;

  while (c != '0') {
    cout << endl << "1. 统计该二叉树中叶子结点的数目.";
    cout << endl << "2. 将该二叉树中所有的结点的左右子树交换.";
    cout << endl << "3. 判断该二叉树是否为完全二叉树.";
    cout << endl << "4. 非递归中序遍历.";
    cout << endl << "5. 遍历二叉树中某一层的所有节点.";
    cout << endl
         << "6. Test CreateBinaryTree(std::string &, BinTreeNode<ElemType> * "
            "root).";
    cout << endl << "0. 退出";
    cout << endl << "选择功能(0~5):";
    cin >> c;
    switch (c) {
    case '1':
      cout << endl << "该二叉树叶子结点数目为：";
      cout << bt.LeafCount() << endl;
      break;
    case '2':
      cout << "左右子树交换前为:";
      DisplayBTWithTreeShape<char>(bt);
      bt.Revolute();
      cout << "左右子树交换后为:";
      DisplayBTWithTreeShape<char>(bt);
      break;
    case '3':
      if (bt.IsCompleteBinaryTree())
        cout << "该二叉树为完全二叉树！" << endl;
      else
        cout << "该二叉树不是完全二叉树！" << endl;
      break;
    case '4':
      cout << endl;
      bt.InOrderwithStack(Write<char>);
      cout << endl;
      break;
    case '5': {
      cout << "请输入要遍历的层数：";
      int a;
      cin >> a;
      bt.TransLevel(bt.GetRoot(), a);
      break;
    }
    case '6': {
      BinTreeNode<char> *root = new BinTreeNode<char>;
      string str = "ABC  DE G  F   ";
      CreateBinaryTreePre(str, root);
      BinaryTree<char> tree(root);
      DisplayBTWithTreeShape<char>(tree);

      break;
    }
    }
  }

  return 0;
}
