#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include <iostream>
namespace bp = boost::property_tree;

void CreateJson1() {
  /*
   * students: [
   *    {
   *      "name": "George",
   *      "age" : 21
   *    },
   *    {
   *      "name": "John",
   *      "age" : 22
   *    },
   *    {
   *      "name": "Tom",
   *      "age" : 23
   *    }
   * ]
   */
  bp::ptree ch1;
  ch1.put("name", "George");
  ch1.put("age",  21);
  bp::ptree ch2;
  ch2.put("name", "John");
  ch2.put("age",  22);
  bp::ptree ch3;
  ch3.put("name", "Tom");
  ch3.put("age",  23);
  bp::ptree list;
  list.push_back(std::make_pair("", ch1));
  list.push_back(std::make_pair("", ch2));
  list.push_back(std::make_pair("", ch3));

  bp::ptree contracts_tree;
  contracts_tree.add_child("students",list);
}

bp::ptree MakeConfig() {
//  {
//      "system1": {
//        "name1": "value1",
//        "name2": "value2",
//        "name3": "value3",
//        "name4": "value4"
//      },
//      "system2": {
//        "name1": "value1",
//        "name2": "value2",
//        "name3": true,
//        "name4": 11,
//        "name5": 31
//      },
//      "system3": {
//          "sub1": {
//            "grand_sub": {
//                "host": "localhost",
//                "port": "8000"
//              }
//          },
//          "sub2": {
//            "grand_sub": {
//                "host": "localhost",
//                "port": "8001"
//              }
//          }
//      },
//      "system4": [
//        {
//          "name": "john",
//          "age":  1
//        },
//        {
//          "name": "jerry",
//          "age":  2
//        }
//      ],
//      "system5": [
//          "Sun",
//          "Earth",
//          "Moon"
//      ]
//  }

  bp::ptree config_tree;

  // system1
  auto& system1_tree = config_tree.add_child("system1", bp::ptree());
  system1_tree.put("name1", "value1");
  system1_tree.put("name2", "value2");
  system1_tree.put("name3", "value3");
  system1_tree.put("name4", "value4");

  // system2
  auto& system2_tree = config_tree.add_child("system2", bp::ptree());
  system2_tree.put("name1", "value1");
  system2_tree.put("name2", "value2");
  system2_tree.put("name3", true);
  system2_tree.put("name4", 11);
  system2_tree.put("name5", 31);

  // system3
  auto& system3_tree = config_tree.add_child("system3", bp::ptree());
  auto& sub1g_tree = system3_tree.add_child("sub1", bp::ptree()).add_child("grand_sub", bp::ptree());
  sub1g_tree.put("host",  "localhost");
  sub1g_tree.put("port",  8000);
  auto& sub2g_tree = system3_tree.add_child("sub2",  bp::ptree()).add_child("grand_sub", bp::ptree());
  sub2g_tree.put("host",  "localhost");
  sub2g_tree.put("port",  8001);

  // system4
  auto& system4_tree = config_tree.add_child("system4", bp::ptree());
  auto p1 = system4_tree.push_back(std::make_pair("", bp::ptree()));
  p1->second.put("name", "john");
  p1->second.put("age",  1);
  auto p2 = system4_tree.push_back(std::make_pair("", bp::ptree()));
  p2->second.put("name", "jerry");
  p2->second.put("age",  2);

  // system5
  auto& system5_tree = config_tree.add_child("system5", bp::ptree());
  auto s1 = system5_tree.push_back(std::make_pair("", bp::ptree()));
  s1->second.put("", "Sun");
  auto s2 = system5_tree.push_back(std::make_pair("", bp::ptree()));
  s2->second.put("", "Earth");
  auto s3 = system5_tree.push_back(std::make_pair("", bp::ptree()));
  s3->second.put("", "Moon");

  return config_tree;
}

using namespace std;

int main() {
	auto config = MakeConfig();

  for (auto& e : config ) {
    std::cout << e.first << ": " << e.second.data() << std::endl;
  }

  auto system1  = config.get_child("system1");
  auto system2  = config.get_child("system2");
  auto system3  = config.get_child("system3");
  auto system4  = config.get_child("system4");
  auto system5  = config.get_child("system5");


  std::cout << "name1 => " << system1.get("name1", "") << std::endl;
  std::cout << "name2 => " << system1.get("name2", "") << std::endl;
  std::cout << "name3 => " << system1.get("name3", "") << std::endl;
  std::cout << "name4 => " << system1.get("name4", "") << std::endl;

  std::cout << "name1 => " << system2.get("name1", "")    << std::endl;
  std::cout << "name2 => " << system2.get("name2", "")    << std::endl;
  std::cout << "name3 => " << system2.get("name3", false) << std::endl;
  std::cout << "name4 => " << system2.get("name4", 0)     << std::endl;
  std::cout << "name5 => " << system2.get("name5", 0)     << std::endl;

  std::cout << "sub1: " << system3.get_child("sub1").begin()->first << std::endl;
  std::cout << "host => " << system3.get_child("sub1").begin()->second.get("host", "")  << std::endl;
  std::cout << "port => " << system3.get_child("sub1").begin()->second.get("port", 0)   << std::endl;
  std::cout << "sub2: " << system3.get_child("sub2").begin()->first << std::endl;
  std::cout << "host => " << system3.get_child("sub2").begin()->second.get("host", "")  << std::endl;
  std::cout << "port => " << system3.get_child("sub2").begin()->second.get("port", 0)   << std::endl;

  for (auto e : system4) {
    auto name = e.second.get("name", "");
    auto age  = e.second.get("age",  0);
    std::cout << name << " => " << age << std::endl;
  }

  for (auto e : system5) {
    std::cout << e.second.data() << std::endl;
  }

	return 0;
}
