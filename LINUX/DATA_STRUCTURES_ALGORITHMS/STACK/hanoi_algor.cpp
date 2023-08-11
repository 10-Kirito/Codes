#include <cstdio>
#include <iostream>

int c = 0;
/**
 * move n from x to y
 */
void move(char x, int n, char y) {
  printf("%i. Move disk %i from %c to %c\n", ++c, n, x, y);
}

void hanoi(int n, char x, char y, char z){
  // the n disks numbered from 1 to n from top to bottom are moved
  // to z according to the rules, and y can be used as un auxiliary tower.
  //

  if (n == 1) {
    move(x, 1, z);
  }else {
    hanoi(n-1, x, z, y);
    move(x, n, z);
    hanoi(n-1, y, x, z);
  }
}

int main (int argc, char *argv[])
{
  hanoi(4, 'x', 'y', 'z');
  return 0;
}
