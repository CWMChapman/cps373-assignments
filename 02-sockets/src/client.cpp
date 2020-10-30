#include <asio.hpp>
#include <iostream>
#include <map>

using asio::ip::tcp;

int main() {

    asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");
    tcp::socket socket(io_context);

  std::array<int, 24> message1 = {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Get the number of orders for E=01 (Claudia)
  std::string explanation1 = "Getting the number of orders for E=01 (Claudia):";
  std::array<int, 24> message2 = {1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0}; // Add an order: E=01, Q1=2, Q2=5, Q3=0, Q4=1, Q5=0
  std::string explanation2 = "Adding an order for E=01 (Claudia) Q1=2, Q2=5, Q3=0, Q4=1, Q5=0:";
  std::array<int, 24> message3 = {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Get the number of orders for E=01 (should have increased by one!)
  std::string explanation3 = "Getting the number of orders for E=01 (Claudia):";
  std::array<int, 24> message4 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Get the total number of orders
  std::string explanation4 = "Getting the total number of orders:";
  std::array<int, 24> messages [4] = { message1, message2, message3, message4 };
  std::string explanation [4] = {explanation1, explanation2, explanation3, explanation4 };

  for (int i = 0; i < 4; ++i) { 
    std::cout << explanation[i] << std::endl;
    std::array<int, 24> message = messages[i];

    asio::connect(socket, endpoints);

    asio::error_code error;
    

    std::array<uint8_t, 3> buf;
    buf.fill(0);

    int buf_index = 0;
    int bit_index = 0;
    for (int i = 0; i < message.size(); ++i) {
      if((i+1)%8 == 0){
        ++buf_index;
      }
      
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
    std::cout << "Response: " << response << std::endl;
}

  return 0;
}


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

*/