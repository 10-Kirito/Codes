#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

struct config {
  std::string serverIP;
  int serverPort;
  std::string zookeeperIP;
  int zookeeperPort;

  void load(const std::string &filename);
  void save(const std::string &filename);
};

void config::load(const std::string &filename) {
  pt::ptree tree;
  pt::read_json(filename, tree);

  serverIP = tree.get<std::string>("server.ip");
  serverPort = tree.get<int>("server.port");
  zookeeperIP = tree.get<std::string>("zookeeper.ip");
  zookeeperPort = tree.get<int>("zookeeper.port");
}

void config::save(const std::string &filename) {
  pt::ptree tree;

  tree.put("server.ip", serverIP);
  tree.put("server.port", serverPort);
  tree.put("zookeeper.ip", zookeeperIP);
  tree.put("zookeeper.port", zookeeperPort);

  pt::write_json(filename, tree);
}

int main() {
  // test the property_tree:
  config cfg;
  cfg.load("config.json");
  cfg.save("config2.json");
  return 0;
}