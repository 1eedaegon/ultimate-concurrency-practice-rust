// 1. pthreads
// Rust도 결국 OS의 pthreads를 이용하기 때문에 이쪽에서부터 접근한다.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

void *thread_func(void *arg) {
    int id = (int)arg;
    for (int i=0; i<5; i++) {
        printf("id=%d, i=%d\n", id, i);
        sleep(1);
    }
    return "print finished!";
}

int main(int argc , char *argv[]) {
    pthread_t v[NUM_THREADS];

    for (int i=0; i<NUM_THREADS; i++ ) {
        /*
            첫번째에 pthread_t 타입의 포인터,
            두번째에 attribute(NULL은 기본값임),
            세번째에 스레드에 던질 함수,
            네번째에 함수에 전달할 매개변수

            pthread의 모든 함수는 에러발생 시 0 아닌 다른값을 리턴하고 errno와 호환된다.(과거지식이라 정확하지 않음)
        */
        if(pthread_create(&v[i], NULL, thread_func, (void *)i) != 0) {
            perror("pthread created.");
            return -1;
        }
    }

    for(int i=0; i<NUM_THREADS; i++) {
        char *ptr;
        // pthread_join() 하지않으면 메모리 누수가 발생한다.
        if (pthread_join(v[i], (void **)&ptr) == 0) {
            printf("msg = %s\n", ptr);
        } else {
            perror("pthread_join");
            return -1;
        }
    }
    return 0;
}

