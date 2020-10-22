#include "bakery.hpp"
#include <fstream>
#include <iostream>
#include <bitset>
#include <map>

void print_bakery(const Bakery& bakery) {
  std::cout << "Employees: " << std::endl;
  for (auto employee : bakery.employees) {
    std::cout << employee << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Items: " << std::endl;
  for (auto item : bakery.items) {
    std::cout << item.name << ", " << item.price << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Orders: " << std::endl;
  for (auto order : bakery.orders) {
    std::cout << order.employee << ": ";
    auto j = 0;
    for (auto item : order.items) {
      std::cout << item.second << " " << item.first;
      j++;
      if (size_t(j) < order.items.size())
        std::cout << ", ";
    }
    std::cout << std::endl;
  }
}

// You shouldn't need to edit this function (unless you want!)
Bakery text_deserializer(std::string file_path) {
  std::ifstream infile(file_path);
  std::string line;
  Bakery bakery;

  while (!infile.eof()) {
    // Employees section
    if (line.compare("@employees") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        bakery.employees.push_back(line);
        std::getline(infile, line);
      }
    }

    // Items section
    if (line.compare("@items") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        auto end = line.find(", ");
        Item item;
        item.name = line.substr(0, end);
        item.price = line.substr(end + 2);
        bakery.items.push_back(item);
        std::getline(infile, line);
      }
    }

    // Orders section
    if (line.compare("@orders") == 0) {
      std::getline(infile, line);
      auto e = bakery.employees;
      while (line.size() > 0) {
        Order order;
        auto end = line.find(": ");
        order.employee = line.substr(0, end);

        // Find all the orders
        auto rest = line.substr(end + 2);
        size_t pos = 0;
        std::string token;
        while ((pos = rest.find(", ")) != std::string::npos) {
          token = rest.substr(0, pos);
          end = token.find(" ");
          auto quantity = token.substr(0, end);
          auto item_name = token.substr(end + 1);
          order.items.push_back(std::make_pair(item_name, quantity));
          rest.erase(0, pos + 2);
        }
        end = rest.find(" ");
        auto quantity = rest.substr(0, end);
        auto item_name = rest.substr(end + 1);
        order.items.push_back(std::make_pair(item_name, quantity));
        bakery.orders.push_back(order);

        // no more lines to read
        if (infile.eof())
          break;

        std::getline(infile, line);
      }
    }

    std::getline(infile, line);
  }

  return bakery;
}

// Implement these 3 functions!
// Hint: use print_bakery to help think about the text serializer
void text_serializer(const Bakery& bakery, std::string file_path) {
  std::ofstream outfile (file_path);
  outfile << "@employees " << std::endl;
  for (auto employee : bakery.employees) {
    outfile << employee << std::endl;
  }

  outfile << std::endl;
  outfile << "@items " << std::endl;
  for (auto item : bakery.items) {
    outfile << item.name << ", " << item.price << std::endl;
  }

  outfile << std::endl;
  outfile << "@orders " << std::endl;
  for (auto order : bakery.orders) {
    outfile << order.employee << ": ";
    auto j = 0;
    for (auto item : order.items) {
      outfile << item.second << " " << item.first;
      j++;
      if (size_t(j) < order.items.size())
        outfile << ", ";
    }
    outfile << std::endl;
  }

  outfile.close();  
}



