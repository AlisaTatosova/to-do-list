#ifndef TODOLIST_H
#define TODOLIST_H
#include "filehandler.h"
#include "task.h"
#include <vector>
#include <map>

class ToDoList {
public:
    explicit ToDoList(Saver& saver);
    void menu();
    void add_task();
    void delete_task();
    void update_task();
    void mention_completed();
    void check_tasks_completeness();
    void display_all_tasks();
    void save_to_file();
    void notify_deadline();
    std::map<std::string, int> get_current_date_time();

private:
    std::vector<Task> tasks; 
    Saver& saver;
};

#endif