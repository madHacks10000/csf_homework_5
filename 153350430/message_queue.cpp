/*
 * File for implementation of the message queue
 * CSF Assignment 5
 * Madeline Estey (mestey1@jhu.edu)
 * Owen Reed (oreed2@jhu.edu)
 */

#include <cassert>
#include <ctime>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include "message_queue.h"
#include "guard.h"

<<<<<<< HEAD
// lock ensures that the message queue can only be modified by one thread at a time, 
// and the semaphore is used to “notify” the other end that a new message is available. 

// no messages available, we want the receiver to sleep until there are available messages, 
// and each time a message is sent, it reduces the available messages by one

// don't directly lock mutexes, use Guard methods


/*
Message Queue Constructor.
*/
=======
/*
 * Message Queue object constructor.
 */
>>>>>>> 2cabb8ad9f71b4faeaaeb3f459ffc9436f2a5260
MessageQueue::MessageQueue() {
  // Initialize the mutex and the semaphore
  sem_init(&m_avail, 0, 0);
  pthread_mutex_init(&m_lock, NULL);
}

<<<<<<< HEAD

/*
Message queue destructor.
*/
=======
/*
 * Message Queue object destructor.
 */
>>>>>>> 2cabb8ad9f71b4faeaaeb3f459ffc9436f2a5260
MessageQueue::~MessageQueue() {
  // destroy the mutex and the semaphore
  pthread_mutex_destroy(&m_lock);
  sem_destroy(&m_avail);
  //empty the message queue
  Message *next_message;
  while((next_message = dequeue())!= nullptr) {
    next_message = NULL;
  }
}

<<<<<<< HEAD

/*
Handels an enqueue to the message queue. Locks before touching the data structure.
*/
=======
/*
 * Add a message to the queue until the client is ready to process it.
 */
>>>>>>> 2cabb8ad9f71b4faeaaeb3f459ffc9436f2a5260
void MessageQueue::enqueue(Message *msg) {
  // Put the specified message on the queue
  Guard g(m_lock);
  m_messages.push_back(msg);
<<<<<<< HEAD
  // be sure to notify any thread waiting for a message to be
  // available by calling sem_post
=======
  // Notify any thread waiting for a message to be available
>>>>>>> 2cabb8ad9f71b4faeaaeb3f459ffc9436f2a5260
  sem_post(&m_avail);
}

/*
<<<<<<< HEAD
Handels a dequeue to the message queue. Locks before touching the data structure.
*/
=======
 * Remove message from a user's queue.
 */
>>>>>>> 2cabb8ad9f71b4faeaaeb3f459ffc9436f2a5260
Message *MessageQueue::dequeue() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  ts.tv_sec += 1;

<<<<<<< HEAD
  //call sem_timedwait to wait up to 1 second for a message
  //to be available, return nullptr if no message is available
=======
  // Wait up to 1 second for a message to be available, return nullptr if no message is available
>>>>>>> 2cabb8ad9f71b4faeaaeb3f459ffc9436f2a5260
  if(sem_timedwait(&m_avail, &ts) == 0) {
    Guard g(m_lock);
    // Remove the next message from the queue, return it
    Message *msg = m_messages.front();
    m_messages.pop_front();
    return msg;
  } else {
    return nullptr;
  }
}
