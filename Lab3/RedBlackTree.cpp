#include "RedBlackTree.h"

RBNode* findMin(RBNode* node) {
	RBNode* minimum = node;
	while (minimum->left_child != nullptr) minimum = minimum->left_child;
	return minimum;
}

RBNode* findMax(RBNode* node) {
	RBNode* maximum = node;
	while (maximum->right_child != nullptr) maximum = maximum->right_child;
	return maximum;
}

// вставка элемента (tested)
void insertRBNode(RBNode* insnode, RBTree* tree) {
	if (tree->root == nullptr) {
		tree->root = insnode;
		insnode->color = 0;
		return;
	}

	RBNode* root = tree->root;
	RBNode* parent = root->parent;
	insnode->color = 1;
	while (root != nullptr) {
		if (insnode->key < root->key) {
			if (root->left_child == nullptr) {
				insnode->parent = root;
				root->left_child = insnode;
				RBinsertionFix(insnode, tree);
				return;
			}
			root = root->left_child;
		}
		else if (insnode->key > root->key) {
			if (root->right_child == nullptr) {
				insnode->parent = root;
				root->right_child = insnode;
				RBinsertionFix(insnode, tree);
				return;
			}
			root = root->right_child;
		}
		else {
			std::cout << "Элемент с таким значением уже существует.\n";
			delete insnode;
			return;
		}
		parent = root;
	}
}

void RBinsertionFix(RBNode* insnode, RBTree* tree) {

	while (insnode->parent != nullptr && insnode->parent->parent != nullptr && insnode->parent->color == 1) {
		if (insnode->parent == insnode->parent->parent->left_child) {
			if (insnode->parent->parent->right_child != nullptr && insnode->parent->parent->right_child->color == 1) {
				insnode->parent->color = 0;
				insnode->parent->parent->right_child->color = 0;
				insnode->parent->parent->color = 1;
				insnode = insnode->parent->parent;
			}
			else {
				if (insnode == insnode->parent->right_child) {
					insnode = insnode->parent;
					RBleftRotation(insnode, tree);
				}
				insnode->parent->color = 0;
				insnode->parent->parent->color = 1;
				RBrightRotation(insnode->parent->parent, tree);
			}
		}
		else {
			if (insnode->parent->parent->left_child != nullptr && insnode->parent->parent->left_child->color == 1) {
				insnode->parent->color = 0;
				insnode->parent->parent->left_child->color = 0;
				insnode->parent->parent->color = 1;
				insnode = insnode->parent->parent;
			}
			else {
				if (insnode == insnode->parent->left_child) {
					insnode = insnode->parent;
					RBrightRotation(insnode, tree);
				}
				insnode->parent->color = 0;
				insnode->parent->parent->color = 1;
				RBleftRotation(insnode->parent->parent, tree);
			}
		}
	}
	tree->root->color = 0;
}

// поиск предыдущего (tested)
RBNode* findPredcessor(RBNode* node) {
	RBNode* predcessor = nullptr;
	// 1 случай - предшественник находится ниже
	if (node->left_child != nullptr) {
		predcessor = node->left_child;
		while (predcessor->right_child != nullptr) {
			predcessor = predcessor->right_child;
		}

	} // 2 случай - предшественника нужно искать 
	else {
		if (node->parent != nullptr) {
			predcessor = node->parent;
			if (node == predcessor->left_child) {
				if (predcessor->parent != nullptr) {
					if (predcessor == predcessor->parent->left_child) {
						while (predcessor->parent != nullptr && predcessor == predcessor->parent->left_child) predcessor = predcessor->parent;
						if (predcessor->parent != nullptr) predcessor = predcessor->parent;
						else predcessor = nullptr;
					}
					else if (predcessor == predcessor->parent->right_child) {
						predcessor = predcessor->parent;
					}
				}
				else {
					predcessor = nullptr;
				}
			}
			else {
				predcessor;
			}
		}
	}
	return predcessor;
}

// поиск следующего (tested)
RBNode* findSuccessor(RBNode* node) {
	RBNode* successor = nullptr;
	// 1 случай - потомок находится ниже
	// сюда же входит случай, если указанная нода - корневая -> не требуется дальнейшей проверки на наличие родителя на первом этапе
	if (node->right_child != nullptr) {
		successor = node->right_child;
		while (successor->left_child != nullptr) {
			successor = successor->left_child;
		}

	} // 2 случай - потомка нужно искать 
	else {
		if (node->parent != nullptr) {
			successor = node->parent;
			// 2 варианта для положения ноды: это правый ребенок родителя;
			if (node == successor->right_child) {
				if (successor->parent != nullptr) {
					// если сам родитель правый потомок
					if (successor == successor->parent->right_child) {
						while (successor->parent != nullptr && successor == successor->parent->right_child) successor = successor->parent;
						// проверяем не дошли ли до корня, если дошли - следующего нет
						if (successor->parent != nullptr) successor = successor->parent;
						else successor = nullptr;
					}
					// если сам родитель левый потомок
					else if (successor == successor->parent->left_child) {
						successor = successor->parent;
					}
				}
				else {
					successor = nullptr;
				}
			}
			// это левый ребенок родителя. 
			else {
				successor;
			}
		}
	}
	return successor;
}

// поиск по ключу (tested)
RBNode* searchByKey(int value, RBTree* tree) {
	RBNode* root = tree->root;
	if (root == nullptr) {
		return nullptr;
	}
	while (root != nullptr) {
		if (root->key > value) {
			root = root->left_child;
		}
		else if (root->key < value) {
			root = root->right_child;
		}
		else {
			return root;
		};
	}
	return root;
}

