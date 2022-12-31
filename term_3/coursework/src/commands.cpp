#include <iostream>

#include "commands.hpp"
#include "sorted_string_array.hpp"

namespace coursework {
  namespace editor {
    Editor::Editor(SortedStringArray *ssa) : ssa_(ssa) {}

    Editor::~Editor() {
      if (ssa_)
        delete ssa_;
    }

    void Editor::open(std::string &filename) {
      close();
      filename_ = filename;
      ssa_ = new SortedStringArray(filename_);
    }

    void Editor::close() {
      if (ssa_)
        delete ssa_;
      ssa_ = nullptr;
    }

    void Editor::save() {
      close();
      open(filename_);
    }

    int Editor::find(std::string &str) {
      if (ssa_)
        return ssa_->find(str);
      else
        throw SortedStringArray::FileNotOpen();
    }

    void Editor::add(std::string &str) {
      if (ssa_)
        ssa_->add(str);
      else
        throw SortedStringArray::FileNotOpen();
    }

    void Editor::remove(size_t pos) {
      if (ssa_)
        ssa_->remove(pos);
      else
        throw SortedStringArray::FileNotOpen();
    }

    void Editor::defragment() {
      if (ssa_)
        ssa_->defragment();
      else
        throw SortedStringArray::FileNotOpen();
    }

    std::string Editor::at(size_t pos) {
      if (ssa_)
        return ssa_->at(pos);
      else
        throw SortedStringArray::FileNotOpen();
    }

    size_t Editor::size() {
      if (ssa_)
        return ssa_->size();
      else
        throw SortedStringArray::FileNotOpen();
    }


    SortedStringArray::ConstIterator Editor::itbegin() {
      return ssa_->begin();
    }

    SortedStringArray::ConstIterator Editor::itend() {
      return ssa_->end();
    }

    Command::Command(Editor *editor) : editor_(editor) {}


    QuitCommand::QuitCommand(Editor *editor) : Command(editor) {}

    Command::Status QuitCommand::execute(std::string &queue) const {
      editor_->close();
      return Status::exit;
    }

    OpenCommand::OpenCommand(Editor *editor) : Command(editor) {}

    Command::Status OpenCommand::execute(std::string &queue) const {
      editor_->open(queue);
      return Status::ok;
    }

    CloseCommand::CloseCommand(Editor *editor) : Command(editor) {}

    Command::Status CloseCommand::execute(std::string &queue) const {
      editor_->close();
      return Status::ok;
    }

    SaveCommand::SaveCommand(Editor *editor) : Command(editor) {}

    Command::Status SaveCommand::execute(std::string &queue) const {
      editor_->save();
      return Status::ok;
    }

    FindCommand::FindCommand(Editor *editor) : Command(editor) {}

    Command::Status FindCommand::execute(std::string &queue) const {
      std::cout << editor_->find(queue) << std::endl;
      return Status::ok;
    }

    AddCommand::AddCommand(Editor *editor) : Command(editor) {}

    Command::Status AddCommand::execute(std::string &queue) const {
      editor_->add(queue);
      return Status::ok;
    }

    RemoveCommand::RemoveCommand(Editor *editor) : Command(editor) {}

    Command::Status RemoveCommand::execute(std::string &queue) const {
      editor_->remove(std::stoi(queue));
      return Status::ok;
    }

    DefragmentCommand::DefragmentCommand(Editor *editor) : Command(editor) {}

    Command::Status DefragmentCommand::execute(std::string &queue) const {
      editor_->defragment();
      return Status::ok;
    }

    AtCommand::AtCommand(Editor *editor) : Command(editor) {}

    Command::Status AtCommand::execute(std::string &queue) const {
      std::cout << editor_->at(std::stoi(queue)) << std::endl;
      return Status::ok;
    }

    ShowCommand::ShowCommand(Editor *editor) : Command(editor) {}

    Command::Status ShowCommand::execute(std::string &queue) const {
      auto end = editor_->itend();
      auto index = 0;
      for (auto it = editor_->itbegin(); it < end; ++it, ++index) {
        std::cout << "[" << index << "] - \"" << *it << "\""
                  << std::endl;
      }

      return Status::ok;
    }


    HelpCommand::HelpCommand(Editor *editor) : Command(editor) {}
    Command::Status HelpCommand::execute(std::string &queue) const {
      std::cout << "Help:\n"
                << "quit             - quit\n"
                << "open [filename]  - open file\n"
                << "close            - close file\n"
                << "save             - save\n"
                << "defrag           - defragment\n"
                << "find [string]    - find [string]\n"
                << "add [string]     - add [string]\n"
                << "remove [index]   - remove record at [index]\n"
                << "at [index]       - show record at [index]\n"
                << "show             - show all records in file\n"
                << "help             - show this message" << std::endl;
      return Status::ok;
    }

  }  // namespace editor
}  // namespace coursework
