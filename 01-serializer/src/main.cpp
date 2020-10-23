#include <chrono>
#include <iostream>
#include "../include/bakery.hpp"

using namespace std::chrono;

int main() {

  // Text Deserializer
  auto start = high_resolution_clock::now();
  auto bakery = text_deserializer("../data/large.txt");
  auto deser_time = high_resolution_clock::now() - start;
  std::cout << "Text deserializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;
  // print_bakery(bakery);


  // Text Serializer
  start = high_resolution_clock::now();
  text_serializer(bakery, "../data/text_serialized.txt");
  deser_time = high_resolution_clock::now() - start;
  std::cout << "Text serializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;
  // print_bakery(bakery);


  //Binary Serializer
  start = high_resolution_clock::now();
  binary_serializer(bakery, "../data/binary_serialized.bin");
  deser_time = high_resolution_clock::now() - start;
  // binary_serializer(bakery, "../data/binary_serialized.txt");
  std::cout << "Binary serializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;
  // print_bakery(bakery);
  
  
  //Binary Deserializer
  start = high_resolution_clock::now();
  bakery = binary_deserializer("../data/binary_serialized.bin");
  deser_time = high_resolution_clock::now() - start;
  std::cout << "Binary deserializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;
  // print_bakery(bakery);
  
  // text_serializer(bakery, "../data/text_serialized.txt");

  
  
  return 0;
}