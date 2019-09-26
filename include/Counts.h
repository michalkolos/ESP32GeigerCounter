#ifndef COUNTS_H
#define COUNTS_H

#include <mutex>

class Counts{

private:
    int* cpmQueue;
    int currentPos;
    int queueLen;
    unsigned long previousTime;
    std::mutex myMutex;

public:
    Counts(int queueLen);
    ~Counts();

    void check(volatile int *tickCount);
    int getQueueUtilisation();
    int getCpm(int pos);

};


#endif