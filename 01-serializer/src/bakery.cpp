#include "bakery.hpp"
#include <fstream>
#include <iostream>
#include <bitset>
#include <map>
#include <string>

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
  
  short num_employees = 0;
  short num_items = 0;
  int num_orders = 0;
  infile.read(reinterpret_cast<char*>(&num_employees), sizeof(short));
  infile.read(reinterpret_cast<char*>(&num_items), sizeof(short));
  infile.read(reinterpret_cast<char*>(&num_orders), sizeof(int));

  // Employees section
  short employee_reference;
  short length;
  std::string employee;
  std::map<short, std::string> employee_dict;
  for (short i = 0; i < num_employees; ++i) {
    infile.read(reinterpret_cast<char*>(&employee_reference), sizeof(short));
    infile.read(reinterpret_cast<char*>(&length), sizeof(short));
    employee.resize(length);
    infile.read(reinterpret_cast<char*>(&employee[0]), sizeof(char)*length);
    employee_dict[employee_reference] = employee;
    bakery.employees.push_back(employee); // add the employee's name to the bakery object
  }

  // Items section
  short item_name_reference;
  short price_length;
  std::string item_name;
  std::string item_price;
  std::map<short, std::string> item_name_dict;
  for (short i = 0; i < num_items; ++i) {
    Item item;
    infile.read(reinterpret_cast<char*>(&item_name_reference), sizeof(short));
    infile.read(reinterpret_cast<char*>(&length), sizeof(short));
    item_name.resize(length);
    infile.read(reinterpret_cast<char*>(&item_name[0]), sizeof(char)*length);
    item_name_dict[item_name_reference] = item_name;
    item.name = item_name;
    infile.read(reinterpret_cast<char*>(&price_length), sizeof(short));
    item_price.resize(price_length);
    infile.read(reinterpret_cast<char*>(&item_price[0]), sizeof(char)*price_length);
    item.price = item_price;
    bakery.items.push_back(item);
  }

  // Orders section
  short order_length;
  short item_second; // how many of said item is in this order (quantity)
  short item_first_reference; 
  std::string item_first; // what is the name of the item (name)
  for (int i = 0; i < num_orders; ++i) {
    Order order;
    infile.read(reinterpret_cast<char*>(&employee_reference), sizeof(short));
    order.employee = employee_dict[employee_reference];
    infile.read(reinterpret_cast<char*>(&order_length), sizeof(short));

    for (short i = 0; i < order_length; ++i) {
      infile.read(reinterpret_cast<char*>(&item_second), sizeof(short));
      infile.read(reinterpret_cast<char*>(&item_first_reference), sizeof(short));
      item_first = item_name_dict[item_first_reference];
      order.items.push_back(std::make_pair(item_first, std::to_string(item_second)));
    }
    bakery.orders.push_back(order);
  }
  infile.close(); 
  return bakery;
}



void binary_serializer(const Bakery& bakery, std::string file_path) {
  std::ofstream outfile;
  outfile.open(file_path, std::ios::out | std::ios::binary);
  short num_employees = 0;
  short num_items = 0;
  int num_orders = 0;
  outfile.write(reinterpret_cast<char*>(&num_employees), sizeof(short));
  outfile.write(reinterpret_cast<char*>(&num_items), sizeof(short));
  outfile.write(reinterpret_cast<char*>(&num_orders), sizeof(int));
  std::map<std::string, short> employee_dict;
  
  int count = 0;
  short employee_reference = 0;
  for (auto employee : bakery.employees) {
    employee_dict[employee] = employee_reference;
    short length = employee.length();
    outfile.write(reinterpret_cast<char*>(&employee_reference), sizeof(short)); // first 2 bytes are the employee reference
    outfile.write(reinterpret_cast<char*>(&length), sizeof(short)); // next 2 bytes is the length of the employees name 
    outfile << employee;
    ++employee_reference; //increment the reference for the next employee
    ++count;
  }
  num_employees = count;

  count = 0;
  short length;
  short price_length;
  std::map<std::string, short> item_name_dict;
  short item_name_reference = 0;
  for (auto item : bakery.items) {
    item_name_dict[item.name] = item_name_reference;
    length = item.name.length();
    outfile.write(reinterpret_cast<char*>(&item_name_reference), sizeof(short)); // first 2 bytes are the items name reference
    outfile.write(reinterpret_cast<char*>(&length), sizeof(short)); // next 2 bytes is the length of the item's name 
    outfile << item.name;
    price_length = item.price.length();
    outfile.write(reinterpret_cast<char*>(&price_length),sizeof(short));
    outfile << item.price;
    ++item_name_reference; //increment the reference for the next item
    ++count;
  }
  num_items = count;
  
  count = 0;
  short order_length;
  for (auto order : bakery.orders) {
    outfile.write(reinterpret_cast<char*>(&employee_dict[order.employee]), sizeof(short)); // write the employee reference
    order_length = order.items.size();
    outfile.write(reinterpret_cast<char*>(&order_length), sizeof(short));

    for (auto item : order.items) {
      short item_second = std::stoi(item.second); // this will always be in the range of a short, so im using stoi, because there is no stos
      outfile.write(reinterpret_cast<char*>(&item_second), sizeof(short));
      item_name_reference = item_name_dict[item.first];
      outfile.write(reinterpret_cast<char*>(&item_name_reference),sizeof(short));
    }
    ++count;
  }
  num_orders = count;

  outfile.seekp(0, std::ios::beg);
  outfile.write(reinterpret_cast<char*>(&num_employees), sizeof(short));
  outfile.write(reinterpret_cast<char*>(&num_items), sizeof(short));
  outfile.write(reinterpret_cast<char*>(&num_orders), sizeof(int));

  outfile.close();  

}
