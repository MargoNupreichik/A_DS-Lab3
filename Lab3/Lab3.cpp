// Выполнила: Нупрейчик Маргарита, гр. 2309
//

#include <locale>
#include <random>

#include "BinarySearchTree.h"
#include "RedBlackTree.h"

int main()
{
	setlocale(LC_ALL, "rus");

	srand(time(0));

	/*RBTree* BST = new RBTree(); // всегда хранит указатель на корневой элемент

	RBNode toInsert[] = {
	{4, nullptr, nullptr, nullptr, 0},
	{3, nullptr, nullptr, nullptr, 0},
	{8, nullptr, nullptr, nullptr, 0},
	{2, nullptr, nullptr, nullptr, 0},
	{1, nullptr, nullptr, nullptr, 0},
	{5, nullptr, nullptr, nullptr, 0},
	{9, nullptr, nullptr, nullptr, 0},
	{7, nullptr, nullptr, nullptr, 0},
	{15, nullptr, nullptr, nullptr, 0},
	{12, nullptr, nullptr, nullptr, 0},
	{23, nullptr, nullptr, nullptr, 0},
	{25, nullptr, nullptr, nullptr, 0}
	};
	for (int i = 0; i < 12; i++) {
		insertRBNode(&toInsert[i], BST);
	}

	printRB("", BST->root, false);
	int i = 0; std::cin >> i;
	RBNode* newNode = new RBNode(); newNode->key = i;
	insertRBNode(newNode, BST);
	printRB("", BST->root, false);

	*/
	BTTree* BST = new BTTree();

	BTNode toInsert[] = {
	{4, nullptr, nullptr, nullptr},
	{3, nullptr, nullptr, nullptr},
	{8, nullptr, nullptr, nullptr},
	{2, nullptr, nullptr, nullptr},
	{1, nullptr, nullptr, nullptr},
	{5, nullptr, nullptr, nullptr},
	{9, nullptr, nullptr, nullptr},
	{7, nullptr, nullptr, nullptr},
	{15, nullptr, nullptr, nullptr},
	{12, nullptr, nullptr, nullptr},
	{23, nullptr, nullptr, nullptr},
	{25, nullptr, nullptr, nullptr}
	};
	for (int i = 0; i < 12; i++) {
		insertBTNode(&toInsert[i], BST);
	}

	printBT("", BST->root, false);
	int i = 0; std::cin >> i;
	BTNode* newNode = new BTNode(); newNode->key = i;
	insertBTNode(newNode, BST);
	printBT("", BST->root, false);
}
