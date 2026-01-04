#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* point;
typedef struct node {
	int data;
	point left;
	point right;
}node;

point createNode(int data) {
	point newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}


point insert(point root, int data) {
	if (root == NULL) {
		root = createNode(data);
	}
	else if (data >= root->data) {
		root->left = insert(root->left, data);
	}
	else if (data < root->data) {
		root->right = insert(root->right, data);
	}
	return root;
}
int replace(point root) {
	if (root == NULL) return 0;
	int leftSum = replace(root->left);
	int rightSum = replace(root->right);
	int oldValue = root->data;
	root->data = leftSum + rightSum;
	return oldValue + root->data;
}

int printInorder(point root, FILE* file) {
	if (root == NULL) return 0;
	printInorder(root->left, file);
	fprintf(file, "%d ", root->data);
	printInorder(root->right, file);
	return 0;
}

int main() {

	FILE* file = fopen("tree.txt", "w");
	point root = NULL;

	int array[10];

	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		array[i] = rand() % 81 + 10;
	}

	for (int i = 0; i < 10; i++) {
		root = insert(root, array[i]);
	}

	fprintf(file, "Before replace:\n");
	printInorder(root, file);

	replace(root);

	fprintf(file, "\nAfter replace:\n");
	printInorder(root, file);
	return 0;
}