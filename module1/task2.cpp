//
// Created by jahongir on 17/10/18.
//

#include <iostream>
#include <cmath>
/**
 *Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 *Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
 * ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
 * Время работы поиска для каждого элемента B[i]: O(log(k)).
 */

using namespace std;

int BinaryTwinSearch(const int*, int, int, int);

int TwinSearch(const int[], int, int);

int main() {

    int n, i;
    cin >> n;

    int A[n];
    for(i = 0; i < n; i++)
        cin >> A[i];

    int m;
    cin >> m;

    int B[m];
    for(i = 0; i < m; i++)
        cin >> B[i];

    for(i = 0; i < m; i++)
        cout << TwinSearch(A, n, B[i]) << ' ';

    return 0;
}

int BinaryTwinSearch(const int* array, int begin, int end, int el) {

    int left = begin,
            right = end,
            mid = 0;

    int twinIndex = begin;
    int twin = array[twinIndex];
    int difference = abs(twin - el);

    while (left <= right) {

        mid = left + (right - left) / 2;

        if(array[mid] == el)
            return mid;
        else if(array[mid] > el)
            right = mid - 1;
        else
            left = mid + 1;

        int _difference = abs(array[mid] - el);

        if (_difference < difference || (twin > array[mid] && _difference == difference)) {
            twinIndex = mid;
            twin = array[mid];
            difference = _difference;
        }

    }

    return twinIndex;
}

int TwinSearch(const int array[], int size, int el) {

    int k = 1,
            prepos = 0;

    while (k <= size) {

        if (array[k - 1] == el)
            return k - 1;


        if (array[k - 1] > el)
            return BinaryTwinSearch(array, prepos, k - 1, el);
        else {
            if (k == size) return k - 1;
        }

        prepos = k - 1;

        k *= 2;
        if (k > size) k = size;
    }

    return -1;
}
