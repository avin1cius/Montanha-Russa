#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread {
    pthread_t id;
	static void *staticRun(void *args);

 public:
	Thread();
	virtual ~Thread();
	void start();
	virtual void run() = 0;
	void join();
	pthread_t getId();
};

#endif /* THREAD_H_ */