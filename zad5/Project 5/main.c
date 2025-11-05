#define _CRT_SECURE_NO_WARNINGS
#define FUNCTION_ERROR (-1)
#include <stdio.h>
#include <stdlib.h>

typedef struct stog* point;

typedef struct stog {
	int number;
	point next;
}stog;

int push(int num, point head) {

	if (head == NULL) {
		return -1;
	}
	point q = head;

	point temp = malloc(sizeof(stog));
	temp->number = num;

	while (q->next != NULL) {
		q = q->next;
	}
	q->next = temp;
	temp->next = NULL;

	return 1;
}

int pop(point head) {

	if (head == NULL) {
		return -1;
	}
	point temp = head;
	while (temp->next->next != NULL) {
		temp = temp->next;
	}
	int num = temp->next->number;

	temp->next->next = NULL;
	free(temp->next);
	temp->next = NULL;
	
	return num;
}

int chToNum(char symbol) {

	int num;
	char a = '0';
	num = (int)symbol - (int)a;

	return num;
}

int calPostfix(point head) {

	if (head == NULL) {
		return -1;
	}
	int a;
	int b;
	char symbol[50];

	FILE* file = fopen("postfix.txt", "r");
	fgets(symbol, sizeof(symbol), file);

	for (int i = 0; symbol[i] != '\0'; i++) {
		if (symbol[i] > 47 && symbol[i] < 58) {
			push(chToNum(symbol[i]), head);
		}
		else{
			switch (symbol[i])
			{
			case ' ':
				break;

			case '+':
				a = pop(head);
				b = pop(head);
				push(a + b, head);
				break;

			case '-':
				a = pop(head);
				b = pop(head);
				push(b - a, head);
				break;

			case '*':
				a = pop(head);
				b = pop(head);
				push(a * b, head);
				break;
			}
		}
	}
	fclose(file);
}

int main() {

	stog head = {NULL};

	calPostfix(&head);

	printf("%d", head.next->number);

	return 0;
}