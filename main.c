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
	float value;
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
	printf("Digite a descricao: ");
	fgets(userList[userListIndex].desc, 64, stdin);
	printf("Digite a quantidade: ");
	scanf("%d", &userList[userListIndex].amoult);
	printf("Digite o valor: ");
	scanf("%f", &userList[userListIndex].value);
	
	userListIndex++;
	clearScreen();
}

void handleReadAll (User userList[]) {
	clearScreen();

	printf("--- RELATORIO --- \n\n");
	for(int i = 0; i < userListIndex; i++) {
		if (userList[i].id != 0) {
			printf("ID %d \n", userList[i].id);
			printf("DESCRICAO %s", userList[i].desc);
			printf("QUANTIDADE %d \n", userList[i].amoult);
			printf("VALOR %.2f \n", userList[i].value);
			printf("\n");
		}
	}
}

void handleReadById (User userList[]) {
	clearScreen();
	
	int targetId;
	printf("Digite um ID (numero): ");
	scanf("%d", &targetId);

	for(int i = 0; i < userListIndex; i++) {
		if(targetId == userList[i].id) {
			printf("ID %d \n", userList[i].id);
			printf("DESCRICAO %s", userList[i].desc);
			printf("QUANTIDADE %d \n", userList[i].amoult);
			printf("VALOR %.2f \n", userList[i].value);
			printf("\n");
		}
	}
}

void remove_element(User *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length; i++) array[i] = array[i + 1];
}

void handleDeleteById (User userList[]) {
	clearScreen();
	
	int targetId;
	printf("Digite um ID (numero): ");
	scanf("%d", &targetId);

	for(int i = 0; i < userListIndex; i++) {
		if(targetId == userList[i].id) {
			remove_element(userList, i, userListIndex);
			return;
		}
	}
	printf("O produto nao esta cadastrado. \n");
}

void handleInput (User userList[]) {
	char input;
	scanf("%s", &input);
	getchar();

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
		handleReadById(userList);
		break;
	case 'D':
	case 'd':
		handleDeleteById(userList);
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
