#include "task.h"

Task::Task(const std::string& to_do, bool is_completed) 
        : to_do{to_do, ++tasks_count} {}

std::pair<std::string, int> Task::get_to_do() const {
    return to_do;
}

std::string Task::get_deadline() const {
    return deadline;
}

bool Task::get_completeness() const {
    return is_completed;
}

void Task::set_new_task(const std::string& new_task) {
    to_do.first = new_task;
}

void Task::set_deadline(const std::string& deadline) {
    this -> deadline = deadline;
}

void Task::set_completed(bool is_completed) {
    this -> is_completed = is_completed;
}

void Task::set_task_num(int task_num) {
    to_do.second = task_num;
}

void Task::dec_tasks_count() {
    --tasks_count;
}











