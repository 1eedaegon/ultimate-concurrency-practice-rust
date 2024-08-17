// 2. detach-thread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
    pthread(POSIX thread) 사용으로 메모리 누수를 막는 방법이...
    1. join
    2. detach thread
    
    근데 detach thread를 생성하는 방법도 2가지다.
    1. pthreads에 attr을 주는 방법
    2. pthreads_detach()를 호출하는 방법
*/

void *thread_func(void *arg) {
    for (int i=0; i<5; i++) {
        printf("i = %d\n",i);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // attr 초기화
    pthread_attr_t attr;
    if (pthread_attr_init(&attr) != 0) {
        perror("pthread_attr_init");
        return -1;
    }
    // attr의 상태를 PTHREAD_CREATE_DETACHED로 바꾸고
    // 꿀팁은 attr로 stack size나 cpu affinity 설정도 가능함!
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        return -1;
    }

    // attr과 함께 생성
    pthread_t th;
    if (pthread_create(&th, &attr, thread_func, NULL) != 0) {
        perror("pthread_create");
        return -1;
    }

    // 생성했으면 파괴해야한다.
    if (pthread_attr_destroy(&attr) != 0) {
        perror("pthread_attr_destroy");
        return -1;
    }
    sleep(5);

    return 0;
}

// 흠... 그럼 2. pthreads_detach()를 호출하는 방법 은 어떻게?
// 굉장히 간단한 함수를 심어놓고 끝.
// pthread_self()로 현재 실행중인 함수의 scope와 정보를 얻은다음
// pthreads_detach로 전달해서 detach로 만든다.
/*
void *detach_thread_func() {
    pthreads_detach(pthread_self());
    for (int i=0; i<5; i++) {
        printf("i = %d\n",i);
        sleep(1);
    }
    return NULL;
}
*/   