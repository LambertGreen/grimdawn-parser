#include "player.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <player.gdc file> <player-name>\n", argv[0]);
    return 1;
  }

  try {
    json j;
    j.emplace("player-name", argv[2]);

    player player(argv[1]);
    j.emplace("player-data", player.get_json());

    std::cout << j.dump() << std::endl;

  } catch (const std::runtime_error& e) {
    std::cout << "Exception:" << e.what() << std::endl;

  } catch (const std::exception& e) {
    printf("Error reading file: %s\n", argv[1]);
    return 1;
  }

  return 0;
}
