#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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
	else if (data < root->data) {
		root->left = insert(root->left, data);
	}
	else if (data > root->data) {
		root->right = insert(root->right, data);
	}
	return root;
}

point search(point root, int data) {
	if (root == NULL) {
		printf("\tERROR!\nNUMBER NOT FOUND IN TREE!\n");
		return root;
	}

	if (data == root->data) {
		printf("Number %d found.\n", data);
		return root;
	}
	
	if (data < root->data) {
		return search(root->left, data);
	}
	else if (data > root->data) {
		return search(root->right, data);
	}
}

int printPreorder(point root) {
	if (root == NULL) return 0;
		printf("%d\n", root->data);
		printPreorder(root->left);
		printPreorder(root->right);
		return 0;
}
int printInorder(point root) {
	if(root == NULL) return 0;
		printInorder(root->left);
		printf("%d\n", root->data);
		printInorder(root->right);
		return 0;
}
int printPostorder(point root) {
	if (root == NULL) return 0;
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d\n", root->data);
		return 0;
}
point findMin(point root) {
	while (root->left != NULL)
		root = root->left;
	return root;
}

point deleteNode(point root, int data) {
	if (root == NULL)
		return NULL;

	if (data < root->data) {
		root->left = deleteNode(root->left, data);
	}
	else if (data > root->data) {
		root->right = deleteNode(root->right, data);
	}
	else {

		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}

		if (root->left == NULL) {
			point temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			point temp = root->left;
			free(root);
			return temp;
		}

		point temp = findMin(root->right);
		root->data = temp->data;
		root->right = deleteNode(root->right, temp->data);
	}

	return root;
}

int main() {
	
	point root = createNode(7); 
	insert(root, 4); 
	insert(root, 11); 
	insert(root, 8); 
	insert(root, 3); 
	insert(root, 13); 
	insert(root, 6); 
	insert(root, 1); 
	insert(root, 14);

	printPostorder(root);
	search(root, 67);
	deleteNode(root, 13);
	printPostorder(root);

	return 0;
}