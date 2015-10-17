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

char smallest_character(char str[], char c)
{
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] > c) return str[i];
        ++i;
    }
    return str[0];
}

int main()
{
    char str[] = {'c', 'f', 'j', 'p', 'v'};
    char c[3] = {'a', 'c', 'Z'};
    char result[3];
    struct timespec start, end;

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);

    int i;
    for (i = 0; i < 10000; ++i) {
        result[0] = smallest_character(str, c[0]);
        result[1] = smallest_character(str, c[1]);
        result[2] = smallest_character(str, c[2]);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double cpu_time = diff_in_second(start, end);

    printf("result[0]: %c\n", result[0]);
    printf("result[1]: %c\n", result[1]);
    printf("result[2]: %c\n", result[2]);
    printf("execution time: %lf sec\n", cpu_time);

    return 0;
}
