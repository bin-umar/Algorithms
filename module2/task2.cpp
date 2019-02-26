#include <iostream>
#include <stack>

using namespace std;

/**
 * Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K
 * добавляется в правое поддерево root; иначе в левое поддерево root.
 * Выведите элементы в порядке in-order (слева направо).
 * Рекурсия запрещена.
 * Обход дерева в порядке in-order
 */

template <class T>
class Stack {
public:
    Stack(): buffer(8), elements(0) { array = new T[buffer]; };
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    ~Stack() { delete []array; };

    Stack& operator=(const Stack&) = delete;
    Stack& operator=(Stack&&) = delete;

    void push(T data) {
        if (++elements < buffer) reAlloc(buffer *= 2);
        array[elements - 1] = data;
    }

    T pop() {
        if(buffer >= 16 && elements == (buffer / 4)) reAlloc(buffer /= 2);
        return array[--elements];
    }

    bool empty() { return elements == 0; }
    int size() { return elements; }

private:
    int buffer;
    int elements;
    T* array;

    void reAlloc(int newBuffer) {
        auto* temp = new T[newBuffer];

        for (int i=0; i < elements; i++)
            temp[i] = array[i];

        delete []array;
        array = temp;
    }
};

template <class T>
struct Fruit {
    T data;
    Fruit* left;
    Fruit* right;

    explicit Fruit(T _data): data(_data), left(nullptr), right(nullptr) {};
//    ~Fruit() {
//        if (left != nullptr)
//            delete left;
//        if (right != nullptr)
//            delete right;
//    }
};

template <class T>
T isLess(T a, T b);

template <>
int isLess(int a, int b) {
    return a < b;
}


template <class T>
class BinaryTree {
public:
    BinaryTree(): root(nullptr) {};
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;

    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

    ~BinaryTree() {
//        delete root;
        DestroyTree();
    }

    void Add(T);
    Fruit<T>* root;

private:

    void DestroyTree() {
        Fruit<T>* save;
        for (Fruit<T>* it = root; it != nullptr; it = save) {

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

    void DestroyTreeRecursive(Fruit<T>* node) {

        if (node != nullptr) {
            DestroyTreeRecursive(node->left);
            DestroyTreeRecursive(node->right);
            delete node;
        }
    }
};

template <class T>
void BinaryTree<T>::Add(T data) {

    auto* newNode = new Fruit<T>(data);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Fruit<T>* next = root;

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

template <class TPtr, class Fprint>
void InOrderPrint(TPtr _root, Fprint print){

    Stack<TPtr> stack;

    while (_root != nullptr || !stack.empty()){

        if (!stack.empty()){

            _root = stack.pop();
//            stack.pop();
            print(_root->data);

            if (_root->right != nullptr) _root = _root->right;
            else _root = nullptr;
        }

        while (_root != nullptr){
            stack.push(_root);
            _root = _root->left;
        }
    }
}


template <class T>
void print(T data) {
    cout << data << " ";
}

void Test() {
    BinaryTree<int> tree;

    tree.Add(7);
    tree.Add(5);
    tree.Add(2);
    tree.Add(10);
    tree.Add(8);
    tree.Add(9);
    tree.Add(3);
    tree.Add(6);
    tree.Add(4);
    tree.Add(1);

    InOrderPrint(tree.root, print<int>);
}


int main() {

//    Test();
    int n;
    cin >> n;

    BinaryTree<int> tree;

    int element;

    for (int i=0;  i < n; i++) {
        cin >> element;
        tree.Add(element);
    }

    InOrderPrint(tree.root, print<int>);

    return 0;
}