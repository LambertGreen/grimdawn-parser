#include "player.hpp"

#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {

void exportJson(std::string playerGdcFilename,
                std::string playerName,
                std::string outFilename) {
  player player(playerGdcFilename.c_str());
  json j{{"player-name", playerName}, {"player-data", player.to_json()}};

  std::ofstream ofile(outFilename);
  if (ofile.is_open()) {
    ofile << j.dump();
    ofile << "\n";
    ofile.close();
    std::cout << "Json written to " + outFilename << std::endl;
  }
}

void edit(std::string playerGdcFilename,
          std::string edit_action,
          std::string outFilename) {
  player player(playerGdcFilename.c_str());
  if (edit_action == "reset-stats") {
    player.reset_stats();
  }
  player.write(outFilename.c_str());
  std::cout << "Gdc written to " + outFilename << std::endl;
}
}  // namespace

int main(int argc, char** argv) {
  try {
    cxxopts::Options options(argv[0], "GrimDawn Player Commandline Editor");

    // -------------------------------------------------------------------------
    // clang-format off

    options.add_options()
      ("action", "Action to perform: export-json, edit", cxxopts::value<std::string>())
      ("file", "Player.gdc file", cxxopts::value<std::string>())
      ("file-out", "Output file name", cxxopts::value<std::string>())
      ("help", "Print help");

    options.add_options("export-json")
      ("name", "Player name", cxxopts::value<std::string>());

    options.add_options("edit")
      ("edit-action", "Edit action perform: reset-stats", cxxopts::value<std::string>());

    // clang-format on
    // -------------------------------------------------------------------------

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({"", "export-json", "edit"}) << std::endl;
      return 0;
    }

    const auto action = result["action"].as<std::string>();
    const auto playerGdcFilename = result["file"].as<std::string>();
    const auto outFilename = result["file-out"].as<std::string>();

    if (action == "export-json") {
      const auto playerName = result["name"].as<std::string>();
      exportJson(playerGdcFilename, playerName, outFilename);
    } else if (action == "edit") {
      const auto edit_action = result["edit-action"].as<std::string>();
      edit(playerGdcFilename, edit_action, outFilename);
    }
  } catch (const std::runtime_error& e) {
    std::cout << "Exception:" << e.what() << std::endl;
    return -1;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
