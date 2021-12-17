# SizedQueue
An Arduino library.

Fast FIFO based on circular buffer (if the queue is full, the oldest one will be overwritten by a "push").

Suitable mostly for the ESP family (uses FreeRtos mutices for thread safety), Should also work with non-FreeRtos based controllers, but needs manual synchronization on access.

The circular array is statically allocated.

Include and initialization:
```c
#include <SizedQueue.h>

typedef struct {
    int v1;
    int v2;
} _svals;

SizedQueue<_svals, 20> m_queue;
```

Consumer thread example:
```c
static void show()
{
  _svals v;

  while (1) {
    while (m_queue.pop(v)) {
      Serial.print(" " + String(v.v1) + "," + String(v.v2));
    }
    Serial.println("");
    delay(1000);
  }
}
```
Producer:
```c
void loop()
{
  _svals v;
  v.v1 = i++;
  v.v2 = random(100);
  m_queue.push(v);
  delay(100);
}
```
See also **examples**.
# License
**MIT**
