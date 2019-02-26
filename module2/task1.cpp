#include <iostream>
#include <string>

using namespace std;

/**
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
 * когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна поддерживать операции добавления строки
 * в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
 * Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
    g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

 */

template <class T>
int Hash(const T& key, size_t m);

template <>
int Hash(const string& key, size_t m) {

    int a = 31;
    int hash = 0;

    for (char i : key)
        hash = (hash * a + i) % (int)m;

    return hash;
}

template <class T>
struct HashTableData {};

template <>
struct HashTableData<string> {
    string data;
    bool isDeleted;
    explicit HashTableData(const string& _data = ""): data(_data), isDeleted(true) {};

    bool isNull() { return data.empty(); };
};

template <class T>
class HashTable {
public:
    HashTable(): buffer(8), alpha(0.75) { tableInit(); };
    HashTable(size_t size): buffer(size), alpha(0.75) { tableInit(); };
    HashTable(size_t size, double a): buffer(size), alpha(a) { tableInit(); };

    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;

    HashTable& operator=(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    ~HashTable() { delete []table; };

    bool Has(const T& key);
    bool Add(const T& key);
    bool Remove(const T& key);

private:
    size_t buffer; // M - size of table
    size_t elements = 0; // N - quantity of current elements of table
    double alpha;
    HashTableData<T>* table;

    inline void tableInit() { table = new HashTableData<T>[buffer]; };

    int QuadProbing(const T& key, int probe);
    void ReHash();
};

template <class T>
bool HashTable<T>::Has(const T& key) {

    for (int i=0; i < buffer; i++) {

        int hash = QuadProbing(key, i);

        if (table[hash].data == key && !table[hash].isDeleted)
            return true;
        else if (table[hash].isNull())
            break;
    }

    return false;
}

template <class T>
bool HashTable<T>::Add(const T& key) {

    if (Has(key))
        return false;

    for (int i=0; i < buffer; i++) {

        int hash = QuadProbing(key, i);

        if (table[hash].isDeleted) {

            table[hash].data = key;
            table[hash].isDeleted = false;
            break;

        }
    }

    if (++elements >= alpha * buffer)
        ReHash();

    return true;
};

template <class T>
bool HashTable<T>::Remove(const T &key){

    if (!Has(key))
        return false;

    for (int i=0; i < buffer; i++) {

        int hash = QuadProbing(key, i);

        if (!table[hash].isDeleted && table[hash].data == key) {
            table[hash].isDeleted = true;
            break;
        }
    }

    elements--;

    return true;
};

template <class T>
void HashTable<T>::ReHash(){

    auto* newTable = new HashTableData<T>[buffer *= 2];

    for (int j=0; j < buffer / 2; j++) {
        if (!table[j].isNull() && !table[j].isDeleted) {
            for (int i=0; i < buffer; i++) {

                int hash = QuadProbing(table[j].data, i);

                if (newTable[hash].isNull()) {
                    newTable[hash] = table[j];
                    break;
                }
            }
        }
    }

    delete []table;
    table = newTable;
};

template <class T>
int HashTable<T>::QuadProbing(const T& key, int probe) {

    int hash = Hash<T>(key, buffer);
    double c1 = 0.5, c2 = 0.5;

    hash = (int)(hash + c1 * probe + c2 * probe * probe) % (int)buffer;
    return hash;

};

template <class T>
void doOperation(HashTable<T>& hashTable, const T& key, char command) {
    switch (command) {
        case '?':
            cout << (hashTable.Has(key) ? "OK" : "FAIL") << endl;
            break;
        case '+':
            cout << (hashTable.Add(key) ? "OK" : "FAIL") << endl;
            break;
        case '-':
            cout << (hashTable.Remove(key) ? "OK" : "FAIL") << endl;
            break;
        default:
            cerr << "bad input" << endl;
            return;
    }
}


int main() {
    HashTable<string> hashTable;

    char command;
    string key;

    while(cin >> command >> key)
        doOperation<string>(hashTable, key, command);

    return 0;
}