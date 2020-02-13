#include "fib_heap.h"

#define N 100

int main() {
    fib_heap <int, int> f(N);
    // insert test
    for (int i=0; i<N; i++) {
        f.insert(i,i);
//        printf("insert (%d, %d)\n", i, i);
    }

    // deletemin
    for (int i=0; i<N; i++) {
        int argmin = f.deletemin();
        printf("deleted key is %d\n", argmin);
    }

    // decrease key

    return 0;
}
