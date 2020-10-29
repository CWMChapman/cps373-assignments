#include <inttypes.h>
#include <asio.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <map>

#include "bakery.hpp"

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 3000));

  // Use this bakery to handle queries from the client
  Bakery bakery = text_deserializer("../data/bakery.txt");
  
  std::map<std::string, std::string> employees;
  employees = {
        {"00","Brad"},
        {"01","Claudia"},
        {"10","Simone"},
        {"11","NULL"}
  };
  std::map<std::string, std::string> items;
  employees = {
        {"q1","Biscuit"},
        {"q2","Bun"},
        {"q3","Brownie"},
        {"q4","White Loaf"},
        {"q4","Wheat Loaf"}
  };

  uint16_t counter = 0;
  while (true) {
    // Wait for client
    std::cout << "Blocked for read" << std::endl;
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    std::array<uint8_t, 3> buf;
    asio::error_code error;
    size_t len = socket.read_some(asio::buffer(buf), error);

    // Example of error handling
    // if (error != asio::error::eof)
    //   throw asio::system_error(error);

    // Add x to counter


    std::array<int, 24> message = {0};
    // std::array<int, 24> message = {0};

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
    
    std::string message_type = std::to_string(message[0]) + std::to_string(message[1]);
    std::string employee_index = std::to_string(message[2]) + std::to_string(message[3]);
    std::string q1 = std::to_string(message[4]) + std::to_string(5) + std::to_string(6) + std::to_string(7);    
    std::string q2 = std::to_string(message[8]) + std::to_string(9) + std::to_string(11) + std::to_string(12);
    std::string q3 = std::to_string(message[12]) + std::to_string(13) + std::to_string(14) + std::to_string(15);
    std::string q4 = std::to_string(message[16]) + std::to_string(17) + std::to_string(18) + std::to_string(19);
    std::string q5 = std::to_string(message[20]) + std::to_string(21) + std::to_string(22) + std::to_string(23);    
    
    // 00: Total number of orders 
    if (message_type == "00") {
      int num_orders = bakery.orders.size();
      response = num_orders;
    }
    // 01: Total number of orders for employee
    else if (message_type == "01") {
      // std::string s = ;
      std::string employee = employees[employee_index];
      int num_orders = 0;
      for (int i = 0; i < bakery.orders.size(); ++i) {
        if (bakery.orders[i].employee == employee) {
          ++num_orders;
        }
      }
      response = num_orders;
    }
    // 10: Add an order using E, Q1, Q2, Q3, Q4, and Q5.
    else if (message_type == "10") {
      Order order;
      order.employee = employees[employee_index];
      if ;
      order.items.push_back(std::make_pair(,item[]));
    }
    else {
      // This option (11) is invaild.
     }

    // auto x = uint8_t(buf[0]);
    // std::cout << "counter: " << counter << std::endl;
    // std::cout << "x: " << x << std::endl;
    // counter += x;
    // std::cout << +x << " " << counter << std::endl;

    // buf.fill(0);

    std::memcpy(&response, &counter, sizeof(uint16_t));

    asio::write(socket, asio::buffer(buf), error);
  }

  return 0;
}