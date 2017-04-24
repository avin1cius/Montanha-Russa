#ifndef DAVID_H_INCLUDED
#define DAVID_H_INCLUDED
#include <mutex>

class David
{
 public:
    David(){
    };

    std::mutex lock_mutex;

    bool TS(bool lock){
        lock_mutex.lock();
        bool initial = lock;
        lock = true;
        return initial;
        lock_mutex.unlock();
    }

    int FA(int &var, int incr){
        lock_mutex.lock();
        int tmp = var;
        var = var + incr;
        return tmp;
        lock_mutex.unlock();
    }

};

#endif // DAVID_H_INCLUDED
