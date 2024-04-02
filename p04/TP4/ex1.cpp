#include "exercises.h"
#include "cmath"

/* Bruteforce approach
 *
 * int maxSubsequence(int A[], unsigned int n, int &i, int &j) {
    int sum = A[0];
    i = j = 0;

    for (int s = 0; s < n; s++) {
        for (int e = s; e < n; e++) {
            int current = 0;
            for (int k = s; k <= e; k++) {
                current += A[k];
            }

            if (current > sum) {
                sum = current;
                i = s;
                j = e;
            }
        }
    }
    return sum;
}
 */

// Handle cases when the subarray crosses the mid of the array
int maxCrossing(int A[], int low, int mid, int high, int &l, int &r) {
    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = mid;

    for (int i = mid; i >= low; --i) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int maxRight = mid + 1;

    for (int i = mid + 1; i <= high; ++i) {
        sum += A[i];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = i;
        }
    }

    l = maxLeft;
    r = maxRight;

    return leftSum + rightSum;
}

// Auxiliary recursive function
int subSequenceAux(int A[], int low, int high, int &i, int &j) {
    if (low == high) {
        i = low;
        j = high;
        return A[low];
    }

    int mid = (low + high) / 2;
    int leftLow, leftHigh, rightLow, rightHigh, crossLow, crossHigh;
    int leftSum = subSequenceAux(A, low, mid, leftLow, leftHigh);
    int rightSum = subSequenceAux(A, mid + 1, high, rightLow, rightHigh);
    int crossSum = maxCrossing(A, low, mid, high, crossLow, crossHigh);

    if (leftSum >= rightSum && leftSum >= crossSum) {
        i = leftLow;
        j = leftHigh;
        return leftSum;
    } else if (rightSum >= leftSum && rightSum >= crossSum) {
        i = rightLow;
        j = rightHigh;
        return rightSum;
    } else {
        i = crossLow;
        j = crossHigh;
        return crossSum;
    }
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if (n == 0) {
        return 0;
    }

    return subSequenceAux(A, 0, n - 1, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}