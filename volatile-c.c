// 3. with volatile

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


/*
    makefile에 -03과 -S를 넣어서 컴파일 최적화 최대로 땡긴다음 출력하면?
    여기의 완성은 알아서
*/

/*
결과가 아래와 같음
    1. gcc -O3 -S ....
    wait_while_0:
        ldr w8, [x0]
        cbz w8, .LBB0_2
        ret
    .LBB0_2:
        b .LBB0_2
*/
void wait_while_0(int *p) {
    while(*p==0) P {}
}

/*
결과가 아래와 같음
    2. gcc -O3 -S ....(with volatile)
    wait_while_0:
    .LBB0_1:
        ldr w8, [x0]
        cbz w8, .LBB0_1
        ret
*/

void wait_while_0(volatile int *p) {
    while(*p==0) P {}
}
// 컴파일 최적화가 aarch64 명령어를 생성한다.
// x0을 읽어서 w8레지스터 저장
// Compare and branch(jump to .LBB0_1) if zero w8
// if not zero, return