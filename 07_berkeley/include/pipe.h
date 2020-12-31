#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
  public:
    Pipe& operator<<(T value) {
        unique_lock<mutex> lck{mtx};
        not_empty.wait(lck, [this](){return !closed;});
        
        backend.push(value);

        not_empty.notify_one();

        return *this;
    }
    
    Pipe& operator>>(T& value) {
        unique_lock<mutex> lck{mtx};
        not_empty.wait(lck, [this](){return backend.size();});
        
        value = backend.front();
        backend.pop();
        
        return *this;
    }

    void close() {
        closed = true;
    }
    
    explicit operator bool() {
        return closed;
    }
};
#endif
