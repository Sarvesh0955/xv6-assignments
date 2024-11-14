#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define TOTAL_SUM 20

typedef struct {
    int start;
    int end;
    int partial_sum;
} ThreadData;

void* calculate_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_sum = 0; 	
    for (int i = data->start; i <= data->end; i++) {
        data->partial_sum += i;
    }
    return NULL;
}

int threaded_sum(int n_threads) {
    pthread_t threads[n_threads];
    ThreadData thread_data[n_threads];
    int range_size = TOTAL_SUM / n_threads;
    int remainder = TOTAL_SUM % n_threads;

    for (int i = 0; i < n_threads; i++) {
        thread_data[i].start = i * range_size + 1;
        thread_data[i].end = (i + 1) * range_size;
        if (i == n_threads - 1) {
            thread_data[i].end += remainder;
        }
        pthread_create(&threads[i], NULL, calculate_sum, &thread_data[i]);
    }

    int total_sum = 0;
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    return total_sum;
}

int single_thread_sum() {
    int total_sum = 0;
    for (int i = 1; i <= TOTAL_SUM; i++) {
        total_sum += i;
    }
    return total_sum;
}

int main() {
    clock_t start, end;
    double time_taken;

    start = clock();
    int single_result = single_thread_sum();
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Single-thread result: %d, Time: %f seconds\n", single_result, time_taken);

    int thread_counts[] = {2, 4, 10};
    for (int i = 0; i < 3; i++) {
        int n_threads = thread_counts[i];
        start = clock();
        int threaded_result = threaded_sum(n_threads);
        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d-thread result: %d, Time: %f seconds\n", n_threads, threaded_result, time_taken);
    }

    return 0;
}
