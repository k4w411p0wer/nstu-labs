#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "commands.hpp"
#include "sorted_string_array.hpp"


int main() {
  coursework::editor::Editor editor;
  std::unordered_map<std::string, coursework::editor::Command *> commands = {
    {"quit", new coursework::editor::QuitCommand(&editor)},
    {"open", new coursework::editor::OpenCommand(&editor)},
    {"close", new coursework::editor::CloseCommand(&editor)},
    {"save", new coursework::editor::SaveCommand(&editor)},
    {"defrag", new coursework::editor::DefragmentCommand(&editor)},
    {"find", new coursework::editor::FindCommand(&editor)},
    {"add", new coursework::editor::AddCommand(&editor)},
    {"remove", new coursework::editor::RemoveCommand(&editor)},
    {"at", new coursework::editor::AtCommand(&editor)},
    {"show", new coursework::editor::ShowCommand(&editor)},
    {"help", new coursework::editor::HelpCommand(&editor)},
  };
  bool quit = false;
  std::string query;
  coursework::editor::Command::Status status =
    coursework::editor::Command::Status::ok;

  std::string q = "";
  commands["help"]->execute(q);

  while (!quit) {
    std::getline(std::cin, query);

    std::stringstream ss(query);
    std::string command_name, args;

    ss >> command_name;
    ss.get();
    std::getline(ss, args);

    try {
      auto command = commands.at(command_name);
      try {
        status = command->execute(args);
      } catch (std::out_of_range) {
        std::cout << "this index out of range" << std::endl;
      } catch (std::invalid_argument) {
        std::cout << "invalid argument for command" << std::endl;
      } catch (coursework::SortedStringArray::FileNotOpen) {
        std::cout << "file not open" << std::endl;
      }
    } catch (std::out_of_range) {}
    quit = quit || (status == coursework::editor::Command::Status::exit);
  }

  for (const auto &[key, command] : commands) {
    delete command;
  }
  return 0;
}
