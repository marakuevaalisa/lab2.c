#include "Bintree.h"

#define MARKER -1
node_t* tree_create(int key) {

	node_t* node;
	node = (node_t*)malloc(sizeof(node_t));

	if (node == NULL) {
		return NULL;
	}

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
};


node_t* tree_search(node_t* root, int key) {

	if (root == NULL) {
		return NULL;
	}


	if (root->key == key) {
		return root;
	}
	if (key < root->key) {
		return tree_search(root->left, key);
	}
	else {
		return tree_search(root->right, key);
	}
};


node_t* tree_add(node_t* root, int key) {


	if (root == NULL) {
		return NULL;
	}

	if (key < root->key) {	
	
		if (root->left == NULL) {
			return root->left = tree_create(key);
		}

		else {
			return tree_add(root->left, key);
		}
	}
	else {

		if (root->right == NULL) {
			return root->right = tree_create(key);
		}

		else {
			return tree_add(root->right, key);
		}
	}

	return NULL;
};

void serialize(node_t* root, FILE* fp) {
	if (fp == NULL) {
		printf("Could not open file");
		return;
	}

	if (root == NULL) {
		fprintf(fp,"%d ", MARKER);
		return;
	}

	fprintf(fp, "%d ", root->key);
	serialize(root->left, fp);
	serialize(root->right, fp);
};

node_t* deserialize(node_t* root, FILE* fp) {
	
	int key;
	if (!fscanf(fp, "%d ", &key) || key == MARKER) {
		return NULL;
	}

	root = tree_create(key);
	root->left = deserialize(root->left, fp);
	root->right = deserialize(root->right, fp);

	return root;
};
