#include "bakery.hpp"
#include <fstream>
#include <iostream>
#include <bitset>

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
  outfile << "Employees: " << std::endl;
  for (auto employee : bakery.employees) {
    outfile << employee << std::endl;
  }

  outfile << std::endl;
  outfile << "Items: " << std::endl;
  for (auto item : bakery.items) {
    outfile << item.name << ", " << item.price << std::endl;
  }

  outfile << std::endl;
  outfile << "Orders: " << std::endl;
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
  std::ifstream infile(file_path);
  std::string line;
  Bakery bakery;

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

  return bakery;
}



void binary_serializer(const Bakery& bakery, std::string file_path) {
  std::ofstream outfile;
  outfile.open(file_path, std::ios::out | std::ios::binary);

  for (auto employee : bakery.employees) {
    std::string out = "";
    for (int i = 0; i < employee.size(); ++i) {
      outfile << std::bitset<8>(employee[i]);
    }
  }

  for (auto item : bakery.items) {
    for (int i = 0; i < item.name.size(); ++i) {
      outfile <<  std::bitset<8>(item.name[i]);
    }
    for (int i = 0; i < item.price.size(); ++i) {
      outfile << std::bitset<8>(item.price[i]);
    }
  }

  for (auto order : bakery.orders) {
    for (int i = 0; i < order.employee.size(); ++i) {
      outfile << std::bitset<8>(order.employee[i]);
    }
    auto j = 0;
    for (auto item : order.items) {
      for (int i = 0; i < item.first.size(); ++i) {
        outfile << std::bitset<8>(item.first[i]);
      }
      for (int i = 0; i < item.second.size(); ++i) {
        outfile << std::bitset<8>(item.second[i]);
      }
      j++;
    }
  }

  outfile.close();  

}
