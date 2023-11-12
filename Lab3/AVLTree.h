#pragma once

struct AVLNode {

	int key;
	AVLNode* parent;
	AVLNode* left_child;
	AVLNode* right_child;
	short height; // возможные значения: -2 -1 0 1 2
};

struct AVLTree {
	AVLNode* root;
	AVLTree() {
		root = nullptr;
	}
};