#include <stdio.h>

int largestCombination(int* candidates, int candidatesSize) {
    int ans = 0;

    for (int i = 0; i < 24; i++) {
        int mask = 1 << i;
        int count = 0;

        for (int j = 0; j < candidatesSize; j++) {
                if (candidates[j] & mask) {
                    count++;
                }
            }

        // Atualiza ans com o maior valor de count
        if (count > ans) {
            ans = count;
        }
    }

    return ans;
}