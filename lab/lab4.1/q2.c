#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 100

typedef struct {
    int row;
    int col;
    int N;
    int** mat1;
    int** mat2;
    int** result;
} ThreadData;

void* calculate_element(void* arg) {
ThreadData* data = (ThreadData*)arg;
data->result[data->row][data->col] = 0;
for (int k = 0; k < data->N; k++) {
data->result[data->row][data->col] += data->mat1[data->row][k] * data->mat2[k][data->col];
}
pthread_exit(0);
}

void print_matrix(int** matrix, int N) {
for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
printf("%d ", matrix[i][j]);
}
printf("\n");

}
}

int** allocate_matrix(int N) {
int** matrix = (int**)malloc(N * sizeof(int*));
for (int i = 0; i < N; i++) {
matrix[i] = (int*)malloc(N * sizeof(int));
}
return matrix;
}

int main() {
int N;
printf("Enter the size of the matrices (N x N): ");
scanf("%d", &N);

int** mat1 = allocate_matrix(N);
int** mat2 = allocate_matrix(N);
int** result = allocate_matrix(N);

printf("Enter elements of the first matrix:\n");
for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
scanf("%d", &mat1[i][j]);
}
}

printf("Enter elements of the second matrix:\n");
for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
scanf("%d", &mat2[i][j]);

}
}

pthread_t threads[MAX_THREADS];
ThreadData thread_data[MAX_THREADS];
int thread_count = 0;

clock_t start = clock();

for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
thread_data[thread_count].row = i;
thread_data[thread_count].col = j;
thread_data[thread_count].N = N;
thread_data[thread_count].mat1 = mat1;
thread_data[thread_count].mat2 = mat2;
thread_data[thread_count].result = result;
pthread_create(&threads[thread_count], NULL, calculate_element,
&thread_data[thread_count]);
thread_count++;
}
}

for (int i = 0; i < thread_count; i++) {
pthread_join(threads[i], NULL);
}

clock_t end = clock();
double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

printf("Result (with threads):\n");

print_matrix(result, N);
printf("Time taken (with threads): %f seconds\n", time_taken);

for (int i = 0; i < N; i++) {
free(mat1[i]);
free(mat2[i]);
free(result[i]);
}
free(mat1);
free(mat2);
free(result);

return 0;
}