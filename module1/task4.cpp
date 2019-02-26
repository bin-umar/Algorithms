//
// Created by jahongir on 19/10/18.
//

#include <iostream>
#include <cassert>

using namespace std;

/**
 * На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 * Этот вокзал является их конечной станцией. Дано расписание движения электричек,
 * в котором для каждой электрички указано время ее прибытия, а также время отправления в следующий рейс.
 * Электрички в расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в свободный
 * тупик с минимальным номером. При этом если электричка из какого-то тупика отправилась в момент времени X,
 * то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку,
 * прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное количество
 * тупиков для работы по расписанию. Напишите программу, которая по данному расписанию определяет,
 * какое минимальное количество тупиков требуется для работы вокзала.
 */

struct ETrain {
    int arrivalTime;
    int nextFlight;
};

class PQueue {
public:
    PQueue();
    // явный конструктор копирования
    PQueue(const PQueue& other) = delete;
    // явный конструктор переноса
    PQueue(PQueue&& other) = default;
    // явный деструктор
    ~PQueue();

    // явный операция-функция присваивания путем копирования
    PQueue& operator=(const PQueue& other) = delete;
    // явный операция-функция присваивания путем переноса
    PQueue& operator=(PQueue&& other);

    ETrain getTop() { return trains[0]; }; //
    int getDeadlocks() { return deadlocks; }; // Количество тупиков

    void insert(ETrain newTrain);
    ETrain remove();

    bool isEmpty() { return top < 0; };

private:
    void increaseMemory();

    void siftUp(int index);     // Проталкиваем элемента вверх
    void siftDown(int index);   // Проталкиваем элемента вверх

    ETrain* trains;
    int top;
    int allocSize = 4;
    int deadlocks;

};

PQueue::PQueue() {

    trains = new ETrain[allocSize];
    top  = -1;
    deadlocks = 0;

}

PQueue& PQueue::operator=(PQueue&& PQueue) {

    swap(top, PQueue.top);
    swap(allocSize, PQueue.allocSize);
    swap(trains, PQueue.trains);

    PQueue.trains = nullptr;
    PQueue.top = 0;
    PQueue.allocSize = 0;

    return *this;
}

PQueue::~PQueue() {
    delete []trains;
}

void PQueue::siftUp(int index) {

    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;

        if( trains[index].nextFlight >= trains[parent].nextFlight )
            return;
        swap( trains[index], trains[parent] );
        index = parent;
    }

}

void PQueue::siftDown(int index) {

    int left = 2 * index + 1;
    int right = 2 * index + 2;
    // Ищем большего сына, если такой есть.
    int largest = index;
    if( left < allocSize && trains[left].nextFlight < trains[index].nextFlight )
        largest = left;
    if( right < allocSize && trains[right].nextFlight < trains[largest].nextFlight )
        largest = right;
    // Если больший сын есть, то проталкиваем корень в него.
    if( largest != index ) {
        swap( trains[index], trains[largest] );
        siftDown(largest );
    }

}

void PQueue::increaseMemory() {

    ETrain* temp = new ETrain[allocSize * 2];

    for (int i = 0; i < allocSize; i++)
        temp[i] = trains[i];

    delete[]trains; // clean old memory
    trains = temp; // get new memory

    allocSize *= 2;
}

void PQueue::insert(ETrain newTrain) {

    if (top + 1 >= allocSize) increaseMemory();

    trains[++top] = newTrain;

    siftUp(top);

    deadlocks = top + 1 > deadlocks ? top + 1: deadlocks;
}

ETrain PQueue::remove() {

    assert(!isEmpty());

    ETrain result = trains[0];
    trains[0] = trains[top];

    top--;
    siftDown(0);

    return result;
}


int main() {

    int n;
    cin >> n;

    PQueue station;
    ETrain newTrain;

    for (int i=0; i < n; i++) {

        cin >> newTrain.arrivalTime >> newTrain.nextFlight;

        if (!station.isEmpty()) {

            while (station.getTop().nextFlight < newTrain.arrivalTime)
                station.remove();
        }

        station.insert(newTrain);
    }

    cout << station.getDeadlocks();

    return 0;
}