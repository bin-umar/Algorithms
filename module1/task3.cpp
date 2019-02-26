//
// Created by jahongir on 18/10/18.
//

#include <iostream>

using namespace std;

/**
 *Реализовать очередь с динамическим зацикленным буфером.
 * Обрабатывать команды push back и pop front.

Формат ввода
    В первой строке количество команд n. n ≤ 1000000.
    Каждая команда задаётся как 2 целых числа: a b.

    a = 2 - pop front
    a = 3 - push back

    Если дана команда pop front, то число b - ожидаемое значение.
    Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

Формат вывода
    Требуется напечатать YES - если все ожидаемые значения совпали.
    Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 */

class Queue {
public:
    Queue();
    // явный конструктор копирования
    Queue(const Queue& other) = delete;
    // явный конструктор переноса
    Queue(Queue&& other) = default;
    // явный деструктор
    ~Queue();

    // явный операция-функция присваивания путем копирования
    Queue& operator=(const Queue& other) = delete;
    // явный операция-функция присваивания путем переноса
    Queue& operator =(Queue&& other);

    void push(int el);
    int pop();

private:
    int* q;
    int putIndex, getIndex;
    int allocSize = 4;

};

Queue::Queue() {
    q = new int[allocSize + 1];
    putIndex = getIndex = 0;
}

Queue& Queue::operator=(Queue&& queue) {

    swap(putIndex, queue.putIndex);
    swap(getIndex, queue.getIndex);
    swap(allocSize, queue.allocSize);
    swap(q, queue.q);

    queue.q = nullptr;
    queue.getIndex = 0;
    queue.getIndex = 0;
    queue.allocSize = 0;

    return *this;
}

Queue::~Queue() {
    delete []q;
}

void Queue::push(int el){

    if (putIndex == allocSize && getIndex == 0) {

        int* temp = new int[allocSize * 2 + 1];
        for (int i = 0; i <= allocSize; i++)
            temp[i] = q[i];

        delete[]q; // clean old memory
        q = temp; // get new memory

        allocSize *= 2;

    } else if ((putIndex + 1) == getIndex) {

        int* temp = new int[allocSize * 2 + 1];
        int i = 0;
        int begin = 0;

        while(getIndex <= allocSize)
            temp[i++] = q[getIndex++];

        while(begin <= putIndex)
            temp[i++] = q[begin++];

        delete[]q;
        q = temp;

        getIndex = 0;
        putIndex = i - 1;

        allocSize *= 2;
    }

    putIndex = (++putIndex) % (allocSize + 1);

    q[putIndex] = el;
}

int Queue::pop() {

    // If its Empty
    if (getIndex == putIndex)
        return -1;

    getIndex = (++getIndex) % (allocSize + 1);

    return q[getIndex];
}

bool doOperation(Queue &queue, int operation, int value) {

    if (operation == 3) {
        queue.push(value);
        return true;
    }

    if (operation == 2)
        return value == queue.pop();

    return false;
}

int main() {

    int n;
    cin >> n;

    Queue queue;

    for (int i=0; i < n; i++) {

        int operation, value;

        cin >> operation >> value;

        if (!doOperation(queue, operation, value)) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";


    return 0;
}