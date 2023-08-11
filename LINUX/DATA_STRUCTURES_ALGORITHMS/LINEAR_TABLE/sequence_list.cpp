#include "sequence_list.h"
#include <iostream>
#include <stdexcept>

bool seq_list::insert_list(int location, int data){
  // 如果顺序表已经满了，就直接退出！
  if(isfull())
    return false;

  // 检查插入位置的合法性:
  // 规定只能插入第一个位置（此时顺序表为空）；
  // 还有插入当前顺序表的最后一个元素的后面的那个位置（即list.length() + 1）;
  // 所以说插入的位置的取值范围只能为[1, list.length() + 1];
  //
  if (location < 1 || location > length() + 1) {
    return false;
  }

  // 遍历顺序表，将第location个元素之后的所有元素依次往后面移动:
  //  注意1：
  //  这里有一个细节，就是遍历整个顺序表的时候，我们最好选择从后面往前面遍历
  //  因为这样的话，我们就不需要存储下一个要移动的元素的值了！
  //
  //  注意2：
  //  如果顺序表当前为空的话，此时就不会执行下面的循环，直接进行赋值即可.
  for (int i = length(); i >= location; --i) {
    _data[i] = _data[i - 1];
  }
  _data[location - 1] = data;
  ++_length;

  return true;
}



bool seq_list::delete_list(int location){
  // 检查当前顺序表是否为空，如果为空，返回false
  if (empty()) {
    return false;
  }

  // 检查删除元素的位置的合法性:
  // 我们可以删除元素的范围为：[1, list.length()];(因为只有这么多元素供我们删除)
  //
  if (location < 1 || location > length()) {
    return false;
  }

  // 注意1：
  // 这里和上面插入元素的时候的遍历顺序刚好相反，因为我们是删除元素，之前的元素就不需要保存了
  // 所以可以直接选择正向遍历，当然了，反方向删除也是正确的。
  // 
  for (int i = location; i <= length(); ++i) {
    _data[i - 1] = _data[i];
  }
  --_length;
  return true;
}

int seq_list::getElement(int location) {
  // 如果传进来的参数越界的话，就会抛出异常!
  if (location < 1 || location > length()) {
    throw std::logic_error("parameter out of bounds!");
  }
  // 如果当前顺序表为空的话，就会抛出异常!
  if (empty()) {
    throw std::logic_error("empty sequence list!");
  }
  return _data[--location];
}

void seq_list::print_list() {
  std::cout << "{"; 
  for (int i = 0; i < length(); ++i) {
    std::cout << _data[i];
    if (length() == 1 || i == length() - 1) {
      std::cout << "}" << std::endl;
    }else {
      std::cout << ", ";
    }
  }
  // 空顺序表的时候需要额外的打印一个}出来
  if (empty()) {
    std::cout << "}" << std::endl;
  }
}

