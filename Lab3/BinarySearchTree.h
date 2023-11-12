#pragma once

#include <iostream>

struct BTNode {

	int key;
	BTNode* parent;
	BTNode* left_child;
	BTNode* right_child;
};

struct BTTree {
	BTNode* root;
	BTTree() { root = nullptr; }
};

BTNode* findMin(BTNode* node);
BTNode* findMax(BTNode* node);
void insertBTNode(BTNode* insnode, BTTree* tree);
BTNode* findPredcessor(BTNode* node);
BTNode* findSuccessor(BTNode* node);
BTNode* searchByKey(int value, BTTree* tree);
BTNode* deleteBTNode(int nodekey, BTNode* root);
void BTleftRotation(BTNode* node, BTTree* tree);
void BTrightRotation(BTNode* node, BTTree* tree);
void BTbigLeftRotation(BTNode* node, BTTree* tree);
void BTbigRightRotation(BTNode* node, BTTree* tree);
int getLevel(int nodekey, BTNode* root);
int BTheight(BTNode* node);
void BTprintLevel(BTNode* root, int level);
void roundaboutWidth(BTNode* root);
void depthPreorder(BTNode* root);
void depthPostorder(BTNode* root);
void depthInorder(BTNode* root);
void printBT(const std::string& prefix, BTNode* node, bool isLeft);