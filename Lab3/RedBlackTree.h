#pragma once

#include <iostream>

struct RBNode {

	int key;
	RBNode* parent;
	RBNode* left_child;
	RBNode* right_child;
	bool color; // 0 - черный, 1 - красный
};

struct RBTree {
	RBNode* root;
	RBTree() {
		root = nullptr;
	}
};

RBNode* findMin(RBNode* node);
RBNode* findMax(RBNode* node);
void insertRBNode(RBNode* insnode, RBTree* tree);
RBNode* findPredcessor(RBNode* node);
RBNode* findSuccessor(RBNode* node);
RBNode* searchByKey(int value, RBTree* tree);
RBNode* deleteBTNode(int nodekey, RBNode* root);
void RBleftRotation(RBNode* node, RBTree* tree);
void RBrightRotation(RBNode* node, RBTree* tree);
void RBbigLeftRotation(RBNode* node, RBTree* tree);
void RBbigRightRotation(RBNode* node, RBTree* tree);
int getLevel(int nodekey, RBNode* root);
int RBheight(RBNode* node);
void RBprintLevel(RBNode* root, int level);
void roundaboutWidth(RBNode* root);
void depthPreorder(RBNode* root);
void depthPostorder(RBNode* root);
void depthInorder(RBNode* root);
void printRB(const std::string& prefix, RBNode* node, bool isLeft);

void RBinsertionFix(RBNode* insnode, RBTree* tree);
void RBfixDelete(RBNode* delpar);