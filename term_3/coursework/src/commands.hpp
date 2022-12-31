#pragma once

#include <string>

#include "sorted_string_array.hpp"

namespace coursework {
  namespace editor {
    class Editor {
  private:
      std::string filename_;
      SortedStringArray *ssa_;

  public:
      Editor(SortedStringArray *ssa = nullptr);
      ~Editor();
      void open(std::string &filename);
      void close();
      void save();
      int find(std::string &str);
      void add(std::string &str);
      void remove(size_t pos);
      void defragment();
      std::string at(size_t pos);
      size_t size();
      SortedStringArray::ConstIterator itbegin();
      SortedStringArray::ConstIterator itend();
    };

    class Command {
  protected:
      Editor *editor_;
      Command(Editor *editor);

  public:
      virtual ~Command() = default;
      enum class Status { exit, ok };
      virtual Status execute(std::string &queue) const = 0;
    };

    class QuitCommand : public Command {
  public:
      QuitCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class OpenCommand : public Command {
  public:
      OpenCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class CloseCommand : public Command {
  public:
      CloseCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class SaveCommand : public Command {
  public:
      SaveCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class FindCommand : public Command {
  public:
      FindCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class AddCommand : public Command {
  public:
      AddCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class RemoveCommand : public Command {
  public:
      RemoveCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class DefragmentCommand : public Command {
  public:
      DefragmentCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class AtCommand : public Command {
  public:
      AtCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };

    class ShowCommand : public Command {
  public:
      ShowCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };
    class HelpCommand : public Command {
  public:
      HelpCommand(Editor *editor);
      Status execute(std::string &queue) const override;
    };
  }  // namespace editor
}  // namespace coursework
