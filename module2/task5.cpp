#include <bits/stdc++.h>
#include <time.h>
typedef char byte;
typedef bool bit;
#define interface struct

using namespace std;

int w = 0, r = 0;

interface IInputStream {
    IInputStream(ifstream& inpF): inpFile(inpF) {}

    bool Read(byte& value){
        if(inpFile.eof())
            return false;
        r++;
        inpFile.get(value);
        return true;
    }

private:
    ifstream& inpFile;
};

interface IOutputStream {
    IOutputStream(ofstream& outF): outFile(outF) {}
    void Write(byte value) {
        w++;
        outFile << value;
    }

private:
    ofstream& outFile;
};

/// Input Output Stream

class InBitStream {
public:
    explicit InBitStream(IInputStream& stream): inputStream(stream), buffer(0), bitsCount(0) {}
    bool ReadBit(bit &b);
    void ReadByte(byte &b);

private:
    IInputStream& inputStream;
    int bitsCount;
    byte buffer;
};

bool InBitStream::ReadBit(bit &b) {

    if (bitsCount == 0) {
        if (!inputStream.Read(buffer))
            return false;
    }

    b = buffer & (1 << bitsCount);

    bitsCount = (bitsCount + 1) % 8;
    return true;
}

void InBitStream::ReadByte(byte &b) {

    b = 0;
    bit tmp;

    for (int i = 0; i < 8; i++) {
        b <<= 1;
        if (!ReadBit(tmp))
            return;
        b |= 1 & tmp;
    }

    byte rev = 0;

    for(int i=0; i < 8; i++)
        rev |= ((b >> i) & 1) << (7 - i);
    b = rev;
}

class OutBitStream {
public:
    explicit OutBitStream(IOutputStream& stream): outputStream(stream), buffer(0), bitsCount(0) {}
    void WriteBit(bit b);
    void WriteByte(byte value);
    int GetBitsCount();
    int Finish();

private:
    IOutputStream& outputStream;
    int bitsCount;
    byte buffer;
};

void OutBitStream::WriteBit(bit b) {

    if(b)
        buffer |= 1 << bitsCount;

    bitsCount = ( bitsCount + 1 ) % 8;
    if( bitsCount == 0 ) {
        outputStream.Write(buffer);
        buffer = 0;
    }
}

void OutBitStream::WriteByte(byte value) {
    for( int i = 0; i < 8; ++i )
        WriteBit( ( value & ( 1 << i ) ) != 0 );
}

int OutBitStream::GetBitsCount() {
    return bitsCount;
}

int OutBitStream::Finish() {
    if (bitsCount > 0)
        outputStream.Write(buffer);
}

///  Node
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(int f, char d): data(d), freq(f), left(nullptr), right(nullptr) {}
    Node(char d, Node* l, Node* r): data(d), left(l), right(r) {
        freq = l->freq + r->freq;
    }
};

struct NodeCompare {
    bool operator() (Node* l, Node* r) {
        return l->freq < r->freq;
    }
};

/// Huffman Tree

typedef map<char, vector<bool>> codeTable;

class HuffmanTree {
public:
    HuffmanTree(): root(nullptr) {};
    explicit HuffmanTree(map<char, int>& m);

    HuffmanTree(const HuffmanTree&) = delete;
    HuffmanTree(HuffmanTree&&) = delete;

    codeTable GetTable();
    Node* GetRoot();
    void BuildTable(Node* _root);
    void EncodeTree(OutBitStream& outBitStream);
    void DecodeTree(InBitStream& inBitStream, int count);
    void ReadStream(InBitStream& inBitStream, IOutputStream& original, int zeroes);

    HuffmanTree& operator=(const HuffmanTree&) = delete;
    HuffmanTree& operator=(HuffmanTree&&) = delete;

    ~HuffmanTree() {
        DestroyTree();
    }

private:
    Node* root;
    vector<bool> code;
    codeTable table;

    struct TreeCode {
        byte data;
        bit path;

        TreeCode(byte b, bit p): data(b), path(p) {}
    };

    void TreeToStack(Node* _root, stack<TreeCode>& stack);
    void DestroyTree();
};

HuffmanTree::HuffmanTree(map<char, int>& m){

    list<Node*> t;

    map<char, int>::iterator i;
    for(i = m.begin(); i != m.end(); i++)
        t.push_back(new Node(i->second, i->first));

    while (t.size() != 1) {

        t.sort(NodeCompare());

        Node* left = t.front();
        t.pop_front();

        Node* right = t.front();
        t.pop_front();

        Node* parent =  new Node('~', left, right);
        t.push_back(parent);
    }

    root = t.front();
}

codeTable HuffmanTree::GetTable() {
    return table;
}

Node* HuffmanTree::GetRoot(){
    return root;
}

void HuffmanTree::BuildTable(Node *_root) {

    if (_root->left != nullptr) {
        code.push_back(0);
        BuildTable(_root->left);
    }

    if (_root->right != nullptr) {
        code.push_back(1);
        BuildTable(_root->right);
    }

    if (_root->right == nullptr && _root->left == nullptr)
        table[_root->data] = code;

    code.pop_back();
}

