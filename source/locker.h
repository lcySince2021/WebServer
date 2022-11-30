#ifndef _LOCKER_H_
#define _LOCKER_H_

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <exception>


class Locker {
public:
    Locker() {
        if (pthread_mutex_init(&mtx_, NULL) != 0) {
            printf("mutex init failed\n");
            throw std::exception();
        }
    }

    ~Locker() {
        pthread_mutex_destroy(&mtx_);
    }

    bool Lock() {
        return pthread_mutex_lock(&mtx_) == 0;
    }

    bool UnLock() {
        return pthread_mutex_unlock(&mtx_) == 0;
    }

private:
    pthread_mutex_t mtx_;
};

class Sem {
public:
    Sem() {
        if (sem_init(&sem_, 0, 0) != 0) {
            printf("sem init 1 failed\n");
            throw std::exception();
        }
    }
    
    Sem(int value) {
        if (sem_init(&sem_, 0, value) != 0) {
            printf("sem init 2 failed\n");
            throw std::exception();
        }
    }

    ~Sem() {
        sem_destroy(&sem_);
    }

    bool Wait() {
        return sem_wait(&sem_) == 0;
    }

    bool Post() {
        return sem_post(&sem_) == 0;
    }
private:
    sem_t sem_;
};

#endif
