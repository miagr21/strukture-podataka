#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* point;
typedef struct node {
    int coeff;
    int exp;
    point next;
} node;

point newNode(int coeff, int exp);

int insertSorted(point* head, int coeff, int exp);

point readPolynomial(FILE* f);

point addPolynomials(point p1, point p2);

point multiplyPolynomials(point p1, point p2);

int printPolynomial(point p);

int freePolynomial(point p);

int main() {
    FILE* f = fopen("polynomials.txt", "r");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Reading polynomials from file...\n");

    point poly1 = readPolynomial(f);
    point poly2 = readPolynomial(f);
    fclose(f);

    printf("\nPolynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);

    point sum = addPolynomials(poly1, poly2);
    point product = multiplyPolynomials(poly1, poly2);

    printf("\nSum: ");
    printPolynomial(sum);
    printf("Product: ");
    printPolynomial(product);

    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sum);
    freePolynomial(product);

    return 0;
}

// create new node
point newNode(int coeff, int exp) {
    point n = malloc(sizeof(node));
    n->coeff = coeff;
    n->exp = exp;
    n->next = NULL;
    return n;
}

// insert term in sorted order (descending by exponent)
int insertSorted(point* head, int coeff, int exp) {
    if (coeff == 0) return;
    point new = newNode(coeff, exp);

    if (*head == NULL || (*head)->exp < exp) {
        new->next = *head;
        *head = new;
        return;
    }

    point temp = *head;
    while (temp->next && temp->next->exp > exp)
        temp = temp->next;

    if (temp->exp == exp) {
        temp->coeff += coeff;
        free(new);
        if (temp->coeff == 0) { // remove term if coeff = 0
            point cur = *head, prev = NULL;
            while (cur && cur->exp != exp) {
                prev = cur;
                cur = cur->next;
            }
            if (cur) {
                if (prev) prev->next = cur->next;
                else *head = cur->next;
                free(cur);
            }
        }
        return;
    }

    new->next = temp->next;
    temp->next = new;
    return 1;
}

// read one polynomial from file (stops at blank line or EOF)
point readPolynomial(FILE* f) {
    point head = NULL;
    int coeff, exp;
    char line[100];

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\n' || line[0] == '\r') break;
        if (sscanf(line, "%d %d", &coeff, &exp) == 2)
            insertSorted(&head, coeff, exp);
    }

    return head;
}

// add two polynomials
point addPolynomials(point p1, point p2) {
    point result = NULL;
    while (p1) {
        insertSorted(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    while (p2) {
        insertSorted(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }
    return result;
}

// multiply two polynomials
point multiplyPolynomials(point p1, point p2) {
    point result = NULL;
    for (point i = p1; i; i = i->next)
        for (point j = p2; j; j = j->next)
            insertSorted(&result, i->coeff * j->coeff, i->exp + j->exp);
    return result;
}

// print polynomial
int printPolynomial(point p) {
    if (!p) {
        printf("0\n");
        return;
    }
    while (p) {
        printf("%dx^%d", p->coeff, p->exp);
        if (p->next && p->next->coeff >= 0) printf(" + ");
        else if (p->next) printf(" ");
        p = p->next;
    }
    printf("\n");
    return 1;
}

// free list
int freePolynomial(point p) {
    while (p) {
        point temp = p;
        p = p->next;
        free(temp);
    }
    return 1;
}