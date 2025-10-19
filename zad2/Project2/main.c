#define _CRT_SECURE_NO_WARNINGS
#define FUNCTION_ERROR (-1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[20];
typedef struct person *point;

typedef struct person{ //defining a struct
	string name;
	string surn;
	int bYr;
	point next;
} person;

int addBegin(string n, string s, int yr, point head);

int addEnd(string n, string s, int yr, point head);

int printList(point head);

point findEl(string surname, point head);

int deleteEl(string surname, point head);

int main() {

	person head = {NULL};

	addBegin("Marko", "Radic", 1993, &head); //creating a list
	addEnd("Roko", "Basic", 2018, &head);
	addBegin("Dino", "Kurtovic", 1980, &head);
	addEnd("Ivana", "Boban", 1975, &head);
	addBegin("Nikola", "Tomic", 2005, &head);
	addEnd("Petra", "Novak", 2001, &head);

	printList(&head);
	
	deleteEl("Boban", &head);

	deleteEl("Tripalo", &head);

	deleteEl("Tomic", &head);

	printList(&head);

	return 0;
}

int addBegin(string n, string s, int yr, point head) { //adds an element to the beggining of the list

	point temp = malloc(sizeof(person));
	if (temp == NULL) {
		return -1;
	}

	temp->next = head->next;
	head->next = temp;

	strcpy(temp->name, n);
	strcpy(temp->surn, s);
	temp->bYr = yr;

	return 0;
}

int addEnd(string n, string s, int yr, point head) { //adds an element to the end of the list

	point temp = malloc(sizeof(person));
	if (temp == NULL) {
		return -1;
	}

	while (head->next != NULL) {
		head = head->next;
	}
	head->next = temp;
	temp->next = NULL;

	strcpy(temp->name, n);
	strcpy(temp->surn, s);
	temp->bYr = yr;

	return 0;
}

int printList(point head) { //prints the whole list

	printf("Full name:\tBirth Year:\n");

	point temp = head->next;

	while (temp != NULL) {
		printf("%s %s,\t%d\n", temp->name, temp->surn, temp->bYr);
		temp = temp->next;
	}
	printf("\n");
	return 0;
}

point findEl(string surname, point head) { //takes a surname and checks if the element is on the list

	point temp = head->next;

	while (temp != NULL) {
		if (strcmp(surname, temp->surn) == 0) {
			printf("Chosen element: %s %s, %d\n", temp->name, temp->surn, temp->bYr);
			return temp;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("ERROR! Person not found!\n");
		printf("\n");
		return -1;
	}
}

int deleteEl(string surname, point head) { //searches for an element and deletes it

	point temp = findEl(surname, head);
	if (temp == -1) {
		return -1;
	}
	while (head->next != temp) {
		head = head->next;
	}
	head->next = temp->next;
	temp->next = NULL;
	free(temp);
	temp = NULL;

	if (temp == NULL) {
		printf("Element successfully deleted.\n");
	}
	printf("\n");
	return 0;
}