#include <cstring>
#include <curses.h>
#include <string>
#include <ncurses.h>

int main (int argc, char *argv[])
{
  initscr();
  raw();
  noecho();

  curs_set(0);

  const char * ptr = "Hello, Kirito!";
  mvprintw(LINES / 2, (COLS - strlen(ptr)) / 2,ptr);
  mvprintw(LINES - 1, 0,"Press any key to quit!");
  refresh();

  getch();
  endwin();

  return 0;
}
