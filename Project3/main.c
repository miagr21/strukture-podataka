#define _CRT_SECURE_NO_WARNINGS
#define OK 0
#define MALLOC_ERROR -1
#define EMPTY_LIST -2
#define FILE_NOT_FOUND -3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Napisati program koji iz datoteke „zaposlenici.txt" cita informacije o odjelu, imenu i prezimenu,
//te datumu zaposlenja nekog zaposlenika. Iz procitanih podataka potrebno je izgraditi jednostruko vezanu listu u kojoj ce elementi biti sortirani prvo odjelu, a zatim po prezimenu i
//imenu zaposlenika. Ispisati listu.
//Ocjena 2:
//Potrebno je pronaci pet osoba koje najduze zaposlene i ispisati ih.
//Ociena 3:
//Potrebno je pronaci pet osoba koje najduze zaposlene i pomaknuti ih na kraj liste na nacin da budu sortirane po datumu zaposlenja.


typedef char string[20];

typedef struct datum {
	int day;
	int month;
	int year;
}datum;

typedef struct worker* point;
typedef struct worker {
	string odjel;
	string name;
	string surn;
	datum date;
	point next;
}worker;

point create(string odjel, string name, string surn, int day, int month, int year) {
	point new = malloc(sizeof(worker));
	if (new == NULL) {
		printf("\t!unsuccessfull alocation!\t");
		return MALLOC_ERROR;
	}
	strcpy(new->odjel, odjel);
	strcpy(new->name, name);
	strcpy(new->surn, surn);
	new->date.day = day;
	new->date.month = month;
	new->date.year = year;
	new->next = NULL;
	return new;
}

int insertSort(point head, string odjel, string name, string surn, int day, int month, int year) {
	if (head == NULL) {
		return EMPTY_LIST;
	}
	point new = create(odjel, name, surn, day, month, year);
	point temp = head;

	if (temp->next == NULL || (strcmp(temp->next->odjel, odjel) > 0 || (strcmp(temp->next->odjel, odjel) == 0 && (strcmp(temp->next->surn, surn) > 0 || (strcmp(temp->next->surn,surn)== 0 && (strcmp(temp->next->name, name) > 0)))))) {
		new->next = temp->next;
		temp->next = new;
	}
	else {
		while (temp->next != NULL && (strcmp(temp->next->odjel, odjel) < 0 || (strcmp(temp->next->odjel, odjel) == 0 && (strcmp(temp->next->surn, surn) < 0 || (strcmp(temp->next->surn, surn) == 0 && (strcmp(temp->next->name, name) < 0)))))) {
			temp = temp->next;
		}
		new->next = temp->next;
		temp->next = new;
	}
	return OK;
}

int datumSort(point head, string odjel, string name, string surn, int day, int month, int year) {
	if (head == NULL) {
		return EMPTY_LIST;
	}
	point new = create(odjel, name, surn, day, month, year);
	point temp = head;

	if (temp->next == NULL || (temp->next->date.year > year || (temp->next->date.year == year && temp->next->date.month > month || (temp->next->date.month == month && temp->next->date.day > day)))) {
		new->next = temp->next;
		temp->next = new;
	}
	else {
		while (temp->next != NULL && (temp->next->date.year < year || (temp->next->date.year == year && temp->next->date.month < month || (temp->next->date.month == month && temp->next->date.day < day)))) {
			temp = temp->next;
		}
		new->next = temp->next;
		temp->next = new;
	}
	return OK;
}

int print(point head) {
	if (head == NULL) {
		return EMPTY_LIST;
	}
	point temp = head->next;
	
	while (temp != NULL) {
		printf("%s, %s %s  %d/%d/%d\n", temp->odjel, temp->surn, temp->name, temp->date.year, temp->date.month,temp->date.day);
		temp = temp->next;
	}
	return OK;
}
int addLast(point head, string odjel, string name, string surn, int day, int month, int year) {
	if (head == NULL) {
		return EMPTY_LIST;
	}
	point new = create(odjel, name, surn, day, month, year);
	point t = head;
	while (t->next != NULL) {
		t = t->next;
	}
	t->next = new;
	return OK;
}

int delete(point head, string name) {
	if (head == NULL) {
		return EMPTY_LIST;
	}
	point n = head->next;
	point prev = head;
	while (n != NULL) {
		if (strcmp(n->name, name) == 0) {
			prev->next = n->next;
			n->next = NULL;
			free(n);
			return OK;
		}
		else {
			prev = n;
			n = n->next;
		}
	}
}

int main() {

	point head = malloc(sizeof(worker));
	if (head == NULL) {
		printf("\t!unsuccessfull alocation!\t");
		return MALLOC_ERROR;
	}
	head->next = NULL;

	point time = malloc(sizeof(worker));
	if (time == NULL) {
		printf("\t!unsuccessfull alocation!\t");
		return MALLOC_ERROR;
	}
	time->next = NULL;

	FILE* file = fopen("zaposlenici.txt", "r");
	if (file == NULL) {
		printf("\t!unsuccessfull opening of file!\t");
		return FILE_NOT_FOUND;
	}
	string name;
	string surn;
	string odjel;
	int day;
	int month;
	int year;
	while (fscanf(file, "%s %s %s %d/%d/%d", odjel, name, surn, &day, &month, &year) == 6) {
		insertSort(head, odjel, name, surn, day, month, year);
		datumSort(time, odjel, name, surn, day, month, year);
	}

	print(head);
	printf("\n");
	for (int i = 0; i < 5; i++) {
		if (time->next == NULL) {
			return EMPTY_LIST;
		}
		time = time->next;
		printf("%s %s  %d/%d/%d\n",time->surn, time->name, time->date.year, time->date.month, time->date.day);
		delete(head, time->name);
		addLast(head, time->odjel, time->name, time->surn, time->date.day, time->date.month, time->date.year);
	}
	fclose(file);

	printf("\n");
	print(head);

	return OK;
}