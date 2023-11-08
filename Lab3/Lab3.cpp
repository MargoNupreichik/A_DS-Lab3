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


// функции для binary search tree
 
// вставка элемента (tested)
void insertBTNode(BTNode* insnode, BTNode* root) {
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
    else  {
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
BTNode* searchByKey(int value, BTNode* root) {
    if (root == nullptr) {
        std::cout << "Дерево пусто.\n";
        return nullptr;
    }
    BTNode* parent = root->parent;
    while (root != nullptr) {
        if (root->key > value) {
            root = root->left_child;
        }
        else if (root->key < value) {
            root = root->right_child;
        }
        else {
            return root;
        }
        parent = root;
    }
    return root;
}

// удаление ноды из дерева
void deleteBTNode(BTNode* node) {
    // проверка на всевозможные исключения
    if (node == nullptr) {
        std::cout << "Переданный элемент не существует.\n";
        return;
    }
    if (node->parent == nullptr && node->left_child == nullptr && node->right_child == nullptr) {
        std::cout << "Дерево очищено полностью.\n";
        delete node;
        return;
    }

    bool isLeft, isLeftChild;

    // разбиение на варианты - два дочерних узла, один, нет вовсе
    // листовой узел
    if (node->parent != nullptr && node->left_child == nullptr && node->right_child == nullptr) {
        isLeftChild = (node->parent->left_child != nullptr);
        
        if (isLeftChild) node->parent->left_child = nullptr;
        else node->parent->right_child = nullptr;
        
        delete node;

    }
    // имеет только 1 дочерний узел
    else if (node->left_child == nullptr || node->right_child == nullptr) {
        // нужно понять, удаляемый узел левый или правый
        if (node->parent != nullptr) {
            isLeft = (node->parent->left_child == node);
            isLeftChild = (node->left_child != nullptr);
            BTNode* nodeParent = node->parent;
            if (isLeft) {
                if (isLeftChild) { 
                    nodeParent->left_child = node->left_child; 
                    node->left_child->parent = nodeParent;
                }
                else {
                    nodeParent->left_child = node->right_child;
                    node->right_child->parent = nodeParent;
                }
                
            }
            else {
                if (isLeftChild) {
                    nodeParent->right_child = node->left_child;
                    node->left_child->parent = nodeParent;
                }
                else {
                    nodeParent->right_child = node->right_child;
                    node->right_child->parent = nodeParent;
                }
                
            }
        }
        else {
            isLeftChild = (node->left_child != nullptr);
            if (isLeftChild) node->left_child->parent = nullptr;
            else node->right_child = nullptr;
        }
        delete node;
    }
    // имеет 2 дочерних узла
    else {
        BTNode* toReplace = findSuccessor(node);
        int temp = toReplace->key;
        toReplace->key = node->key;
        node->key = temp;

        deleteBTNode(toReplace);
    }
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

    BTNode* bst = new BTNode(); bst->key = rand() % 100; // инициализация корневого элемента
    BTNode* cursor = bst; // всегда хранит указатель на корневой элемент

    for (int i = 1; i < 10; i++) {
        // здесь производится вставка 10 элементов
        BTNode* toInsert = new BTNode(); toInsert->key = rand() % 100;
        insertBTNode(toInsert, bst);
        bst = cursor;
    }
    printBT("", cursor, false);
    int valueToFind = 0;
    while (true) {
        std::cin >> valueToFind;
        BTNode* found = searchByKey(valueToFind, bst);
        bst = cursor;
        if (found != nullptr) {
            std::cout << "founded\n";
            deleteBTNode(found);
            printBT("", cursor, false);
        }
    }
}
