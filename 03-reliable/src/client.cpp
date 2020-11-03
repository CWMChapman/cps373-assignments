#include <asio.hpp>
#include <iostream>
#include <fstream>
#include "../include/sender.hpp"
#include <queue>


// #define NUM_MSGS 852 // this is defined in sender.hpp

using asio::ip::tcp;


int main() {
  asio::io_context io_context;
  Sender sender(io_context, "127.0.0.1", "3000");

  std::queue <int> q;
  int message_counter = 0;

  int32_t curr_msg = 0;

  std::array<std::string, NUM_MSGS> message = {""};
  int queue_pop_counter = 0;
  int while_counter = 0;
  while (true) {
    if (q.size() < 10 && curr_msg < NUM_MSGS){ 
      int c = curr_msg;
      if (c + 20 <= NUM_MSGS) {
        for (int i = c; i < c + 20; i++) {
          sender.request_msg(i);
          q.push(i);
          curr_msg++;
        }
      }
      else {
        for (int i = c; i < NUM_MSGS; i++) {
          sender.request_msg(i);
          q.push(i);
          curr_msg++;
        }
      }
    }

    std::cout << "While counter: " << while_counter << ", queue_pop_counter: " << queue_pop_counter << ", message_counter: " << message_counter << ", curr_msg: " << curr_msg << ", size of queue: " << q.size() << std::endl;

    if (sender.data_ready()) {
      auto msg = sender.get_msg();
      auto data_str = std::string(msg.data.data(), CHUNK_SIZE);

      if(message[msg.msg_id].empty()) {
        message[msg.msg_id] = data_str;
        message_counter++;
      }
    }
    
    else {
      while(!q.empty() && !message[q.front()].empty() ) {
        q.pop();
      }
      // std::cout << "curr_msg: " << curr_msg << ", message_counter: " << message_counter << ", curr_msg / (message_counter + 1): " << curr_msg / (message_counter + 1) << std::endl;
      if (!q.empty()){
        q.push(q.front());
        sender.request_msg(q.front());
        q.pop();
        queue_pop_counter++;
      }
    }

    if (NUM_MSGS == curr_msg && NUM_MSGS == message_counter)
      break;
    while_counter++;
  }

  std::cout << "queue pop counter is: " << queue_pop_counter << std::endl;

  std::ofstream outfile ("../data/poem.txt");
  std::cout << std::endl;
  for (int i = 0; i < curr_msg; i++) {
    outfile << message[i];
  }
  outfile << std::endl;
  outfile.close();

  

  return 0;
}