CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99
PERF_STAT ?= perf stat -e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses

EXEC = iterative recursive
all: $(EXEC)

iterative: iterative.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

recursive: recursive.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

clean:
	$(RM) $(EXEC) *.o perf.*

clean_cache:
	echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh

stat_iterative: clean_cache
	$(PERF_STAT) ./iterative

stat_recursive: clean_cache
	$(PERF_STAT) ./recursive
