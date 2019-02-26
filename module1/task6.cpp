#include <iostream>

using namespace std;

/**
 *  Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
 *  Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с
 *  индексом k ∈[0..n-1] в отсортированном массиве. Напишите нерекурсивный алгоритм.
 *  Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
 *  Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 *  Описание для случая прохода от начала массива к концу:
 *  Выбирается опорный элемент.
 *  Опорный элемент меняется с последним элементом массива.
 *  Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы,
 *  строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
 *  Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 *  Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 *  Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
 *  Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 *  В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 */


template <class T>
int partition(T* arr, int n, int k) {

    swap(arr[k], arr[n-1]);

    int i, j;

    for (i = 0, j = 0; j < n -1; j++) {
        if (arr[j] <= arr[n-1]) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[n-1]);

    return i;

}

template <class T>
T kth_element(T* arr, int n, int k) {

    int pivot;

    while (true) {

        pivot = partition(arr, n, k);

        if (pivot > k) {
            n = pivot;
        } else if (pivot == k) {
            return arr[pivot];
        }
    }
}

int main() {

    int n, k;
    cin >> n >> k;

    int* arr = new int[n];

    for (int i=0; i < n; i++)
        cin >> arr[i];

    int result = kth_element(arr, n, k);
    cout << result;

    delete []arr;
    return 0;
}