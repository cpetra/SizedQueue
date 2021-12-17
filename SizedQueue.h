/******************************************************************************
 * @Date    : 2021-12-15 05:08:55
 * @Author  : Constantin Petra (constantin.petra@gmail.com)
 * @Link    : http://github.com/cpetra
 * @Version : 0.1
 *
 *****************************************************************************/

#ifndef __SIZED_QUEUE_H_INCLUDED
#define __SIZED_QUEUE_H_INCLUDED

#if defined(ESP8266) || defined(ESP32)
#define HAVE_SEMAPHORE
#include <freertos/semphr.h>
#endif

template <typename T, const size_t sz> 
class SizedQueue {
    T q[sz];
    const size_t size = sz;
    size_t last;
    size_t first;
#ifdef HAVE_SEMAPHORE
    SemaphoreHandle_t sem;
#endif
    inline void lock() {
        #if defined(HAVE_SEMAPHORE)
        xSemaphoreTake(sem, 0);
        #endif
    }

    inline void unlock() {
        #if defined(HAVE_SEMAPHORE)
        xSemaphoreGive(sem);
        #endif
    }

public:
    SizedQueue() {
        last = first = 0;
        #if defined(HAVE_SEMAPHORE)
        sem = xSemaphoreCreateMutex();
        #endif
    }

    ~SizedQueue() {
        #if defined(HAVE_SEMAPHORE)
        vSemaphoreDelete(sem);
        #endif
    }

    void push(const T&a) {
        lock();
        q[last] = a;
        if(++last >= size) {
            last = 0;
        }

        if (first == last) {
            if (++first >= size) {
                first = 0;
            }
        }
        unlock();
    }

    bool pop(T& a) {
        lock();
        if (last == first) {
            unlock();
            return false;
        }

        a = q[first];
        if (++first >= size) {
            first = 0;
        }
        unlock();
        return true;
    }

    bool peek() {
        bool ret;
        lock();
        ret = !(last == first);
        unlock();
        return ret;
    }
};
#endif /*__SIZED_QUEUE_H_INCLUDED*/

