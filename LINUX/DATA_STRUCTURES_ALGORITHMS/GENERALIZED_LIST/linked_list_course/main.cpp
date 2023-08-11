#include "gen_list.h" // 广义表
#include <string>

int main(void) {

  GenList<char> g, g1, temp;
  char c = '*', e;
  int i, n; // n是我们插入元素的时候要插入的位置
  Status sta;
  bool b = 1;

  while (c != '0') {
    cout << endl << "1. 生成广义表.";
    cout << endl << "2. 显示广义表.";
    cout << endl << "3. 在表头插入原子元素.";
    cout << endl << "4. 在指定位置插入原子元素.";
    cout << endl << "5. 在表头插入子表元素.";
    cout << endl << "6. 在指定位置子表元素.";
    cout << endl << "7. 删除元素.";
    cout << endl << "8. 求广义表的深度.";
    cout << endl << "9. 求广义表的长度.";
    cout << endl << "H. 求广义表的表头.";
    cout << endl << "T. 求广义表的表尾.";
    cout << endl << "S. 求广义表的表头和表尾连续操作.";
    cout << endl << "0. 退出";
    cout << endl << "选择功能(0~7):";
    cin >> c;
    switch (c) {
    case '1':
      GetChar(); // 读入输入的回车符
      cout << "请输入广义表eg: (a,(b,c)):";
      g.Input();
      break;
    case '2':
      if (!g.IsEmpty()) {
        g.Show();
        cout << endl;
        g.Reverse(g.Gethead());
        cout << "该广义表倒置之后为：" << endl;
        g.Show();
        cout << endl;
      } else
        cout << "广义表为空表。" << endl;
      break;
    case '3':
      cout << endl << "输入原子元素:";
      cin >> e;
      g.Insert(e);
      cout << endl << "请输入原子元素：";
      cin >> e;
      cout << endl << "请输入插入的位置：";
      cin >> n;
      g.Insert(n, e);
      break;
    case '4':
      cout << endl << "请输入原子元素：";
      cin >> e;
      cout << endl << "请输入插入的位置：";
      cin >> n;
      g.Insert(n, e);
      break;
    case '5':
      GetChar(); // 读入输入的回车符
      cout << "请输入子表eg: (a,(b,c)):";
      g1.Input();
      g.Insert(g1);
      break;
    case '6':
      GetChar(); // 读入输入的回车符
      cout << "请输入子表eg: (a,(b,c)):";
      g1.Input();
      cout << endl << "请输入插入位置";
      cin >> n;
      g.Insert(n, g1);
      break;
    case '7':
      cout << endl << "输入位置:";
      cin >> i;
      if (g.Delete(i) == RANGE_ERROR)
        cout << "位置范围错." << endl;
      break;
    case '8':
      cout << endl << "深度为:" << g.GetDepth() << endl;
      break;
    case '9':
      cout << endl << "长度为:" << g.GetLength() << endl;
      break;
    case 'H': // 取广义表的表头
      g1 = g.GetHead();
      g1.ShowHT(1);
      break;
    case 'T': // 取广义表的表尾
      sta = g.GetTail(g1);
      if (sta == SUCCESS)
        g1.ShowHT(0);
      else {
        cout << "该广义表为空！";
      }
      break;
    case 'S':
      g1 = g;
      e = GetChar();
      e = GetChar();
      while (e != 10) {
        if (e == 'H') {
          g1 = g1.GetHead();
          b = 1;
          /*g1.ShowHT(1);
          cout << endl;*/
        } else if (e == 'T') {
          /*temp = g1;
          sta = g1.GetTail(temp);*/
          // g1.Show();
          // cout << endl;
          sta = g1.GetTail(g1);
          // g1 = temp;
          b = 0;
          /*if (sta == SUCCESS)
                  g1.ShowHT(0);
          else {
                  cout << "该广义表为空！";
          }
          cout << endl;*/
        }
        e = GetChar();
      }
      if (b == 1)
        g1.ShowHT(1);
      else {
        if (sta == SUCCESS)
          g1.ShowHT(0);
        else {
          cout << "该广义表为空！";
        }
      }

      break;
    }
  }

  system("PAUSE"); // 调用库函数system()
  return 0;        // 返回值0, 返回操作系统
}
