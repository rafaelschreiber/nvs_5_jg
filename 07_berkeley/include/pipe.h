#ifndef _PIPE_H_
#define _PIPE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
    long latency{0};
  public:
    Pipe& operator<<(T value) {
        unique_lock<mutex> lock{mtx};
        not_empty.wait(lock, [this](){return !closed;});
        
        this_thread::sleep_for(std::chrono::duration<long>(latency));
        backend.push(value);
        not_empty.notify_one();

        return *this;
    }
    
    Pipe& operator>>(T& value) {
        unique_lock<mutex> lock{mtx};
        not_empty.wait(lock, [this](){return backend.size();});

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

    void set_latency(long latency_duration){
        latency = latency_duration;
    }
};
#endif
