#include <iostream>
#include <queue>

using namespace std;

/**
 * Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
 * Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
 * При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
 * Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во
 * втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
 * Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
 * Равные ключи добавляйте в правое поддерево. Вычислить количество узлов в самом широком слое
 * декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу.
 * Разница может быть отрицательна.
 * 3_2. Декартово дерево. Разница ширин
 */

/// Common

template <class T>
T isLess(T a, T b);

template <>
int isLess(int a, int b) {
    return a < b;
}

template <class TPtr>
void destroyTree(TPtr root) {

    TPtr save;
    for (TPtr it = root; it != nullptr; it = save) {

        if (it->left == nullptr) {

            save = it->right;
            delete it;

        } else {
            save = it->left;
            it->left = save->right;
            save->right = it;
        }
    }
}

template <class TPtr>
int getWidestNodes(TPtr root) {

    int maxWidth = 0;
    queue<TPtr> layer;
    layer.push(root);

    while (!layer.empty()) {

        int currentWidth = (int)layer.size();

        if (currentWidth > maxWidth)
            maxWidth = currentWidth;

        for (int i = 0; i < currentWidth; ++i) {

            TPtr temp = layer.front();
            layer.pop();
            if (temp->left)
                layer.push(temp->left);
            if (temp->right)
                layer.push(temp->right);

        }
    }

    return maxWidth;
}

/// Binary Tree with its node

template <class T>
struct BinaryNode {
    T data;
    BinaryNode* left;
    BinaryNode* right;

    explicit BinaryNode(T _data): data(_data), left(nullptr), right(nullptr) {};
};

template <class T>
class BinaryTree {
public:
    BinaryTree(): root(nullptr) {};

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;

    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

    ~BinaryTree() {
        destroyTree<BinaryNode<T>*>(root);
    }

    void Add(T);
    int GetWidestNodes() {
        return getWidestNodes<BinaryNode<T>*>(root);
    };

private:
    BinaryNode<T>* root;
};

template <class T>
void BinaryTree<T>::Add(T data) {

    auto* newNode = new BinaryNode<T>(data);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    BinaryNode<T>* next = root;

    while (true) {

        if (isLess(newNode->data, next->data)) {

            if (next->left != nullptr)
                next = next->left;
            else {
                next->left = newNode;
                return;
            }

        } else {

            if (next->right != nullptr)
                next = next->right;
            else {
                next->right = newNode;
                return;
            }
        }
    }
}

/// Treap with its node

template <class T, class P>
struct TreapNode {
    T key;
    P priority;
    TreapNode* left = nullptr;
    TreapNode* right = nullptr;

    explicit TreapNode(T k, P p): key(k), priority(p) {};
};


template <class T, class P>
class Treap {
public:
    Treap(): root(nullptr) {};

    Treap(const Treap&) = delete;
    Treap(Treap&&) = delete;

    Treap& operator=(const Treap&) = delete;
    Treap& operator=(Treap&&) = delete;

    ~Treap() {
        destroyTree<TreapNodePtr>(root);
    };

    typedef TreapNode<T,P>* TreapNodePtr;

    void Add(T key, P priority);
    void Split(TreapNodePtr currNode, T key, TreapNodePtr& left, TreapNodePtr& right);
    TreapNodePtr Merge(TreapNodePtr left, TreapNodePtr right);

    int GetWidestNodes() {
        return getWidestNodes<TreapNodePtr>(root);
    };

private:
    TreapNodePtr root;
};

template <class T, class P>
void Treap<T,P>::Add(T key, P priority){

    auto* newNode = new TreapNode<T,P>(key, priority);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    TreapNodePtr current = root;
    TreapNodePtr prev = root;

    while (current && current->priority >= priority) {

        prev = current;
        if (isLess(key, current->key))
            current = current->left;
        else
            current = current->right;
    }

    Split(current, key, newNode->left, newNode->right);

    if (current == root)
        root = newNode;
    else {
        if (isLess(key, prev->key))
            prev->left = newNode;
        else
            prev->right = newNode;
    }

}

template <class T, class P>
void Treap<T,P>::Split(TreapNodePtr currNode, T key, TreapNodePtr& left, TreapNodePtr& right) {

    if( currNode == nullptr ) {
        left = nullptr;
        right = nullptr;
    } else if( isLess(currNode->key, key) ) {
        Split( currNode->right, key, currNode->right, right );
        left = currNode;
    } else {
        Split( currNode->left, key, left, currNode->left );
        right = currNode;
    }

}

template <class T, class P>
TreapNode<T,P>* Treap<T,P>::Merge(TreapNodePtr left, TreapNodePtr right) {

    if ( left == nullptr || right == nullptr )
        return left == nullptr ? right : left;

    if ( left->priority > right->priority ) {
        left->right = Merge( left->right, right );
        return left;
    } else {
        right->left = Merge( left, right->left );
        return right;
    }

}


void Test() {
    BinaryTree<int> tree;
    Treap<int, int> treap;

//    int keys[] {5, 18, 25, 50, 30, 15, 20, 22, 40, 45};
    int keys[] {38, 37, 47, 35, 12, 0, 31, 21, 30, 41};
//    int priorities[] {11, 8, 7, 12, 30, 15, 10, 5, 20, 9};
    int priorities[] {19, 5, 15, 0, 3, 42, 37, 45, 26, 6};

    for (int i=0; i < 10; i++) {
        tree.Add(keys[i]);
        treap.Add(keys[i], priorities[i]);
    }

    cout << treap.GetWidestNodes() << " " <<  tree.GetWidestNodes() << endl;
}

int main() {

    Test();

//    int n;
//    cin >> n;
//
//    BinaryTree<int> tree;
//    Treap<int, int> treap;
//
//    int key;
//    int priority;
//
//    for (int i=0;  i < n; i++) {
//        cin >> key >> priority;
//        tree.Add(key);
//        treap.Add(key, priority);
//    }
//
//    cout << treap.GetWidestNodes() - tree.GetWidestNodes() << endl;

    return 0;
}