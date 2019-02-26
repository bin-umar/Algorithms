#include <iostream>
/**
 * Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j],
 * где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n). n ≤ 100000.
 */

using namespace std;

int main() {

    int n;
    cin >> n;

    int A[n], B[n];
    int i, j;

    for (i = 0; i < n; i++) cin >> A[i];
    for (j = 0; j < n; j++) cin >> B[j];


    int maxSum = 0, indexI = 0, indexJ = 0;

    for (i = 0; i < n; i++) {

        if(A[i] > A[indexI] && indexJ >= i) {

            indexI = i;
            maxSum = A[i] + B[indexJ];

        } else if(A[i] > A[indexI] && indexJ < i) {

            int _indexJ = i;
            for(j = i + 1; j < n; j++)
                if (B[j] > B[_indexJ])
                    _indexJ = j;

            int sum = A[i] + B[_indexJ];
            if (maxSum < sum) {
                maxSum = sum;
                indexI = i;
                indexJ = _indexJ;
            }

        }
    }

    cout << indexI << " " << indexJ;

    return 0;
}

