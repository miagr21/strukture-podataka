#define _CRT_SECURE_NO_WARNINGS
#define OK 0
#define MALLOC_ERROR NULL
#define EMPTY_LIST -1
#define FILE_ERROR -2
#define NOT_FOUND -3
#define MAX_NAME_LEN 32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Napisati program koji iz datoteke „gradovi.txt" cita podatke o ID i nazivu pojedinog grada. Iz tih podataka se gradi vezana lista gradova. Nakon toga se iz datoteke 
„padaline.txt" cita ID grada, datum (u formatu d. m. godina.) i kolicina padalina na taj datum.
Od ovih podataka se gradi nova vezana lista koja sadrzi naziv grada (preko ID se skuplja iz prve liste), datum i kolicinu padalina.
Podatke sortirati po nazivu grada i datumu. Ispisati listu.
Unijeti neki datum i za taj datum pronaci u kojem gradu je bilo najvise padalina. Ispisati
Za svaki grad pronaci dan s najmanje padalina i prebaciti ga na pocetak liste. Ispisati novu listu.*/

typedef char string[MAX_NAME_LEN];

typedef struct date {
	int day; 
	int month;
	int year;
}date;

typedef struct padaline* pointp;
typedef struct padaline {
	string grad;
	date datum;
	float amount;
	pointp next;
}padaline;

typedef struct grad* pointg;
typedef struct grad {
	int id;
	string naziv;
	pointg next;
}grad;

pointg createG(int id, string naziv) {
	pointg new = malloc(sizeof(grad));
	if (new == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	new->id = id;
	strcpy(new->naziv, naziv);
	new->next = NULL;
	return new;
}
pointp createP(string grad, int day, int month, int year, float amount) {
	pointp new = malloc(sizeof(padaline));
	if (new == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	new->amount = amount;
	strcpy(new->grad, grad);
	new->datum.day = day;
	new->datum.month = month;
	new->datum.year = year;
	new->next = NULL;
	return new;
}

int addG(pointg head, int id, string naziv) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	pointg new = createG(id, naziv);
	new->next = head->next;
	head->next = new;
	return OK;
}
int addP(pointp head, string grad, int day, int month, int year, float amount) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	pointp new = createP(grad, day, month, year, amount);
	pointp n = head;

	if (n->next == NULL || (strcmp(n->next->grad, grad) > 0  ||(strcmp(n->next->grad, grad) == 0 && (n->next->datum.month > month || (n->next->datum.month == month && n->next->datum.day > day))))) {
		new->next = n->next;
		n->next = new;
		return OK;
	}
	else {
		while (n->next != NULL && (strcmp(n->next->grad, grad) < 0  ||(strcmp(n->next->grad, grad) == 0 && (n->next->datum.month < month || (n->next->datum.month == month && n->next->datum.day < day))))) {
			n = n->next;
		}
		new->next = n->next;
			n->next = new;
			return OK;
	} {
		new->next = n->next;
		n->next = new;
		free(n);
		return OK;
	}
}

int printG(pointg head) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	pointg t = head->next;
	while (t != NULL) {
		printf("%d %s\n", t->id, t->naziv);
		t = t->next;
	}
	printf("\n");
	free(t);
	return OK;
}
int printP(pointp head) {
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	pointp t = head->next;
	while (t != NULL) {
		printf("%s %d/%d/%d %.1f\n", t->grad, t->datum.day, t->datum.month, t->datum.year, t->amount);
		t = t->next;
	}
	printf("\n");
	free(t);
	return OK;
}

int findDate(pointp head, int day, int month, int year){
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	pointp t = head->next;
	while (t != NULL) {
		if (t->datum.day == day && t->datum.month == month && t->datum.year == year) {
			return OK;
		}
		t = t->next;
	}
	free(t);
	return NOT_FOUND;
}
float findMax(pointp head, int day, int month, int year){
	if (head == NULL) {
		printf("unsuccessfull");
		return EMPTY_LIST;
	}
	float max = 0.0;
	pointp t = head->next;
	while (t != NULL) {
		if (t->datum.day == day && t->datum.month == month && t->datum.year == year) {
			if (max < t->amount) {
				max = t->amount;
			}
		}
		t = t->next;
	}
	free(t);
	return max;
}

int main() {

	pointg headg = malloc(sizeof(grad));
	if (headg == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	headg->next = NULL;
	pointp headp = malloc(sizeof(padaline));
	if (headp == NULL) {
		printf("unsuccessfull");
		return MALLOC_ERROR;
	}
	headp->next = NULL;

	FILE* fileg = fopen("gradovi.txt", "r");
	if (fileg == NULL) {
		printf("unsuccessfull");
		return FILE_ERROR;
	}
	int id;
	string name;
	while (fscanf(fileg, "%d %s", &id, name) == 2) {
		addG(headg, id, name);
	}
	fclose(fileg);


	FILE* filep = fopen("padaline.txt", "r");
	if (filep == NULL) {
		printf("unsuccessfull");
		return FILE_ERROR;
	}
	int ID;
	int day, month, year;
	float amount;
	string grad;
	while (fscanf(filep, "%d %d/%d/%d %f", &ID,&day,&month,&year, &amount) == 5) {
		pointg t = headg->next;
		while (t != NULL && t->id != ID) {
			t = t->next;
		}
		if (t == NULL) {
			return NOT_FOUND;
		}
		strcpy(grad, t->naziv);
		addP(headp, grad, day, month, year, amount);
	}
	fclose(filep);
	printP(headp);

	printf("Unesi zeljeni datum u formatu dan/mjesec/godina\n");
	scanf("%d/%d/%d", &day, &month, &year);
	if (day < 0 || day>31) {
		printf("Invalid date!\n");
	}
	else if (month < 0 || month > 12) {
		printf("Invalid date!\n");
	}
	if (findDate(headp, day, month, year) == NOT_FOUND) {
		printf("Nemamo podatke za taj dan!\n");
	}
	pointp t = headp->next;
	while (t != NULL) {
		if (t->amount == findMax(headp, day, month, year)) {
			printf("Grad sa najvise padalina na datum %d/%d/%d je %s sa padalinama od %.1fmm\n", day, month, year, t->grad, t->amount);
		}
		t = t->next;
	}
	free(t);

	return OK;
}