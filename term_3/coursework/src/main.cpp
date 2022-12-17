/* Создать класс, производный от fstream. Файл содержит массив указателей
 * на упорядоченные по алфавиту строки, представленные записями переменной
 * длины: целый счетчик и последовательность символов.
 *
 * Формат файла:
 *     в начале его размер массива указателей,
 *     текущее количество указателей,
 *     адрес массива указателей в файле.
 *
 * Обеспечить полную функциональность класса.
 * Протестировать его.
 * Программа тестирования должна содержать меню, обеспечивающее выбор операций.
 *
 * Дополнение: добавить в коллекцию вложенный класс, реализующий функции
 * итератора.
 */


#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "sorted_string_array.hpp"


class Editor {
  private:
  std::string filename_;
  SortedStringArray *ssa_;

  public:
  Editor(SortedStringArray *ssa = nullptr) : ssa_(ssa) {}
  ~Editor() {
    if (ssa_)
      delete ssa_;
  }
  void open(std::string &filename) {
    close();
    filename_ = filename;
    ssa_ = new SortedStringArray(filename_);
  }
  void close() {
    if (ssa_)
      delete ssa_;
    ssa_ = nullptr;
  }
  void save() {
    close();
    open(filename_);
  }
  void add(std::string &str) {
    if (ssa_)
      ssa_->add(str);
    else
      throw SortedStringArray::FileNotOpen();
  }
  void remove(size_t pos) {
    if (ssa_)
      ssa_->remove(pos);
    else
      throw SortedStringArray::FileNotOpen();
  }
  void defragment() {
    if (ssa_)
      ssa_->defragment();
    else
      throw SortedStringArray::FileNotOpen();
  }
  std::string at(size_t pos) {
    if (ssa_)
      return ssa_->at(pos);
    else
      throw SortedStringArray::FileNotOpen();
  }
  size_t size() {
    if (ssa_)
      return ssa_->size();
    else
      throw SortedStringArray::FileNotOpen();
  }
};


class Command {
  protected:
  Editor *editor_;
  Command(Editor *editor) : editor_(editor) {}

  public:
  virtual ~Command() = default;
  enum class Status { exit, ok, error };
  virtual Status execute(std::string &queue) const = 0;
};

class QuitCommand : public Command {
  public:
  QuitCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->close();
    return Status::exit;
  }
};

class OpenCommand : public Command {
  public:
  OpenCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->open(queue);  // TODO
    return Status::ok;
  }
};

class CloseCommand : public Command {
  public:
  CloseCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->close();
    return Status::ok;
  }
};

class SaveCommand : public Command {
  public:
  SaveCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->save();
    return Status::ok;
  }
};

class AddCommand : public Command {
  public:
  AddCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->add(queue);
    return Status::ok;
  }
};

class RemoveCommand : public Command {
  public:
  RemoveCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->remove(std::stoi(queue));
    return Status::ok;
  }
};

class DefragmentCommand : public Command {
  public:
  DefragmentCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    editor_->defragment();
    return Status::ok;
  }
};

class AtCommand : public Command {
  public:
  AtCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    std::cout << editor_->at(std::stoi(queue)) << std::endl;
    return Status::ok;
  }
};

class ShowCommand : public Command {
  public:
  ShowCommand(Editor *editor) : Command(editor) {}
  Status execute(std::string &queue) const override {
    auto size = editor_->size();
    for (size_t i = 0; i < size; ++i) {
      std::cout << "[" << i << "] - \"" << editor_->at(i) << "\"" << std::endl;
    }
    return Status::ok;
  }
};


int main() {
  Editor editor;
  std::unordered_map<std::string, Command *> commands = {
    {"quit", new QuitCommand(&editor)},
    {"open", new OpenCommand(&editor)},
    {"close", new CloseCommand(&editor)},
    {"save", new SaveCommand(&editor)},
    {"defrag", new DefragmentCommand(&editor)},
    {"add", new AddCommand(&editor)},
    {"remove", new RemoveCommand(&editor)},
    {"at", new AtCommand(&editor)},
    {"show", new ShowCommand(&editor)},
  };
  bool quit = false;
  std::string query;
  Command::Status status = Command::Status::ok;
  while (!quit) {
    std::getline(std::cin, query);

    std::stringstream ss(query);
    std::string command_name, args;

    ss >> command_name;
    ss.get();
    std::getline(ss, args);

    try {
      // std::cout << "command: " << command_name << std::endl;
      // status = commands.at(command)->execute(args);
      auto command = commands.at(command_name);
      try {
        status = command->execute(args);
      } catch (std::out_of_range) {
        std::cout << "this index out of range" << std::endl;
      } catch (SortedStringArray::FileNotOpen) {
        std::cout << "file not open" << std::endl;
      }
    } catch (std::out_of_range) {
      // std::cout << "bad command: " << command_name << std::endl;
    }
    // std::cout << "status: " << int(status) << std::endl;
    quit = quit || (status == Command::Status::exit);
  }

  for (const auto &[key, command] : commands) {
    delete command;
  }
  // SortedStringArray s;
  // s.open("1.ssa");
  // for (const auto &str : s) {
  //   std::cout << str << std::endl;
  // }
  // s.close();
  return 0;
}
