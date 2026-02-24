#define _CRT_SECURE_NO_WARNINGS
#define MALLOC_ERROR NULL
#define FILE_NOT_FOUND -2
#define EMPTY_LIST -3
#define OK 0
#define NOT_FOUND 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*Napisati program koji generira dvije vezane liste. Za svaku od listi je potrebno generirati 20 slucajnih brojeva i to:
• vrijednosti od 50 do 75 za prvu listu
• vrijednosti od 60 do 85 za drugu listu,
pri cemu se vrijednosti unutar jedne liste ne smiju ponavljati i novi element je potrebno dodavati na pocetak liste. Ispisati obje liste.
Iz listi izbrisati samo one vrijednosti koje se pojavljuju u obje liste. Ispisati koja se
vrijednost brise i ispisati obje liste nakon brisanja.
U obje liste pronaci 5 najvecih vrijednosti i pomaknuti ih na pocetak liste.*/

typedef struct list* point;
typedef struct list {
	int num;
	point next;
}list;

point create(int num) {

	point new = malloc(sizeof(list));
	if (new == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	new->num = num;
	new->next = NULL;
	return new;
}

int addFront(point head, int num) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point new = create(num);
	new->next = head->next;
	head->next = new;
	return OK;
}

int print(point head) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point n = head->next;
	while (n != NULL) {
		printf("%d, ", n->num);
		n = n->next;
	}
	printf("\n");
	return OK;
}

int exist(point head, int num) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point n = head->next;
	while(n != NULL){
		if (n->num == num) {
			return 1;
		}
		n = n->next;
	}
	return 0;
}

int delete(point head, int num) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point prev = head;
	point n = head->next;

	while (n!= NULL) {
		if (n->num == num) {
			prev->next = n->next;
			n->next = NULL;
			free(n);
			return OK;
		}
		prev = n;
		n = n->next;
	}
	return NOT_FOUND;
}

int deleteDouble(point head1, point head2) {
	if (head1 == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	if (head2 == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point i = head1->next;

	while (i != NULL) {
		int currentNum = i->num;
		point next = i->next;
		if (exist(head2, currentNum) == 1) {
			printf("brisanje elementa %d...\n", currentNum);
			delete(head1, currentNum);
			delete(head2, currentNum);
		}
		i = next;
	}
	return OK;

}

int sort(point head, int num) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point new = create(num);
	point n = head;
	if (n->next == NULL || n->next->num < num) {
		new->next = n->next;
		n->next = new;
		return OK;
	}
	while (n->next != NULL && n->next->num > num) {
		n = n->next;
	}
	new->next = n->next;
	n->next = new;
	return OK;
}

int print5(point head) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	point temp = head->next;
	for (int i = 0; i < 5; i++) {
		printf("%d, ", temp->num);
		temp = temp->next;

	}
		printf("\n");
	return OK;
}

int main() {
	srand((unsigned)time(NULL));

	point list1 = malloc(sizeof(list));
	if (list1 == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	list1->next = NULL;

	point list2 = malloc(sizeof(list));
	if (list2 == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	list2->next = NULL;

	point sort1 = malloc(sizeof(list));
	if (sort1 == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	sort1->next = NULL;

	point sort2 = malloc(sizeof(list));
	if (sort2 == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	sort2->next = NULL;

	for (int i = 0; i < 20; i++) {


	int num1 = rand() % 26 + 50;
		while (exist(list1, num1)) {
			num1 = rand() % 26 + 50;
		}
		addFront(list1, num1);
		sort(sort1, num1);

	int num2 = rand() % 26 + 60;
		while (exist(list2, num2)) {
			num2 = rand() % 26 + 60;
		}
		addFront(list2, num2);
		sort(sort2, num2);
	}
	print(list1);
	print(list2);

	print5(sort1);
	print5(sort2);

	deleteDouble(list1, list2);

	return OK;
}