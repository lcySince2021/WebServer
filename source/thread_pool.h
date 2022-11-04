#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <queue>
#include <iostream>

template<class T>
class ThreadPool {
public:
    ThreadPool(int thread_num) {
        thread_num_ = thread_num;
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&cond_, NULL);
        for (int i = 0; i < thread_num_; ++i) {
            pthread_t tid;
            pthread_create(&tid, NULL, Routine, this);
            tids_.push_back(tid);
        }
    }

    ~ThreadPool() {
        printf("destory thread pool\n");
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&cond_);
        for (auto tid : tids_) {
            pthread_cancel(tid);
        }
    }

    void PushTask(T task) {
        Lock();
        queue_.push(task);
        UnLock();
        WakeUp();
    }

private:
    void Lock() { pthread_mutex_lock(&mutex_); }
    void UnLock() { pthread_mutex_unlock(&mutex_); }
    void Wait() { pthread_cond_wait(&cond_, &mutex_); }
    void WakeUp() { pthread_cond_signal(&cond_); }
    bool Empty() { return queue_.empty(); }
    void Pop(T& task) {
        task = queue_.front();
        queue_.pop();
    }

    static void* Routine(void* arg) {
        pthread_detach(pthread_self());
        ThreadPool* pool = (ThreadPool*)arg;
        while (true) {
            pool->Lock();
            while (pool->Empty()) {
                pool->Wait();
            }
            T task;
            std::cout << pthread_self() << std::endl;
            pool->Pop(task);
            pool->UnLock();
            task.Run();
        }
    }

private:
    int thread_num_;
    std::vector<pthread_t> tids_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
    std::queue<T> queue_;
};

#endif