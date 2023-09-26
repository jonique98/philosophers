#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h> // for O_CREAT, O_EXCL
#include <unistd.h> // for sleep
#include <sys/wait.h> // for wait

int main() {
    sem_t *semaphore;
    const char *semaphoreName = "/my_semaphore";
    
    // 세마포어 생성 또는 열기, 초기 값은 5로 설정
    semaphore = sem_open("", O_CREAT | O_EXCL, 0777, 5);


    if (semaphore == SEM_FAILED) {
        perror("Semaphore creation/open failed");
        exit(1);
    }

    // 5개의 자식 프로세스 생성
    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // 자식 프로세스
            while (1) {
                // 세마포어 획득 (2개만 얻으면 실행)
                sem_wait(semaphore);
                sem_wait(semaphore);

                printf("Child acquired 2 semaphores. Value: \n");
                
                // 일부 작업 수행 (예: 임의의 작업 시뮬레이션)
                sleep(rand() % 3);
                
                // 세마포어 반환
                sem_post(semaphore);
                sem_post(semaphore);
                printf("Child released 2 semaphores. Value: n");
                
                // 일부 작업 수행 (예: 임의의 작업 시뮬레이션)
                sleep(rand() % 3);
            }
            exit(0);
        }
    }

    // 부모 프로세스는 모든 자식 프로세스의 종료를 기다림
    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    // 세마포어 삭제
    sem_unlink(semaphoreName);
	sem_close(semaphore);

    return 0;
}
