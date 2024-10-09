#include <ncurses.h>

void spiral(const int rows, const int cols, const int printDelay, const char symbol) {
  if (rows > cols) return;
  const int step = cols - rows + 2;
  int row = rows / 2;
  int col = (cols - step) / 2 + step - 1;
  for (int i = 0; i < rows; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < i + step; j++) {
        mvaddch(row, col - j, symbol);
        refresh();
        napms(printDelay);
      }
      for (int j = 0; j < i; j++) {
        mvaddch(row - j - 1, col - i - step + 1, symbol);
        refresh();
        napms(printDelay);
      }
      row -= i + 1;
      col -= i + step - 1;
    }
    else {
      for (int j = 0; j < i + step; j++) {
        mvaddch(row, col + j, symbol);
        refresh();
        napms(printDelay);
      }
      for (int j = 0; j < i; j++) {
        mvaddch(row + j + 1, col + i + step - 1, symbol);
        refresh();
        napms(printDelay);
      }
      row += i + 1;
      col += i + step - 1;
    }
  }
}

int main(int argc, char* argv[]) {
  initscr();

  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  
  curs_set(0);
  
  spiral(rows, cols, 10, '@');
  
  getch();
  endwin();
  return 0;
}

