// Выполнила: Нупрейчик Маргарита, гр. 2309
//

#include <iostream>
#include <locale>
#include <random>

struct BTNode {

	int key;
	BTNode* parent;
	BTNode* left_child;
	BTNode* right_child;
};

struct BTTree {
	BTNode* root;
};

// функции для binary search tree 

BTNode* findMin(BTNode* node) {
	BTNode* minimum = node;
	while (minimum->left_child != nullptr) minimum = minimum->left_child;
	return minimum;
}

BTNode* findMax(BTNode* node) {
	BTNode* maximum = node;
	while (maximum->left_child != nullptr) maximum = maximum->left_child;
	return maximum;
}

// вставка элемента (tested)
void insertBTNode(BTNode* insnode, BTTree* tree) {
	BTNode* root = tree->root;
	if (root == nullptr) {
		root = insnode;
		return;
	}
	BTNode* parent = root->parent;
	while (root != nullptr) {
		if (insnode->key < root->key) {
			if (root->left_child == nullptr) {
				insnode->parent = root;
				root->left_child = insnode;
				return;
			}
			root = root->left_child;
		}
		else if (insnode->key > root->key) {
			if (root->right_child == nullptr) {
				insnode->parent = root;
				root->right_child = insnode;
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

// поиск предыдущего (tested)
BTNode* findPredcessor(BTNode* node) {
	BTNode* predcessor = nullptr;
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
BTNode* findSuccessor(BTNode* node) {
	BTNode* successor = nullptr;
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
BTNode* searchByKey(int value, BTTree* tree) {
	BTNode* root = tree->root;
	if (root == nullptr) {
		std::cout << "Дерево пусто.\n";
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
BTNode* deleteBTNode(int nodekey, BTNode* root) {

	BTNode* temp = nullptr;

	// проверка на всевозможные исключения
	if (root == nullptr) {
		std::cout << "Корня дерева не существует.\n";
		return nullptr;
	} 
	else if (nodekey < root->key) {
		root->left_child = deleteBTNode(nodekey, root->left_child);
	}
	else if (nodekey > root->key) {
		root->right_child = deleteBTNode(nodekey, root->right_child);
	}
	else if (root->left_child != nullptr && root->right_child != nullptr) {
		temp = findMin(root->right_child);
		root->key = temp->key;
		root->right_child = deleteBTNode(root->key, root->right_child);
	}
	else {
		temp = root;
		if (root->left_child == nullptr) {
			root = root->right_child;
		}
		else if (root->right_child == nullptr) {
			root = root->left_child;
		}
		delete temp;
	}
	return root;
}

// левый поворот (tested)
void BTleftRotation(BTNode* node, BTTree* tree) {

	BTNode* x = node;

	if (x == nullptr || (x->parent == nullptr && x->left_child == nullptr && x->right_child == nullptr)) return;
	
	if (x->right_child == nullptr) return;

	BTNode* y = x->right_child;

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
void BTrightRotation(BTNode* node, BTTree* tree) {

	BTNode* x = node;
	if (x == nullptr || (x->parent == nullptr && x->left_child == nullptr && x->right_child == nullptr)) return;

	if (x->left_child == nullptr) return;

	BTNode* y = x->left_child;

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
void BTbigLeftRotation(BTNode* node, BTTree* tree) {
	BTrightRotation(node->left_child, tree);
	BTleftRotation(node, tree);
}

// большой правый поворот (tested)
void BTbigRightRotation(BTNode* node, BTTree* tree) {
	BTleftRotation(node->right_child, tree);
	BTrightRotation(node, tree);
}

void printBT(const std::string& prefix, BTNode* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "'--");

		// print the value of the node
		std::cout << node->key << std::endl;

		// enter the next tree level - left and right branch

		printBT(prefix + (isLeft ? "|   " : "   "), node->left_child, true);
		printBT(prefix + (isLeft ? "|   " : "   "), node->right_child, false);
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	srand(time(0));

	BTTree* BST = new BTTree(); BST->root = new BTNode(); BST->root->key = rand() % 100; // всегда хранит указатель на корневой элемент

	for (int i = 1; i < 10; i++) {
		// здесь производится вставка 10 элементов
		BTNode* toInsert = new BTNode(); toInsert->key = rand() % 100;
		insertBTNode(toInsert, BST);
	}
	printBT("", BST->root, false);
	int valueToFind = 0;
	while (true) {
		std::cin >> valueToFind;
		std::cout << "founded\n";
		BTNode* newRotated = searchByKey(valueToFind, BST);
		if (newRotated != nullptr) {
			BTbigLeftRotation(newRotated, BST);
			if (BST->root != nullptr) {
				printBT("", BST->root, false);
			}
			else break;
		}
	}
}
