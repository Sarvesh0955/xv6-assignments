#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX 10

void multiplyMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int result[MAX][MAX], int row, int m, int n) {
    for (int i = 0; i < n; i++) {
        result[row][i] = 0;
        for (int j = 0; j < m; j++) {
            result[row][i] += m1[row][j] * m2[j][i];
        }
    }
}

int main() {
    int m1[MAX][MAX] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int m2[MAX][MAX] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    
    int result[MAX][MAX];
    int m = 3, n = 3, p = 3; 

    int pipes[MAX][2];
    for (int i = 0; i < m; i++) {
        pipe(pipes[i]);
    }

    for (int i = 0; i < m; i++) {
        int pid = fork();
        if (pid == 0) {
            close(pipes[i][0]);  
            multiplyMatrices(m1, m2, result, i, n, p);
            write(pipes[i][1], result[i], sizeof(result[i]));  
            close(pipes[i][1]); 
            exit();
        } else if (pid < 0) {
            printf(1, "Fork failed\n");
            exit();
        }
    }
    for (int i = 0; i < m; i++) {
        close(pipes[i][1]);  
        read(pipes[i][0], result[i], sizeof(result[i]));  
        close(pipes[i][0]);  
    }
    for (int i = 0; i < m; i++) {
        wait();
    }
    printf(1, "Resultant matrix (%dx%d):\n", m, p);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf(1, "%d ", result[i][j]);
        }
        printf(1, "\n");
    }

    exit();
}
