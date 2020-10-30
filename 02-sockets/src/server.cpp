#include <inttypes.h>
#include <asio.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <map>
#include <bitset>

#include "bakery.hpp"

using asio::ip::tcp;


std::string getBits( std::array<int,24>* message, int firstBit, int numBits ) {
  // first bit must be using zero indexing
  std::string bits;
  for (int i = 0; i < numBits; ++i) {
      bits += std::to_string((*message)[firstBit + i]);
  }

  return bits;
}

int main() {
  asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 3000));

  // Use this bakery to handle queries from the client
  Bakery bakery = text_deserializer("../data/bakery.txt");

  uint16_t counter = 0;
  while (true) {
    // Wait for client
    std::cout << "Blocked for read" << std::endl;
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    std::array<uint8_t, 3> buf;
    asio::error_code error;
    size_t len = socket.read_some(asio::buffer(buf), error);


    std::array<int, 24> message = {0};

    int buf_index = 0;
    int bit_index = 0;
    for (int i = 0; i < message.size(); ++i){
      if((i+1)%8 == 0){
        ++buf_index;
      }
      message[i] = int((buf[buf_index] >> (7- bit_index)) & 1);
      // std::cout << message[i];
      if((i+1)%8 == 0){
        bit_index = 0;
      }
      else{
        ++bit_index;
      }
    }

    uint16_t response;
    
    std::string message_type = getBits(&message, 0, 2); 

    // Message Type 00: Total number of orders 
    if (message_type == "00") {
      int num_orders = bakery.orders.size();
      response = num_orders;
    }
    // Message Type 01: Total number of orders for employee
    else if (message_type == "01") {
      std::string employee_index = getBits(&message, 2, 2);
      std::string employee;
      if (employee_index == "00")
        employee = "Brad";
      else if (employee_index == "01")
        employee = "Claudia";
      else if (employee_index == "10")
        employee = "Simone";
      else 
        employee = "NULL";
      
      int num_orders = 0;
      for (int i = 0; i < bakery.orders.size(); ++i) {
        if (bakery.orders[i].employee == employee) {
          ++num_orders;
        }
      }
      response = num_orders;
    }
    // // Message Type 10: Add an order using E, Q1, Q2, Q3, Q4, and Q5.
    else if (message_type == "10") {
      std::string employee_index = getBits(&message, 2, 2);
      std::string q [5] = {getBits(&message, 4, 4), getBits(&message, 8, 4), getBits(&message, 12, 4), getBits(&message, 16, 4), getBits(&message, 20, 4)};
      Order order;
      if (employee_index == "00")
        order.employee = "Brad";
      else if (employee_index == "01")
        order.employee = "Claudia";
      else if (employee_index == "10")
        order.employee = "Simone";
      else 
        order.employee = "NULL";
      
      std::string item;
      for (int i = 0; i < sizeof(q)/sizeof(q[0]); ++i) { 
      
        if (q[i] != "0000") {
          if (i == 0)
            item = "Biscuit";
          else if (i == 1)
            item = "Bun";
          else if (i == 2)
            item = "Brownie";
          else if (i == 3)
            item = "White Loaf";
          else if (i == 4)
            item = "Wheat Loaf";
          std::string bin(q[i]);
          order.items.push_back(std::make_pair(bin, item));
        }
        else {
          continue;
        }
      }
      bakery.orders.push_back(order);
      response = 0; // not necessary, but it makes the code more readable
    }
    else {
      // This option (11) is invaild.
     }

    std::cout << "Response: " << response << std::endl;
    std::memcpy(&buf, &response, sizeof(uint16_t));

    asio::write(socket, asio::buffer(buf), error);
  }

  return 0;
}