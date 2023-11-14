#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define LIST_LIMIT 999

typedef struct User {
	int id;
	char desc[64];	
	int amoult;	
	int value;
} User;

int userListIndex = 0;

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

User* initiateList () {
	User *users = malloc(LIST_LIMIT);
	return users;
}

void handleCreate (User userList[]) {
	clearScreen();

	srand(time(NULL));
	int id = rand();
	userList[userListIndex].id = id;

	printf("--- CRIACAO DE PRODUTO --- \n");
	fflush(stdin);
	printf("Digite a descricao: ");
	fgets(userList[userListIndex].desc, 64, stdin);
	fflush(stdin);
	printf("Digite a quantidade: ");
	scanf("%d", &userList[userListIndex].amoult);
	fflush(stdin);
	printf("Digite o valor: ");
	scanf("%d", &userList[userListIndex].value);
	fflush(stdin);
	
	userListIndex++;
	clearScreen();
}

void handleReadAll (User userList[]) {
	clearScreen();

	printf("--- RELATORIO --- \n");
	for(int i = 0; i < userListIndex; i++) {
		printf("ID %d \n", userList[i].id);
		printf("DESCRICAO %s \n", userList[i].desc);
		printf("QUANTIDADE %d \n", userList[i].amoult);
		printf("VALOR %d \n", userList[i].value);
		printf("--- \n");
	}
}

void handleInput (User userList[]) {
	char input;
	scanf("%c", &input);
	fflush(stdin);

	switch (input)
	{
	case 'C':
	case 'c':
		handleCreate(userList);
		break;
	case 'R':
	case 'r':
		handleReadAll(userList);
		break;
	case 'U':
	case 'u':
		break;
	case 'D':
	case 'd':
		break;
	default:
		break;
	}
}

int main () {
	User* userList = initiateList();

	while (1) {
		printf("--- \n");
		printf("C - CREATE \n");
		printf("R - READ ALL \n");
		printf("U - READ BY ID \n");
		printf("D - DELETE \n");

		handleInput(userList);
	}


	return 0;
}
