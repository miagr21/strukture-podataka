#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char ime[20];
	char prezime[20];
	int bod;
}Student;

int brRed() {

	FILE* file = fopen("popis.txt", "r");
	if (file == NULL) {
		printf("Datoteka nije pronadena\n");
		return 0;
	}
	
	int br = 0;
	char string[1024] = { "" };

	while (fgets(string, sizeof(string), file) != NULL) {
		br++;
	}

	fclose(file);
	return br;
}

float relBod(float brBod) {

	float relBr = brBod / 50 * 100;
	return relBr;
}

int readF(Student * studenti){

	FILE* file = fopen("popis.txt", "r");
	if (file == NULL) {
		printf("Datoteka nije pronadena\n");
		return 0;
	}
	for (int i = 0; i < brRed(); i++) {
			fscanf(file, "%s %s %d", &studenti[i].ime, &studenti[i].prezime, &studenti[i].bod);
	}
	fclose(file);
	return 1;
}

int printS(Student* studenti) {

	readF(studenti);
	printf("Ime i prezime:\t Broj bodova: \n");
	for (int i = 0; i < brRed(); i++) {
		printf(" %s %s \t %d, %.0f%%\n", studenti[i].ime, studenti[i].prezime, studenti[i].bod, (float)relBod(studenti[i].bod));
	}
	return 1;
}

int main(){

	Student* studenti = malloc(brRed() * sizeof(Student));

	printS(studenti);

	free(studenti);

	return 0;
}