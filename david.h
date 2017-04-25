#ifndef DAVID_H_INCLUDED
#define DAVID_H_INCLUDED
#include <mutex>

class David
{
    std::mutex lock_mutex;
  public:
    David(){
    };

    bool TS(bool &lock){
        lock_mutex.lock();
        bool initial = lock;
        lock = true;
        lock_mutex.unlock();
        return initial;
    }

    int FA(int &var, int incr){
        lock_mutex.lock();
        int tmp = var;
        var = var + incr;
        lock_mutex.unlock();
        return tmp;
    }

};

#endif // DAVID_H_INCLUDED
