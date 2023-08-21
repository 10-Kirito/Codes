#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Create a new window
    WINDOW *chatWindow = newwin(10, 50, 0, 0);

    // Print text in the window
    mvwprintw(chatWindow, 1, 1, "Welcome to the Chat App!");
    mvwprintw(chatWindow, 2, 1, "User1: Hello, world!");
    
    // Refresh the window to display changes
    wrefresh(chatWindow);

    // Wait for user input and exit when 'q' is pressed
    int ch = getch();
    while (ch != 'q') {
        ch = getch();
    }

    // Clean up and exit
    delwin(chatWindow);
    endwin();
    return 0;
}

