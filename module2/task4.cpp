#include <iostream>
#include <stack>

using namespace std;

/**
 * Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел,
 * а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным
 * числом A, команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой
 * статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).
 * 4_2. Порядковые статистики
 */

template <class T>
T isLess(T a, T b);

template <>
int isLess(int a, int b) {
    return a < b;
}

template <class T>
struct AVLNode {
    T data;
    size_t height;
    size_t size;
    AVLNode* left;
    AVLNode* right;

    explicit AVLNode(T _data):
            data(_data), left(nullptr), right(nullptr), height(1), size(1) {}
};

template <class T>
class AVLTree {
public:
    AVLTree(): root(nullptr) {}
    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;

    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree& operator=(AVLTree&&) = delete;

    ~AVLTree() { DestroyTree(); }

    void Add(T data);
    void Delete(T data);
    T FindKthStatistic(int k);

    typedef AVLNode<T>* AVLNodePtr;

private:
    AVLNodePtr root;
    struct Path {
        AVLNodePtr node;
        char c;
    };

    size_t GetHeight(AVLNodePtr node);
    size_t GetSize(AVLNodePtr node);
    int BalanceFactor(AVLNodePtr node);
    void FixHeight(AVLNodePtr node);
    void FixSize(AVLNodePtr node);

    AVLNodePtr RotateRight(AVLNodePtr node);
    AVLNodePtr RotateLeft(AVLNodePtr node);
    AVLNodePtr Balance(AVLNodePtr node);
    void BalanceParents(stack<Path>& stack);

    AVLNodePtr FindMin(AVLNodePtr node);
    AVLNodePtr DeleteMin(AVLNodePtr node);
    void DestroyTree();
};

template <class T>
size_t AVLTree<T>::GetHeight(AVLNodePtr node) {
    return node != nullptr ? node->height : 0;
}

template <class T>
size_t AVLTree<T>::GetSize(AVLTree<T>::AVLNodePtr node){
    return node != nullptr ? node->size : 0;
}

template <class T>
int AVLTree<T>::BalanceFactor(AVLNodePtr node) {
    return (int)(GetHeight(node->right) - GetHeight(node->left));
}

template <class T>
void AVLTree<T>::FixHeight(AVLNodePtr node) {

    size_t hLeft = GetHeight(node->left);
    size_t hRight = GetHeight(node->right);

    node->height = (hLeft > hRight ? hLeft: hRight) + 1;
}

template <class T>
void AVLTree<T>::FixSize(AVLTree<T>::AVLNodePtr node){

    size_t sLeft = GetSize(node->left);
    size_t sRight = GetSize(node->right);

    node->size = sLeft + sRight + 1;
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateLeft(AVLNodePtr node) {

    AVLNodePtr rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;

    FixHeight(node);
    FixHeight(rightNode);
    FixSize(node);
    FixSize(rightNode);

    return rightNode;
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateRight(AVLNodePtr node) {

    AVLNodePtr leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;

    FixHeight(node);
    FixHeight(leftNode);
    FixSize(node);
    FixSize(leftNode);

    return leftNode;
}

template <class T>
AVLNode<T>* AVLTree<T>::Balance(AVLNodePtr node) {

    FixHeight(node);
    FixSize(node);

    if( BalanceFactor(node) == 2 ) {

        if( BalanceFactor(node->right) < 0 )
            node->right = RotateRight(node->right);

        return RotateLeft(node);
    }

    if( BalanceFactor(node) == -2 ) {

        if( BalanceFactor(node->left) > 0  )
            node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    return node;
}

template <class T>
void AVLTree<T>::BalanceParents(stack<Path>& stack) {
    while (!stack.empty()) {
        AVLNodePtr currentNode = stack.top().node;
        stack.pop();

        if (!stack.empty()) {

            Path parent = stack.top();
            if (parent.c == 'l')
                parent.node->left = Balance(currentNode);
            else
                parent.node->right = Balance(currentNode);

        } else {
            root = Balance(currentNode);
        }
    }
}

template <class T>
void AVLTree<T>::Add(T data) {

    auto* newNode = new AVLNode<T>(data);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    AVLNodePtr next = root;
    stack<Path> stack;

    while (true) {
        if (isLess(newNode->data, next->data)) {
            stack.push({next, 'l'});

            if (next->left != nullptr)
                next = next->left;
            else {
                next->left = newNode;
                break;
            }
        } else {
            stack.push({next, 'r'});
            if (next->right != nullptr)
                next = next->right;
            else {
                next->right = newNode;
                break;
            }
        }
    }

    BalanceParents(stack);
}

template <class T>
AVLNode<T>* AVLTree<T>::FindMin(AVLNodePtr node) {

    while (node->left != nullptr)
        node = node->left;

    return node;
}

template <class T>
AVLNode<T>* AVLTree<T>::DeleteMin(AVLNodePtr node) {

    if( node->left == nullptr )
        return node->right;
    node->left = DeleteMin(node->left);

    return Balance(node);
}

template <class T>
void AVLTree<T>::Delete(T data) {

    if(root == nullptr) return;

    AVLNodePtr next = root;
    AVLNodePtr min = nullptr;
    stack<Path> stack;

    while (true) {
        if (data < next->data) {
            stack.push({next, 'l'});
            if (next->left != nullptr)
                next = next->left;
            else
                return;

        } else if (data > next->data) {
            stack.push({next, 'r'});
            if (next->right != nullptr)
                next = next->right;
            else
                return;
        } else {

            AVLNodePtr q = next->left;
            AVLNodePtr r = next->right;

            delete next;

            if(r == nullptr) {
                min = q;
                break;
            }

            min = FindMin(r);
            min->right = DeleteMin(r);
            min->left = q;

            break;
        }
    }

    if (!stack.empty()) {

        Path parent = stack.top();
        if (parent.c == 'l')
            parent.node->left = min;
        else
            parent.node->right = min;

        BalanceParents(stack);

    } else{
        root = min;
    }
}

template <class T>
T AVLTree<T>::FindKthStatistic(int k) {

    AVLNodePtr node = root;
    size_t index = GetSize(root->left);

    while (index != k) {
        if (k > index) {
            node = node->right;
            index += 1 + GetSize(node->left);
        } else {
            node = node->left;
            index -= 1 + GetSize(node->right);
        }
    }

    return node->data;
}

template <class T>
void AVLTree<T>::DestroyTree() {

    AVLNodePtr save;
    for (AVLNodePtr it = root; it != nullptr; it = save) {

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

int main() {

    int n;
    cin >> n;

    AVLTree<int> avlTree;

    for (int i=0; i < n; i++) {
        int data;
        int k;
        cin >> data >> k;

        if (data < 0)
            avlTree.Delete(-data);
        else
            avlTree.Add(data);

        cout << avlTree.FindKthStatistic(k) << endl;
    }

    return 0;
}