#include <Arduino.h>
#include <iostream>
#include <cstring>
#include <mutex>
#include "settings.h"

#include "Counts.h"

Counts::Counts(int queueLen){

    this->cpmQueue = new int[queueLen];
    this->previousTime = 0;
    this->currentPos = 0;
    this->queueLen = queueLen;

    std::memset(cpmQueue, 0, queueLen * 4);
}

Counts::~Counts(){

    delete [] cpmQueue;
}

void Counts::check(volatile int *tickCount){
    unsigned long currentTime = millis();
    unsigned long timeDelta = currentTime - previousTime;

    if (timeDelta > LOG_PERIOD){

        this->myMutex.lock();

        int newCpm = *tickCount * MINUTE_PERIOD / (timeDelta);
        *tickCount = 0;

        cpmQueue[currentPos] = newCpm;
        previousTime = currentTime;

        if(++currentPos > queueLen - 1){ currentPos = 0; }
        this->myMutex.unlock();
    }
}

int Counts::getQueueUtilisation(){
    
    this->myMutex.lock();

    int cpmCount = 0;
    for(int i = 0; i < this->queueLen; i++){
        if(this->cpmQueue[i] != 0){ cpmCount++; }
    }

    this->myMutex.unlock();

    return cpmCount;
}

int Counts::getCpm(int pos){

    this->myMutex.lock();

    int realIndex = this->currentPos - pos - 1;
    while(realIndex < 0) { realIndex = this->queueLen  + realIndex; }

    int returnVal = this->cpmQueue[realIndex];

    this->myMutex.unlock();

    return returnVal;
}