Bakery binary_deserializer(std::string file_path) {
  std::ifstream infile;
  std::string line;
  Bakery bakery;

  infile.open(file_path, std::ios::binary | std::ios::in);
  char out;
  infile.read(&out, sizeof(char));
  std::cout << "out: " << out << std::endl;
  
  infile.close(); 

/*
  while (!infile.eof()) {
    // Employees section
    if (line.compare("@employees") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        std::string binaryLine = "";
        for (int i = 0; i < line.size(); ++i) {
          binaryLine += std::bitset<8>(line[i]).to_string();
        }
        line = binaryLine;
        bakery.employees.push_back(line);
        std::getline(infile, line);
      }
    }

    // Items section
    if (line.compare("@items") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        auto end = line.find(", ");
        Item item;
        item.name = line.substr(0, end);
        std::string binaryItemName = "";
        for (int i = 0; i < item.name.size(); ++i) {
          binaryItemName += std::bitset<8>(item.name[i]).to_string();
        }
        item.name = binaryItemName;
        
        item.price = line.substr(end + 2);
        std::string binaryItemPrice = "";
        for (int i = 0; i < item.price.size(); ++i) {
          binaryItemName += std::bitset<8>(item.price[i]).to_string();
        }
        item.price = binaryItemPrice;
        bakery.items.push_back(item);
        std::getline(infile, line);
      }
    }

    // Orders section
    if (line.compare("@orders") == 0) {
      std::getline(infile, line);
      auto e = bakery.employees;
      while (line.size() > 0) {
        Order order;
        auto end = line.find(": ");
        order.employee = line.substr(0, end);

        // Find all the orders
        auto rest = line.substr(end + 2);
        size_t pos = 0;
        std::string token;
        while ((pos = rest.find(", ")) != std::string::npos) {
          token = rest.substr(0, pos);
          end = token.find(" ");
          auto quantity = token.substr(0, end);
          std::string binaryQuantity = "";
          for (int i = 0; i < quantity.size(); ++i) {
            binaryQuantity += std::bitset<8>(quantity[i]).to_string();
          }
          quantity = binaryQuantity;

          auto item_name = token.substr(end + 1);
          std::string binaryItemName = "";
          for (int i = 0; i < item_name.size(); ++i) {
            binaryItemName += std::bitset<8>(item_name[i]).to_string();
          }
          item_name = binaryItemName;
          order.items.push_back(std::make_pair(item_name, quantity));
          rest.erase(0, pos + 2);
        }
        end = rest.find(" ");
        auto quantity = rest.substr(0, end);
          std::string binaryQuantity = "";
          for (int i = 0; i < quantity.size(); ++i) {
            binaryQuantity += std::bitset<8>(quantity[i]).to_string();
          }
          quantity = binaryQuantity;

          auto item_name = rest.substr(end + 1);
          std::string binaryItemName = "";
          for (int i = 0; i < item_name.size(); ++i) {
            binaryItemName += std::bitset<8>(item_name[i]).to_string();
          }
          item_name = binaryItemName;
        order.items.push_back(std::make_pair(item_name, quantity));
        bakery.orders.push_back(order);

        // no more lines to read
        if (infile.eof())
          break;

        std::getline(infile, line);
      }
    }

    std::getline(infile, line);
  }
  */

  return bakery;
}



void binary_serializer(const Bakery& bakery, std::string file_path) {
  std::ofstream outfile;
  outfile.open(file_path, std::ios::out | std::ios::binary);

  std::map<std::string, short> employee_dict;
  short employee_reference = 0;
  for (auto employee : bakery.employees) {
    employee_dict[employee] = employee_reference;
    short length = employee.length();
    outfile.write(reinterpret_cast<char*>(&employee_reference), sizeof(short)); // first 2 bytes are the employee reference
    outfile.write(reinterpret_cast<char*>(&length), sizeof(short)); // next 2 bytes is the length of the employees name 
    outfile << employee;
    ++employee_reference; //increment the reference for the next employee
  }

  std::map<std::string, short> item_name_dict;
  short item_name_reference = 0;
  for (auto item : bakery.items) {
    item_name_dict[item.name] = item_name_reference;
    short length = item.name.length();
    outfile.write(reinterpret_cast<char*>(&item_name_reference), sizeof(short)); // first 2 bytes are the items name reference
    outfile.write(reinterpret_cast<char*>(&length), sizeof(short)); // next 2 bytes is the length of the item's name 
    // outfile.write(std::bitset<8>(item_name_reference).to_string().c_str(), sizeof(std::bitset<8>(item_name_reference).to_string().c_str())); // first 2 bytes are the items name reference
    // outfile.write(std::bitset<8>(item.name.length()).to_string().c_str(), sizeof(std::bitset<8>(item.name.length()).to_string().c_str())); // next 2 bytes is the length of the item's name 
    outfile << item.name;
    // for (int i = 0; i < item.name.size(); ++i) {
    //   outfile.write(std::bitset<8>(item.name[i]).to_string().c_str(), sizeof(std::bitset<8>(item.name[i]).to_string().c_str()));
    // }
    float price = std::stof(item.price);
    outfile.write(reinterpret_cast<char*>(&price),sizeof(float)); // four bytes
    // outfile.write(std::bitset<32>(std::stof(item.price)).to_string().c_str(), sizeof(std::bitset<32>(std::stof(item.price)).to_string().c_str()));// 4 bytes
    ++item_name_reference; //increment the reference for the next item
  }

  for (auto order : bakery.orders) {
    // outfile.write(std::bitset<8>(employee_dict[order.employee]).to_string().c_str(), sizeof(std::bitset<8>(employee_dict[order.employee]).to_string().c_str()));
    outfile.write(reinterpret_cast<char*>(&employee_dict[order.employee]), sizeof(short));

    // auto j = 0;
    for (auto item : order.items) {
      outfile.write(reinterpret_cast<char*>(&item.second),sizeof(char));
      outfile.write(reinterpret_cast<char*>(&item.first),sizeof(char));
      // outfile.write(std::bitset<8>(item.second[0]).to_string().c_str(), sizeof(std::bitset<8>(item.second[0]).to_string().c_str())); //number of items -- we can index to 0 because its just a string of length 1, always will be between 1 and 10 
      // outfile.write(std::bitset<8>(item_name_dict[item.first]).to_string().c_str(), sizeof(std::bitset<8>(item_name_dict[item.first]).to_string().c_str())); //name of the item
      // j++;
    }
  }

  outfile.close();  

}
