
// Created by jahongir on 25/10/18.


#include <iostream>
#include <cassert>

using namespace std;

/**
 *  На числовой прямой окрасили N отрезков.
 *  Известны координаты левого и правого концов каждого отрезка [Li, Ri].
 *  Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 *  N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
 */

struct Point {
public:
    int value;
    char type;

    //  у нас i-input и o-output
    Point(): value(0), type('i') {};
    Point(int v, char t) {
        value = v;
        type = t;
    };
    Point(const Point& other) = delete;
    Point(Point&& other) = delete;
    ~Point() = delete;

    Point& operator=(const Point& other) = default;
    Point& operator=(Point&& other) = delete;
};

bool isLarger(Point& a, Point& b) {
    return a.value > b.value;
}

template <class T, class TLarger>
void merge(T* arr, int left, int middle, int right, TLarger larger) {

    int i, j, k;
    int n1 = middle - left + 1;
    int n2 =  right - middle;

    T lefts[n1], rights[n2];

    for (i = 0; i < n1; i++)
        lefts[i] = arr[left + i];

    for (j = 0; j < n2; j++)
        rights[j] = arr[middle + 1 + j];

    i = j = 0;
    k = left;

    while (i < n1 && j < n2) {

        if (larger(lefts[i], rights[j]))
            arr[k++] = rights[j++];
        else
            arr[k++] = lefts[i++];

    }

    while (i < n1)
        arr[k++] = lefts[i++];

    while (j < n2)
        arr[k++] = rights[j++];
}

template <class T, class TLarger>
void mergeSort(T* arr, int left, int right, TLarger larger) {

    if (left < right) {

        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle, larger);
        mergeSort(arr, middle + 1, right, larger);

        merge(arr, left, middle, right, larger);
    }
}

int layerMeasure (Point* arr, int size) {

    int result = 0,
            layers = 0,
            begin = -1;

    for (int i=0; i < size; i++) {

        if (arr[i].type == 'i')
            layers++;
        else
            layers--;

        if (layers != 1 && begin != -1) {

            result += arr[i].value - arr[begin].value;
            begin = -1;
        }
        else if (layers == 1)
            begin = i;

    }

    return result;
}

void test() {
    Point* points = new Point[10];

    int arr[] = {1,6,2,7,7,8,5,9,9,10};

    for (int i=0; i < 10; i += 2) {

        points[i].type = 'i';
        points[i].value = arr[i];

        points[i + 1].type = 'o';
        points[i + 1].value = arr[i + 1];
    }

    mergeSort(points, 0, 9, isLarger);

    for (int i=0; i < 10; i++) {
        cout << points[i].value << points[i].type << ' ';
    }

    cout << endl << layerMeasure(points, 10);

    delete []points;
}


int main() {

    int n;
    cin >> n;

    Point* points = new Point[n * 2];

    for (int i=0; i < n * 2; i += 2) {

        points[i].type = 'i';
        points[i + 1].type = 'o';

        cin >> points[i].value >> points[i + 1].value;

    }

    mergeSort(points, 0, n * 2 -1, isLarger);

    for (int i=0; i < n * 2; i++) {
        cout << points[i].value << points[i].type << ' ';
    }

    cout << endl << layerMeasure(points, n * 2);

    delete []points;

    return 0;
}