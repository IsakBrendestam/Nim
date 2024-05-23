#include <time.h>		// time
#include <stdio.h>		// printf
#include <stdlib.h>		// rand, srand, malloc
#include <string.h>		// memset

#define MAX_PINS 10

int nPiles;
int* board;

int RandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}

void GenerateBoard()
{
	printf("Enter number of piles: ");
	scanf("%d", &nPiles);

	board = malloc(nPiles * sizeof(int));

	for (int i = 0; i < nPiles; i++)
		board[i] = RandomNumber(1, MAX_PINS);
}

void PrintBoard()
{
	printf("--- Board ---\n");
	for (int i = 0; i < nPiles; i++)
	{
		printf("Pile %d: ", i+1);
		for (int _ = 0; _ < board[i]; _++)
			printf("*");
		printf("\n");
	}
	printf("-------------\n");
}

char PlayerAction()
{
	int pileIndex;
	printf("Chose a pile: ");
	scanf("%d", &pileIndex);
	pileIndex -= 1;


	if (pileIndex >= nPiles)
		return -1;

	printf("Chose number of sticks to remove: ");
	int stickCount;
	scanf("%d", &stickCount);

	if (stickCount > board[pileIndex])
		return -2;

	board[pileIndex] -= stickCount;

	return 0;
}

int BoardSum()
{
	int sum = 0;
	for (int i = 0; i < nPiles; i++)
		sum += board[i];	
	return sum;
}

int main()
{
	srand(time(NULL));

	printf("-----------------------------------\n");
	printf("|     Welcome to the game Nim     |\n");
	printf("-----------------------------------\n\n");

	GenerateBoard();

	PrintBoard();

	while (BoardSum() > 0)
	{
		if (PlayerAction() != 0)
			printf("[Input Error]");

		PrintBoard();
	}


	free(board);

	return 0;
}
