/*
 * File for Room objects and their methods.
 * CSF Assignment 5
 * Madeline Estey (mestey1@jhu.edu)
 * Owen Reed (oreed2@jhu.edu)
 */

#include <iostream>
#include "guard.h"
#include "message.h"
#include "message_queue.h"
#include "user.h"
#include "room.h"

/*
 * Room object constructor.
 */
Room::Room(const std::string &room_name)
  : room_name(room_name) {
  // Initialize the mutex
  pthread_mutex_init(&lock, NULL);
}

/*
 * Room object destructor.
 */
Room::~Room() {
  // Destroy the mutex
  pthread_mutex_destroy(&lock);
}

/*
 * Add user to the room.
 */
void Room::add_member(User *user) {
  if (members.count(user) <= 0) {
    Guard g(lock); // Protect access while adding user
    this->members.insert(user);
  }
}

/*
 * Remove user from room.
 */
void Room::remove_member(User *user) {
  if (members.count(user) > 0) {
    Guard g(lock); // Protect access while adding user
    members.erase(members.find(user));
    // Pthread_mutex_unlock(&lock);
  }
}

/*
 * Send message to every (receiver) user in the room.
 */
void Room::broadcast_message(const std::string &sender_username, const std::string &message_text) {
  std::set<User *>::iterator it;
  Message msg;
  msg.data = strip_text(get_room_name());
  msg.data += ":";
  msg.data += strip_text(sender_username);
  msg.data += ":";
  msg.data += strip_text(message_text);
  msg.tag = "delivery";
  for (it = members.begin(); it != members.end(); ++it) {
    // Create new message
    if (!((*it)->is_sender)) {
      (*it)->mqueue.enqueue(new Message(msg.tag,msg.data));
    }
  }
  
}

/*
 * Remove newline characters from text input.
 */
std::string Room::strip_text(std::string input) {
  size_t pos = (input).find("\n");
  if (pos != std::string::npos) {
    input.erase(pos,input.length());
  }
  pos = (input).find("\r");
  if (pos != std::string::npos) {
    input.erase(pos,input.length());
  }
  return input;
}
