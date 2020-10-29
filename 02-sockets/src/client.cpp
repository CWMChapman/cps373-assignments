#include <asio.hpp>
#include <iostream>
#include <map>

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  tcp::resolver resolver(io_context);
  tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");

  tcp::socket socket(io_context);
  asio::connect(socket, endpoints);

  asio::error_code error;

/*
TASKS:
• Get the number of orders for E=01 (Claudia)
[01 01 0000 0000 0000 0000 0000]

• Add an order: E=01, Q1=2, Q2=5, Q3=0, Q4=1, Q5=0
[10 01 0010 0101 0000 0001 0000]

• Get the number of orders for E=01 (should have increased by one!) 
[01 01 0000 0000 0000 0000 0000]

• Get the total number of orders
[00 00 0000 0000 0000 0000 0000]


Buf = [0 0 0 0  0 0 0 0] * 3

// buf[1] |= 1 << 7;
[ 0    0    0    0      0    0    0    0 ]
[ 0    1    2    3      4    5    6    7 ]
[ 1    2    4    8      16   32   64  128]

240
[ 0    0    0    0      1    1    1    1 ]


*/
// // FOR TASK 1: Get the number of orders for E=01 (Claudia)
// std::map<std::string, std::string> message;
// message["message_type"] = "01";  // 2 bits
// message["employee"] = "01";      // 2 bits
// message["q1"] = "0000";          // 4 bits
// message["q2"] = "0000";          // 4 bits
// message["q3"] = "0000";          // 4 bits
// message["q4"] = "0000";          // 4 bits
// message["q5"] = "0000";          // 4 bits

// std::string full_message = "010100000000000000000000"; 
std::array<int, 24> message = {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// "01010000 00000000 00000000"

  std::array<uint8_t, 3> buf;
  buf.fill(0);

  int buf_index = 0;
  int bit_index = 0;
  for (int i = 0; i < message.size(); ++i) {
    if((i+1)%8 == 0){
      ++buf_index;
    }
    // std::cout << "char: " << message_int[i] << ", bit_index: " << bit_index << std::endl;
    buf[buf_index] |= message[i] << (7-bit_index);


    if((i+1)%8 == 0){
      bit_index = 0;
    }
    else{
      ++bit_index;
    }
  }

  asio::write(socket, asio::buffer(buf), error);

  size_t len = socket.read_some(asio::buffer(buf), error);
  uint16_t response = *reinterpret_cast<uint16_t*>(&buf.data()[0]);
  std::cout << response << std::endl;

  return 0;
}
