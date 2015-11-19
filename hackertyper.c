#include <stdio.h>
#include <curses.h>
int row, column;
int terminal_row, terminal_column;
void new_line() {
	column = 0;
	row++;
	move(row, column);
	if (row >= terminal_row) {
		row = 0;
		column = 0;
		move(row, column);
	}
	clrtoeol();
	
}
void draw(char c) {
	if (c == '\n') {
		new_line();
	} else if (c == '\t') {
		column += 4;
	} else {
		move(row, column);
		delch();
		insch(c);
		refresh();
		column++;
		if(column >= terminal_column) {
			new_line();
		}
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Please enter a valid filename:\nFormat: hackertyper <filename>\n");
		return 1;
	}
	WINDOW* wnd;
	wnd = initscr();
	cbreak();
	noecho();
	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(1));
	}
	FILE* inputfile = fopen(argv[1], "r");
	char tmp;
	row, column = 0;
	getmaxyx(wnd, terminal_row, terminal_column);
	refresh();
	tmp = getc(inputfile);
	while(tmp != EOF) {
		if (getch() == 'q') break;
		int i = 0;

		draw(tmp);
		tmp = getc(inputfile);
			
	}
	if (has_colors()) {
		attroff(COLOR_PAIR(1));
	}
	fclose(inputfile);
	endwin();
	printf("Hack completed!\n");
	return 0;
}
