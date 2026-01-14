#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
#define HASH_SIZE 11

typedef struct grad* GradPoz;
typedef struct grad {
    char naziv[MAX];
    int stanovnika;
    GradPoz left;
    GradPoz right;
} Grad;


typedef struct drzava* DrzavaPoz;
typedef struct drzava {
    char naziv[MAX];
    GradPoz root;
    DrzavaPoz next;
} Drzava;

int hashFunkcija(char* naziv) {
    int sum = 0;
    for (int i = 0; i < 5 && naziv[i] != '\0'; i++)
        sum += (int)naziv[i];

    return sum % HASH_SIZE;
}

GradPoz createGrad(char* naziv, int br) {
    GradPoz g = malloc(sizeof(Grad));
    strcpy(g->naziv, naziv);
    g->stanovnika = br;
    g->left = g->right = NULL;
    return g;
}

GradPoz insertGrad(GradPoz root, char* naziv, int br) {
    if (!root)
        return createGrad(naziv, br);

    if (br < root->stanovnika ||
        (br == root->stanovnika && strcmp(naziv, root->naziv) < 0))
        root->left = insertGrad(root->left, naziv, br);
    else
        root->right = insertGrad(root->right, naziv, br);

    return root;
}

void printGradovi(GradPoz root) {
    if (!root) return;
    printGradovi(root->left);
    printf("        %s (%d)\n", root->naziv, root->stanovnika);
    printGradovi(root->right);
}

DrzavaPoz createDrzava(char* naziv) {
    DrzavaPoz d = malloc(sizeof(Drzava));
    strcpy(d->naziv, naziv);
    d->root = NULL;
    d->next = NULL;
    return d;
}

void insertDrzavaSorted(DrzavaPoz head, DrzavaPoz nova) {
    while (head->next && strcmp(head->next->naziv, nova->naziv) < 0)
        head = head->next;

    nova->next = head->next;
    head->next = nova;
}

void loadGradovi(DrzavaPoz drzava, char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return;

    char naziv[MAX];
    int br;

    while (fscanf(f, "%s %d", naziv, &br) == 2)
        drzava->root = insertGrad(drzava->root, naziv, br);

    fclose(f);
}

void searchGradovi(GradPoz root, int min) {
    if (!root) return;

    searchGradovi(root->left, min);
    if (root->stanovnika > min)
        printf("        %s (%d)\n", root->naziv, root->stanovnika);
    searchGradovi(root->right, min);
}

void printHash(DrzavaPoz hash[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("\nHash[%d]:\n", i);
        DrzavaPoz temp = hash[i]->next;
        while (temp) {
            printf("    %s:\n", temp->naziv);
            printGradovi(temp->root);
            temp = temp->next;
        }
    }
}

int main() {
    DrzavaPoz hash[HASH_SIZE];

    for (int i = 0; i < HASH_SIZE; i++) {
        hash[i] = malloc(sizeof(Drzava));
        hash[i]->next = NULL;
    }

    FILE* f = fopen("drzave.txt", "r");
    if (!f) {
        printf("Greska pri otvaranju drzave.txt\n");
        return 1;
    }

    char naziv[MAX], dat[MAX];

    while (fscanf(f, "%s %s", naziv, dat) == 2) {
        int index = hashFunkcija(naziv);

        DrzavaPoz d = createDrzava(naziv);
        loadGradovi(d, dat);
        insertDrzavaSorted(hash[index], d);
    }
    fclose(f);

    printHash(hash);

    char trazena[MAX];
    int min;

    printf("\nUnesi drzavu: ");
    scanf("%s", trazena);
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &min);

    int idx = hashFunkcija(trazena);
    DrzavaPoz temp = hash[idx]->next;

    while (temp && strcmp(temp->naziv, trazena) != 0)
        temp = temp->next;

    if (temp) {
        printf("Gradovi s vise od %d stanovnika:\n", min);
        searchGradovi(temp->root, min);
    }
    else {
        printf("Drzava nije pronadena.\n");
    }

    return 0;

}