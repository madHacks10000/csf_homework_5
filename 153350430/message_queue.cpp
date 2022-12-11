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

/*
 * Message Queue object constructor.
 */
MessageQueue::MessageQueue() {
  // Initialize the mutex and the semaphore
  sem_init(&m_avail, 0, 0);
  pthread_mutex_init(&m_lock, NULL);
}

/*
 * Message Queue object destructor.
 */
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

/*
 * Add a message to the queue until the client is ready to process it.
 */
void MessageQueue::enqueue(Message *msg) {
  // Put the specified message on the queue
  Guard g(m_lock);
  m_messages.push_back(msg);
  // Notify any thread waiting for a message to be available
  sem_post(&m_avail);
}

/*
 * Remove message from a user's queue.
 */
Message *MessageQueue::dequeue() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  ts.tv_sec += 1;

  // Wait up to 1 second for a message to be available, return nullptr if no message is available
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