// удаление ноды из дерева
RBNode* deleteRBNode(int nodekey, RBNode* root) {

	RBNode* temp = nullptr;
	RBNode* parent;
	if (root == nullptr) {
		return nullptr;
	}
	else if (nodekey < root->key) {
		root->left_child = deleteRBNode(nodekey, root->left_child);
	}
	else if (nodekey > root->key) {
		root->right_child = deleteRBNode(nodekey, root->right_child);
	}
	// нашли ноду с указанным значением
	// у ноды нет дочерних узлов
	if (root->left_child == nullptr && root->right_child == nullptr) {
		if (root->parent != nullptr) {
			if (root->parent->left_child == root) root->parent->left_child = nullptr;
			else root->parent->right_child = nullptr;
			parent = root->parent;
			root->parent = nullptr;
			return parent;
		}
		else {
			// удаляется корень
			root = nullptr;
			return nullptr;
		}
	}
	// у этой ноды 2 дочерних узла
	else if (root->left_child != nullptr && root->right_child != nullptr) {
		temp = findMin(root->right_child);
		root->key = temp->key;
		root->right_child = deleteRBNode(root->key, root->right_child);
	}
	// у этой ноды 1 дочерний узел
	else if (root->left_child == nullptr && root->right_child == nullptr) {
		temp = root;
		if (root->left_child == nullptr) {
			root = root->right_child;
		}
		else if (root->right_child == nullptr) {
			root = root->left_child;
		}
		delete temp;
	}

	//балансировка нужна только если цвет удаляемой ноды - черный
	if (root->color == 0) RBfixDelete(root->parent);

	if (root == nullptr) return nullptr;
	return root;
}

// исправление последствий удаления ноды
void RBfixDelete(RBNode* delpar) {

}

// левый поворот (tested)
void RBleftRotation(RBNode* node, RBTree* tree) {

	RBNode* x = node;

	if (x == nullptr || (x->parent == nullptr && x->left_child == nullptr && x->right_child == nullptr)) return;

	if (x->right_child == nullptr) return;

	RBNode* y = x->right_child;

	x->right_child = y->left_child;

	if (y->left_child != nullptr) {
		y->left_child->parent = x;
	}
	y->parent = x->parent;

	if (x->parent == nullptr) tree->root = y;
	else if (x == x->parent->left_child) x->parent->left_child = y;
	else x->parent->right_child = y;

	y->left_child = x;
	x->parent = y;
}

// правый поворот (tested)
void RBrightRotation(RBNode* node, RBTree* tree) {

	RBNode* x = node;
	if (x == nullptr || (x->parent == nullptr && x->left_child == nullptr && x->right_child == nullptr)) return;

	if (x->left_child == nullptr) return;

	RBNode* y = x->left_child;

	x->left_child = y->right_child;

	if (y->right_child != nullptr) {
		y->right_child->parent = x;
	}
	y->parent = x->parent;

	if (x->parent == nullptr) tree->root = y;
	else if (x == x->parent->left_child) x->parent->left_child = y; // ?
	else x->parent->right_child = y;

	y->right_child = x;
	x->parent = y;
}

// большой левый поворот (tested)
void RBbigLeftRotation(RBNode* node, RBTree* tree) {
	RBrightRotation(node->left_child, tree);
	RBleftRotation(node, tree);
}

// большой правый поворот (tested)
void RBbigRightRotation(RBNode* node, RBTree* tree) {
	RBleftRotation(node->right_child, tree);
	RBrightRotation(node, tree);
}

// обходы по дереву:
int getLevel(int nodekey, RBNode* root) {
	int level = 0;

	while (root != nullptr) {
		if (root->key == nodekey) return level;

		if (root->key < nodekey) {
			root = root->right_child;
		}
		else root = root->left_child;

		level++;
	}
}


// в ширину
int RBheight(RBNode* node) {
	if (node == nullptr) return 0;
	else {
		int lefth = RBheight(node->left_child);
		int righth = RBheight(node->right_child);

		if (lefth > righth) return (lefth + 1);
		else return (righth + 1);
	}
}

void RBprintLevel(RBNode* root, int level) {
	if (root == nullptr) return;
	if (level == 1) std::cout << " " << root->key << " ";
	else if (level > 1) {
		RBprintLevel(root->left_child, level - 1);
		RBprintLevel(root->right_child, level - 1);
	}
}

void roundaboutWidth(RBNode* root) {
	int h = RBheight(root);

	int i;
	for (int i = 0; i <= h; i++) {
		RBprintLevel(root, i);
	}
}

// в глубину:
void depthPreorder(RBNode* root) {
	if (root != nullptr) {
		std::cout << " | " << root->key;
		depthPreorder(root->left_child);
		depthPreorder(root->right_child);
	}
}

void depthPostorder(RBNode* root) {
	if (root != nullptr) {
		depthPostorder(root->left_child);
		depthPostorder(root->right_child);
		std::cout << " | " << root->key;
	}
}

void depthInorder(RBNode* root) {
	if (root != nullptr) {
		depthInorder(root->left_child);
		std::cout << " | " << root->key;
		depthInorder(root->right_child);
	}
}

void printRB(const std::string& prefix, RBNode* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "'--");

		// print the value of the node
		std::cout << node->key << " " << (node->color == 0 ? "BLACK" : "RED") << std::endl;

		// enter the next tree level - left and right branch

		printRB(prefix + (isLeft ? "|   " : "   "), node->left_child, true);
		printRB(prefix + (isLeft ? "|   " : "   "), node->right_child, false);
	}
}
