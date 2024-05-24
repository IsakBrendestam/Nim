#include <time.h>		// time
#include <stdio.h>		// printf
#include <stdlib.h>		// rand, srand, malloc
#include <string.h>		// memset

#define MAX_PINS 10

int nPiles;
int* board;

char currentPlayer = 0;

int lastPile = 0;
int lastStickCount = 0;

void PrintTitle()
{
	printf("-----------------------------------\n");
	printf("|     Welcome to the game Nim     |\n");
	printf("-----------------------------------\n\n");
}

int RandomNumber(int min, int max)
{
	if (min == max)
		return min;

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
	system("clear");

	PrintTitle();

	printf(" Last Round: \n");
	printf(" Pile: %d\n", lastPile + 1);
	printf(" Sticks Removed: %d\n\n", lastStickCount);
	
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

	if (board[pileIndex] == 0)
		return -2;

	printf("Chose number of sticks to remove: ");
	int stickCount;
	scanf("%d", &stickCount);

	if (stickCount == 0)
		return -3;

	if (stickCount > board[pileIndex])
		return -4;

	board[pileIndex] -= stickCount;

	lastPile = pileIndex;
	lastStickCount = stickCount;

	return 0;
}

void DummyAction()
{
	for (int i = 0; i < nPiles; i++)
		if (board[i] > 0)
		{
			int stickCount = RandomNumber(1, board[i]);
			board[i] -= stickCount;

			lastPile = i;
			lastStickCount = stickCount;

			break;
		}
}

int BoardSum()
{
	int sum = 0;
	for (int i = 0; i < nPiles; i++)
		sum += board[i];	
	return sum;
}

char CheckForWinner()
{
	if (BoardSum() == 0)
	{
		printf("*** The winner is Player %d ***\n", !currentPlayer + 1);
		return 0;
	}

	return 1;
}

int main()
{
	srand(time(NULL));

	RandomNumber(1, 1);

	GenerateBoard();

	PrintBoard();

	char done = 1;
	while (done)
	{
		currentPlayer = 0;
		printf("Player %d turn!\n", currentPlayer+1);

		if (PlayerAction() != 0)
			printf("[Input Error]\n");

		PrintBoard();

		done = CheckForWinner();

		if (done != 0)
		{
			currentPlayer = 1;
			printf("Player %d turn!\n", currentPlayer+1);

			DummyAction();

			PrintBoard();

			done = CheckForWinner();
		}
	}


	free(board);

	return 0;
}
