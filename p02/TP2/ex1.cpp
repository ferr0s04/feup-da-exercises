// By: Gonçalo Leão
// With contributions by Eduardo Almeida

// Complexity: O(n^2)
int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int max;
    for (int x = 0; x < n; x++) {
        int sum = 0;
        for (int y = x; y < n; y++) {
            sum += A[y];
            if (sum > max) {
                max = sum;
                i = x;
                j = y;
            }
        }
    }
    return max;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}