void HuffmanTree::EncodeTree(OutBitStream& outBitStream) {

    stack<TreeCode> stack;
    TreeToStack(root, stack);

    while (!stack.empty()) {

        TreeCode treeCode = stack.top();
        stack.pop();

        if (treeCode.path == 1) {
            outBitStream.WriteBit(treeCode.path);
            outBitStream.WriteByte(treeCode.data);
        } else
            outBitStream.WriteBit(treeCode.path);
    }
}

void HuffmanTree::DecodeTree(InBitStream& inBitStream, int count) {

    stack<Node*> stack;
    bit b;
    byte symbol;

    int _count = count * 2 - 1;
    while (_count > 0) {

        inBitStream.ReadBit(b);
        _count--;

        if (b == 1) {

            inBitStream.ReadByte(symbol);
            Node* p = new Node(0, symbol);
            stack.push(p);

        } else {

            Node* right = stack.top();
            stack.pop();

            Node* left = stack.top();
            stack.pop();

            Node* parent = new Node('\0', left, right);
            stack.push(parent);
        }
    }

    root = stack.top();
    stack.pop();
}

void HuffmanTree::TreeToStack(Node* _root, stack<TreeCode>& stack)  {

    if (!_root) return;

    if (_root->data != '~') {
        TreeCode treeCode(_root->data, 1);
        stack.push(treeCode);
    }

    if (_root->data == '~') {
        TreeCode treeCode('\0', 0);
        stack.push(treeCode);
    }

    TreeToStack(_root->right, stack);
    TreeToStack(_root->left, stack);
}

void HuffmanTree::ReadStream(InBitStream& inBitStream,  IOutputStream& original, int zeroes) {

    bool b;
    Node *p = root;

    vector<bool> bools;

    while (inBitStream.ReadBit(b))
        bools.push_back(b);

    int s = bools.size();
//    cout << bools.size() << endl;
//    cout << zeroes << endl;

    bools.resize(s - zeroes - 9);

    for (bit b: bools) {

        if (b)
            p = p->right;
        else
            p = p->left;

        if (p->left == nullptr && p->right == nullptr) {
            original.Write(p->data);
            p = root;
        }
    }

    bools.clear();
}

void HuffmanTree::DestroyTree() {

    Node* save;
    for (Node* it = root; it != nullptr; it = save) {

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

void Encode(IInputStream& original, IOutputStream& compressed) {

    map<char, int> m;
    byte value = 0;
    string stream;

    while (original.Read(value)){
        m[value]++;
        stream += value;
    }

    HuffmanTree huffmanTree(m);
    huffmanTree.BuildTable(huffmanTree.GetRoot());

    codeTable table = huffmanTree.GetTable();

    OutBitStream outBitStream(compressed);

    byte symbolsCount = (byte)table.size();

    compressed.Write(symbolsCount); // количество символов на нашем таблице
    huffmanTree.EncodeTree(outBitStream); // закодируем дерево и запишем его на stream

    vector<bool> elements;

    for(char c: stream) {
        vector<bool> x = table[c];

        for (auto &&n: x)
            elements.push_back(n);
    }

    int zeroes = (8 - (elements.size() + outBitStream.GetBitsCount()) % 8);
//    cout << outBitStream.GetBitsCount() << endl;
    outBitStream.WriteByte((byte)zeroes);
//    cout << zeroes << endl;
    for (auto &&el: elements)
        outBitStream.WriteBit(el);

    outBitStream.Finish();
//    cout << outBitStream.GetBitsCount() << endl;
}

void Decode(IInputStream& compressed, IOutputStream& original) {

    HuffmanTree huffmanTree;

    byte symbolsCount;
    compressed.Read(symbolsCount);

    unsigned char count = (unsigned char)symbolsCount;

    InBitStream inBitStream(compressed);
    huffmanTree.DecodeTree(inBitStream, count);

    char zeroes;
    inBitStream.ReadByte(zeroes);
    huffmanTree.ReadStream(inBitStream, original, (int)zeroes);
}

int main() {

    clock_t tStart = clock();
//    ifstream f("input.txt", ios::in | ios::binary);
    ifstream f("npm-debug.log");

    ofstream g("output.bin", ios::out | ios::binary);

    IInputStream inputStream(f);
    IOutputStream outputStream(g);

    Encode(inputStream, outputStream);

    f.close();
    g.close();

    cout << "write = " << w << endl;
    cout << "read = " << r << endl;

    w = r = 0;

    ifstream input("output.bin", ios::in | ios::binary);
    ofstream output("npm-debug2.log");
//    ofstream output("output2.txt", ios::out | ios::binary);

    IInputStream inputStr(input);
    IOutputStream outputStr(output);

    Decode(inputStr, outputStr);

    input.close();
    output.close();

    cout << "write = " << w << endl;
    cout << "read = " << r << endl;

    cout << (double)(clock() - tStart) / CLOCKS_PER_SEC;
    return 0;
}