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
void insertBTNode(BTNode* insnode, BTNode* root) {
    if (root == nullptr) {
        root = insnode;
        return;
    }
    BTNode* parent = root->parent;
    while (root != nullptr) {
        if (root->key > insnode->key) {
            if (root->left_child == nullptr) {
                insnode->parent = root;
                root->left_child = insnode;
                return;
            }
            root = root->left_child;
        }
        else if (root->key < insnode->key) {
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

// поиск предыдущего
BTNode* findPredcessor(BTNode* node) {
    return nullptr;
}

// поиск следующего
BTNode* findSuccessor(BTNode* node) {
    BTNode* successor = nullptr;
    // 1 случай - потомок находится ниже
    // сюда же входит случай, если указанная нода - корневая -> не требуется дальнейшей проверки на наличие родителя на первом этапе
    if (node->right_child != nullptr) {
        node = node->right_child;
        while (node->left_child != nullptr) {
            node = node->left_child;
        }
        successor = node;
    } // 2 случай - потомка нужно искать 
    else  {
        if (node == node->parent->left_child) successor = node->parent;
        else { // элемент является правым ребенком своего родителя
            node = node->parent;
            // два варианта - либо родитель родителя правый, либо левый. если левый, идем до упора, и крайний будет нашим элементом
            // если правый, смотрим, но является ли он правым до самого конца. если да - последователя нет
            if (node->parent != nullptr) {
                if (node == node->parent->left_child) {
                    while (node->parent != nullptr && node == node->parent->left_child) node = node->parent;
                    successor = node;
                }
                else {
                    while (node->parent != nullptr && node == node->parent->right_child) node = node->parent;
                    // два варианта: либо родительский элемент текущей ноды пустой, либо это левый элемент.
                    if (node->parent != nullptr && node->parent->left_child == node) successor = node->parent;
                }
            } // обработка случая, когда родитель у родителя не пустой не требуется - элемент самый правый, последователя нет
        }
    }
    return successor;
}

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

void deleteBTNode(BTNode* node, BTNode* root) {
    // проверка на всевозможные исключения
    if (root == nullptr) {
        std::cout << "Корня дерева не существует.\n";
        return;
    }
    if (node == nullptr) {
        std::cout << "Переданный элемент не существует.\n";
        return;
    }
    if (node == root) {
        std::cout << "Дерево очищено полностью.\n";
        return;
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
    std::cin >> valueToFind;
    BTNode* found = searchByKey(valueToFind, bst);
    bst = cursor;
    if (found!= nullptr) {
        std::cout << "founded\n";
        BTNode* successor = findSuccessor(found);
        if (successor != nullptr) std::cout << successor->key << std::endl;
        else std::cout << "not found\n";
    }
}
