#ifndef ATOMICO_H
#define ATOMICO_H

#include <mutex>

class Atomico {
    std::mutex lock_mutex;

  public:

    Atomico() {
    }

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

#endif /* ATOMICO_H  */
