#include <stdlib.h>
#include <conio.h>

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void getChar() {
#ifdef _WIN32
	_getch();
#else
	getchar();
#endif
}