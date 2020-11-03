#include <asio.hpp>
#include <iostream>
#include "../include/sender.hpp"
#include <queue>


// #define NUM_MSGS 852 // this is defined in sender.hpp

using asio::ip::tcp;


int main() {
  asio::io_context io_context;
  Sender sender(io_context, "127.0.0.1", "3000");

  // An explanation of the API
  // data_ready(): returns true if a message is available, otherwise false
  // get_msg(): gets an available message
  // request_msg(id): requests a message at id [0, NUM_MSGS)

  // You will need to make significant modifications to the logic below
  // As a starting point, run the server as follows:
  // ./server --no-delay --no-packet-drops which makes the below code work

  // As an example, you could start by requesting the first 10 messages
  std::queue <int> q;
  int message_counter = 0;

  int32_t curr_msg = 0;
  for (int i = 0; i < 10; i++) {
    sender.request_msg(i);
    q.push(i);
    curr_msg++;
  }


  std::array<std::string, NUM_MSGS> message = {""};
  std::array<int, NUM_MSGS> message_w_ids = {-1};
  int queue_pop_counter = 0;
  int while_counter = 0;
  while (true) {
    std::cout << "While counter: " << while_counter << ", message_counter: " << message_counter << std::endl;
    if (sender.data_ready()) {
      // Get a response Msg:
      // A Msg has a msg_id (corresponds to id in request_msg) and
      // a char array of CHUNK_SIZE (128) storing the data
      auto msg = sender.get_msg();
      std::cout << "msg_id: " << msg.msg_id << std::endl; //")::" << data_str << std::endl;
      // Eventually, you will combine these chunks to write the file
      
      auto data_str = std::string(msg.data.data(), CHUNK_SIZE);
      if (message[msg.msg_id] == "")
        message[msg.msg_id] = data_str;
        message_counter++;
        
      message_w_ids[msg.msg_id] = msg.msg_id;
      
      // Print the msg id and message recieved (may be out of order)
      
    }
    while(!q.empty() && message[q.front()] != "" ) {
      q.pop();
    }
    if (!q.empty() &&  (message_counter > curr_msg / (message_counter + 1))){
      q.push(q.front());
      sender.request_msg(q.front());
      q.pop();
      queue_pop_counter++;
    }

    if(curr_msg < NUM_MSGS && q.size() < 10){
        for (int i = 0; i < q.size()*3 + 5; i++) {
          sender.request_msg(i);
          q.push(i);
          curr_msg++;
        }
      }

    // if(message_counter > curr_msg/(message_counter+1)){
    //   int curr_message_id = q.front();
    //   while(q.size() > curr_msg-message_counter){
    //     if (message[curr_message_id] == ""){

    //     }
    //     while (message[curr_message_id] != "") {
    //       q.pop();
    //       curr_message_id = q.front();
    //     }
    //     queue_pop_counter++;
    //     q.push(curr_message_id);
    //     sender.request_msg(curr_message_id);
    //   }
    // }
    // if (q.size() < 10) {
    //   for (int i = curr_msg; i < curr_msg + 10; i++) {
    //     sender.request_msg(i);
    //     q.push(i);
    //     curr_msg++;
    //   }
    // }

    // std::cout << "[ ";
    // for (int i = 0; i < curr_msg; ++i){
    //   if (message[i] != "")
    //     std::cout << i << ", ";
    //   else 
    //     std::cout << "EMPTY, ";
    // }
    // std::cout << " ]" << std::endl;

    if (message_counter == curr_msg)
      break;
    while_counter++;
  }

  // for (int i = 0; i < curr_msg; i++) {
  //   std::cout << message[i];
  // }
  // std::cout << std::endl;

  for (int i = 0; i < curr_msg; i++) {
    std::cout << message_w_ids[i];
  }
  std::cout << std::endl;

  std::cout << "queue pop counter is: " << queue_pop_counter << std::endl;
  

  return 0;
}
