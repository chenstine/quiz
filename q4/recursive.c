/* recursive version */
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
	int sum = A[0], i, temp = 0, sum2 = A[0];

	if (n > 1) {
		sum2 = maxSubArray(A+1, n-1);
	}

	for (i = 0; i < n; ++i) {
		temp += A[i];
		if (temp > sum) sum = temp;
	}

	if (sum > sum2) return sum;
	else return sum2;
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
