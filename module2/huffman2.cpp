#include <bits/stdc++.h>
#include "iostream"
using namespace std;

struct Node {
    int a;
    char c;
    Node *left, *right;

    explicit Node(int _a, char _c): a(_a), c(_c), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r): left(l), right(r) {
        a = l->a + r->a;
    }
};

struct MyCompare {
    bool operator() (Node* l,  Node* r) {
        return l->a < r->a;
    }
};

vector<bool> code;
map<char, vector<bool>> table;

void BuildTable(Node* root) {

    if (root->left != nullptr) {
        code.push_back(0);
        BuildTable(root->left);
    }

    if (root->right != nullptr) {
        code.push_back(1);
        BuildTable(root->right);
    }

    if (root->right == nullptr && root->left == nullptr)
        table[root->c] = code;

    code.pop_back();
}


int main() {

    ifstream f("input.txt");

    map<char, int> m;

    while (!f.eof()) {
        char c = f.get();
        m[c]++;
    }

    list<Node*> t;

    map<char, int>::iterator i;
    for(i = m.begin(); i != m.end(); i++) {
        Node *p = new Node(i->second, i->first);
        t.push_back(p);
    }

    while (t.size() != 1) {

        t.sort(MyCompare());

        Node* left = t.front();
        t.pop_front();

        Node* right = t.front();
        t.pop_front();

        Node* parent =  new Node(left, right);
        t.push_back(parent);
    }

    Node* root = t.front();

    BuildTable(root);

    f.clear();
    f.seekg(0);

    ofstream g("output.txt");

    int count=0; char buf=0;
    int writeCount = 0;

    while (!f.eof()) {
        char c = f.get();
        vector<bool> x = table[c];

        for (auto &&n : x) {

            buf = buf | n << (7 - count);
            count++;
            if (count == 8) {
                count = 0;
                g << buf;
                buf = 0;
                writeCount++;
            }
        }
    }

    f.close();
    g.close();

    ifstream F("output.txt");

    Node *p = root;
    count=0;
    int rCount = 0;
    char byte;
    byte = F.get();
    while(!F.eof()){
        bool b = byte & (1 << (7-count));

        if (b) p=p->right; else p=p->left;
        if (p->left == nullptr && p->right == nullptr) {
            cout << p->c;
            p=root;
        }

        count++;
        if (count == 8) {
            count=0; byte = F.get();
            rCount++;
        }
    }

    F.close();

    cout << writeCount << endl;
    cout << rCount << endl;

    return 0;
}
