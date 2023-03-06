#include <stdio.h>

int runPenguinBot(int argumentAmount, char** arguments) {
	printf("Penguin bot is working\nArguments:\n");
	for (int i = 0; i < argumentAmount; i++)
		printf("%s", arguments[i]);
}