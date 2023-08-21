// Resource:
// https://leetcode.com/problems/add-two-numbers/
//
// Question:
// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order, and each of their nodes
// contains a single digit. Add the two numbers and return the sum as a linked
// list. You may assume the two numbers do not contain any leading zero, except
// the number 0 itself.
//
// Example:
//
// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
// Explanation: 342 + 465 = 807.
//

// Definition for singly-linked list.
#include <iostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class List {
  ListNode *head;

public:
  List() : head{nullptr} {}
  List(ListNode *node) : head{node} {}

  void insert(const int &value) {
    if (head == nullptr) {
      head = new ListNode(value);
    } else {
      ListNode *temp = head;
      // get the last node:
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = new ListNode(value);
    }
  }

  template <typename... Argc> void insert(const int &value, Argc... more) {
    insert(value);
    insert(more...);
  }

  // get the head of list:
  ListNode *gethead() const { return head; }

  // show big numbers:
  void show_number() const {
    ListNode *node = head;
    while (node) {
      std ::cout << node->val;
      node = node->next;
    }
  }

  // invert the linked-list:
  void invert() {
    ListNode *prev = nullptr;
    ListNode *current = head;
    ListNode *next = head;

    while (next) {
      next = next->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    head = prev;
  }
};

class Solution {
public:
  // The first one solution:
  // It is wrong, because I don't consider the size of number!
  // No matter how big I set the type of number, there are always
  // numbers lager than the maximum value of this type.
  //
  // So we can't easy convert the linked-list to a number, we must
  // calculate while inserting new nodes!
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    int number_1, number_2, result;
    int temp_int = 10;
    ListNode *temp;

    // convert the two linked-lists to numbers:
    temp = l1->next;
    number_1 = l1->val;
    while (temp) {
      number_1 = number_1 + (temp->val * temp_int);
      temp = temp->next;
      temp_int *= 10;
    }

    temp_int = 10;

    temp = l2->next;
    number_2 = l2->val;
    while (temp) {
      number_2 = number_2 + (temp->val * temp_int);
      temp = temp->next;
      temp_int *= 10;
    }
    // end convert
    std::cout << "number_1 is :" << number_1 << std::endl;
    std::cout << "number_2 is :" << number_2 << std::endl;

    result = number_1 + number_2;

    std::cout << "result is :" << result << std::endl;
    // convert the result into linked-list:
    ListNode *result_list = new ListNode(result % 10);
    ListNode *temp_result = result_list;
    while ((result = result / 10)) {
      temp_result->next = new ListNode(result % 10);
      temp_result = temp_result->next;
    }
    return result_list;
  }

  // The second solution:
  ListNode *addTwoBigNumbers(ListNode *l1, ListNode *l2) const {
    // numbers on units:
    int left = l1->val, right = l2->val;
    // the carry number:
    int carry;

    // the result of single units:
    int result = left + right;
    carry = result / 10;
    result = result % 10;

    ListNode *newNode = new ListNode(result);
    ListNode *temp = newNode;

    while (l1->next || l2->next) {
      if (l1->next != nullptr) {
        left = l1->next->val;
        result += left;
        l1 = l1->next;
      }

      if (l2->next != nullptr) {
        right = l2->next->val;
        result += right;
        l2 = l2->next;
      }

      result += carry;

      carry = result / 10;
      result = result % 10;
      temp->next = new ListNode(result);
      temp = temp->next;
    }
    if (carry != 0) {
      temp->next = new ListNode(carry);
      temp = temp->next;
    }

    return newNode;
  }
};

int main(int argc, char *argv[]) {
  List l1, l2, l3, l4, l5, l6;
  l1.insert(1, 2, 3, 4);
  l2.insert(1, 2, 3, 4);
  l3.insert(2, 4, 3);
  l4.insert(5, 6, 4);
  l5.insert(1, 3, 4, 5, 6, 7);
  l6.insert(4, 5, 6, 7);

  List l7;
  std::cout << "The big number is ";
  l7.insert(2, 3, 4, 5, 6, 7, 8, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  l7.show_number();
  std::cout << std::endl;
  l7.invert();
  std::cout << "After invert the big number is ";
  l7.show_number();
  std::cout << std::endl;

  Solution solution;

  solution.addTwoNumbers(l1.gethead(), l2.gethead());
  solution.addTwoNumbers(l3.gethead(), l4.gethead());
  solution.addTwoNumbers(l5.gethead(), l6.gethead());
  l7.invert();
  std::cout << "l7 is ";
  l7.show_number();
  std::cout << std::endl << "l1 is ";
  l1.show_number();
  std::cout << std::endl;
  List l8(solution.addTwoBigNumbers(l7.gethead(), l1.gethead()));
  l8.show_number();
  std::cout << "Test the failed case:" << std::endl;

  List failed_1, failed_2;
  failed_1.insert(2, 4, 3);
  failed_2.insert(5, 6, 4);

  std::cout << "failed_1 is ";
  failed_1.invert();
  failed_1.show_number();
  failed_1.invert();
  std::cout << std::endl;

  std::cout << "failed_2 is ";
  failed_2.invert();
  failed_2.show_number();
  failed_2.invert();
  std::cout << std::endl;

  std::cout << "the result is ";
  List failed_result(solution.addTwoBigNumbers(failed_1.gethead(), failed_2.gethead()));

  failed_result.invert();
  failed_result.show_number();

  return 0;
}
