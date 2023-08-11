#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "shell.h"

// 初始化，创建子进程运行shell

void init(void){
  uint32_t ret_pid = fork();
  if (ret_pid) {
    while (1);
  }else {
    my_shell();
  }
}

int main (void)
{
  system("clear");  
  init();
  return 0;
}


