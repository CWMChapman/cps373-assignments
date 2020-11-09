#include <asio.hpp>
#include <iostream>
#include <fstream>
#include "../include/sender.hpp"
#include <queue>
#include <chrono>

namespace sc = std::chrono;
using asio::ip::tcp;


int main() {
  asio::io_context io_context;
  Sender sender(io_context, "127.0.0.1", "3000");

  std::queue <int> q;
  std::queue <sc::milliseconds> timeout;
  
  int message_counter = 0;
  int32_t curr_msg = 0;
  int rerequest_counter = 0;
  int while_counter = 0;
  
  std::array<std::string, NUM_MSGS> message;

  auto start = sc::high_resolution_clock::now();
  while (true) {
    // if (curr_msg < NUM_MSGS) {
    //   sender.request_msg(curr_msg);
    //   auto hb = sc::duration_cast<sc::milliseconds>(sc::high_resolution_clock::now().time_since_epoch());
    //   hb += sc::milliseconds(500);
    //   timeout.push(hb);
    //   q.push(curr_msg);
    //   curr_msg++;
    // }
    if (q.size() < 10 && curr_msg < NUM_MSGS){ 
      int c = curr_msg;
      if (c + 20 <= NUM_MSGS) {
        for (int i = c; i < c + 20; i++) {
          sender.request_msg(i);
          auto hb = sc::duration_cast<sc::milliseconds>(sc::high_resolution_clock::now().time_since_epoch());
          hb += sc::milliseconds(500);   
          timeout.push(hb);
          q.push(i);
          curr_msg++;
        }
      }
      else {
        for (int i = c; i < NUM_MSGS; i++) {
          sender.request_msg(i);
          auto hb = sc::duration_cast<sc::milliseconds>(sc::high_resolution_clock::now().time_since_epoch());
          hb += sc::milliseconds(500);   
          timeout.push(hb);
          q.push(i);
          curr_msg++;
        }
      }
    }

    std::cout << "While counter: " << while_counter << ", # of packets re-requested: " << rerequest_counter << ", message_counter: " << message_counter << ", curr_msg: " << curr_msg << ", size of queue: " << q.size() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    while (sender.data_ready()) {
      auto msg = sender.get_msg();
      auto data_str = std::string(msg.data.data(), CHUNK_SIZE);

      if(message[msg.msg_id].empty()) {
        message[msg.msg_id] = data_str;
        message_counter++;
      }
    }
    
    while(!q.empty() && !message[q.front()].empty()) {
      timeout.pop();
      q.pop();
    }
    if (!q.empty() && timeout.front() < sc::duration_cast<sc::milliseconds>(
        sc::high_resolution_clock::now().time_since_epoch())){

      auto hb = sc::duration_cast<sc::milliseconds>(sc::high_resolution_clock::now().time_since_epoch());
      hb += sc::milliseconds(500);   
      
      sender.request_msg(q.front());
      timeout.pop();
      timeout.push(hb);
      q.push(q.front());
      q.pop();
      rerequest_counter++;
    }

    while_counter++;

    if (NUM_MSGS == curr_msg && NUM_MSGS == message_counter)
      break;

  }
  auto deser_time = sc::high_resolution_clock::now() - start;

  std::cout << "# of packets re-requested is: " << rerequest_counter << std::endl;

  std::ofstream outfile ("../data/poem.txt");
  std::cout << std::endl;
  for (int i = 0; i < curr_msg; i++) {
    outfile << message[i];
  }
  outfile << std::endl;
  outfile.close();

  std::cout << "All packets have been recieved, and poem is in the data dir." << std::endl;
  std::cout << "Took: " << sc::duration_cast<sc::seconds>(deser_time).count() << "s" << std::endl;

  

  return 0;
}