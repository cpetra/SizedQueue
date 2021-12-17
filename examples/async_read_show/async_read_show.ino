/******************************************************************************
 * @Date    : 2021-12-16 05:52:43
 * @Author  : Constantin Petra (constantin.petra@gmail.com)
 * @Link    : http://github.com/cpetra
 * @Version : 0.1
 * 
******************************************************************************/

#include <SizedQueue.h>
#include <thread>

/* Simple example for using SizedQueue:
 *  - in the main loop, push an item at each 100ms.
 *  - in the "show" thread, pop everything available each second, and print the result.
 */
 
static std::thread thread_show;

/* demo struct, can be anything
 *  
 */
typedef struct {
    int v1;
    int v2;
} _svals;

/* The queue, capable of holding 2x the expected fill rate
 *  
 */
SizedQueue<_svals, 20> m_queue;

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

void setup()
{
  Serial.begin(115200);
  thread_show = std::thread(show);
  randomSeed(analogRead(0));
}


int i = 0;

void loop()
{
  _svals v;
  v.v1 = i++;
  v.v2 = random(100);
  m_queue.push(v);
  delay(100);
}
