/* iterative version */
#include <stdio.h>
#include <time.h>
#include <assert.h>

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int maxSubArray(int A[], int n)
{
	int head, tail, i, temp, sum = A[0];
	for (head = 0; head < n; ++head) {
		for (tail = head; tail < n; ++tail) {
			temp = 0;
			for (i = head; i < tail; ++i) {
				temp += A[i];
			}
			if (temp > sum) sum = temp;
		}
	}

	return sum;
}

int main()
{
    struct timespec start, end;
	int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int i, sum;

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 0; i < 10000; ++i) {
		sum = maxSubArray(A, sizeof(A)/sizeof(A[0]));
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double cpu_time = diff_in_second(start, end);

	printf("Sum: %d\n", sum);
    printf("execution time: %lf sec\n", cpu_time);

    return 0;
}
