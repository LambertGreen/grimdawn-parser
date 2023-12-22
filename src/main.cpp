#include "player.hpp"

#include <cxxopts.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char** argv) {
  try {
    cxxopts::Options options(argv[0], "GrimDawn Player Commandline Editor");
    options.add_options()("f,file", "Player.gdc file",
                          cxxopts::value<std::string>())(
        "n,name", "Player name", cxxopts::value<std::string>());
    auto result = options.parse(argc, argv);

    const auto playerGdcFile = result["file"].as<std::string>();
    const auto playerName = result["name"].as<std::string>();

    player player(playerGdcFile.c_str());
    json j{{"player-name", playerName}, {"player-data", player.to_json()}};
    std::cout << j.dump() << std::endl;

  } catch (const std::runtime_error& e) {
    std::cout << "Exception:" << e.what() << std::endl;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
