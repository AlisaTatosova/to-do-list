#include "todolist.h"
#include <ctime>
#include <iostream>
#include <fstream> 
#include <string>
#include <map>

int Task::tasks_count = 0;

ToDoList::ToDoList(Saver& saver) : saver{saver} {}

void ToDoList::menu() {
    std::cout << "            Here are the actions that you can do " << std::endl;
    std::cout << "1)add task" << std::endl;
    std::cout << "2)delete task" << std::endl;
    std::cout << "3)update task" << std::endl;
    std::cout << "4)mention task as completed" << std::endl;
    std::cout << "5)check completeness count " << std::endl;
    std::cout << "6)exit" << std::endl;
}

void ToDoList::add_task() {
    std::cin.ignore(); 
    std::string task;
    std::cout << "Please, add the task: ";
    std::getline(std::cin, task);
    std::cout << "Please, add deadline for this task in this form [day-month-year hour::min] : ";
    std::string deadline;
    std::getline(std::cin, deadline);
    Task new_task(task);
    new_task.set_deadline(deadline);
    tasks.push_back(new_task);
    std::cout << std::endl;
    std::cout << task << " is added to your to do list" << std::endl;
}

void ToDoList::delete_task() {
    display_all_tasks();
    int id{};
    std::cout << "Please input the number of task to delete: ";
    std::cin >> id;
    std::cout << std::endl;
    bool is_found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        std::pair<std::string, int> to_do = it -> get_to_do();
        if (id == to_do.second) {
            Task::dec_tasks_count();
            is_found = true;
            tasks.erase(it);
            std::cout << "Task " << to_do.first << " is deleted" << std::endl;
            break;
        }
    }

    if (!is_found) {
         std::cout << "Such task is not found!" << std::endl;
    }

    for (auto it = tasks.begin(); it != tasks.end(); ++it) { // in order not to violate the numbering
        std::pair<std::string, int> to_do = it -> get_to_do();
        if (to_do.second > id) {
            it -> set_task_num(--to_do.second);
        }
    }
}

void ToDoList::update_task() {
    display_all_tasks();
    int id{};
    std::cout << "Please input the number of task you want to update: ";
    std::cin >> id;
    std::string new_task;
    std::cout << "Please write new task to update: ";
    std::cin >> new_task;
    bool is_found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        std::pair<std::string, int> to_do = it -> get_to_do();
        if (id == to_do.second) {
            is_found = true;
            it -> set_new_task(new_task);
            std::cout << "Task " << to_do.second << " is updated" << std::endl;
            break;
        }
    }

    if (!is_found) {
        std::cout << "There is no task with such id" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "task " << id << " is updated" << std::endl;
}

void ToDoList::mention_completed() {
    display_all_tasks();
    int id{};
    std::cout << "Please input the number of task to mention completed: ";
    std::cin >> id;
    std::cout << std::endl;
    bool is_found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        std::pair<std::string, int> to_do = it -> get_to_do();
        if (id == to_do.second) {
            is_found = true;
            it -> set_completed(true);
            it -> set_new_task(to_do.first += " completed");
            std::cout << "task " << id << " is mentioned as completed" << std::endl;
            break;
        }
    }

    if (!is_found) {
        std::cout << "There is no task with such id" << std::endl;
    }
}

void ToDoList::check_tasks_completeness() {
    int completed {};
    int uncompleted {};
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        it -> get_completeness() ? ++completed : ++uncompleted;
    }
    std::cout << "Count of completed tasks is " << completed << std::endl;
    std::cout << "Count of uncompleted tasks is " << uncompleted << std::endl;
}

void ToDoList::display_all_tasks() {
    std::cout << "All the tasks" << std::endl;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        std::cout << it -> get_to_do().second << ")";
        std::cout << it -> get_to_do().first << std::endl;
    }
}

std::map<std::string, int> ToDoList::get_current_date_time() {
   time_t now = time(0);
   tm* local_time = localtime(&now);
   std::map<std::string, int> date_time;
   int year = 1900 + local_time -> tm_year;
   date_time["year"] = year;
   int month = 1 + local_time -> tm_mon;
   date_time["month"] = month;
   int day = local_time -> tm_mday;
   date_time["day"] = day;
   int hour = local_time -> tm_hour;
   date_time["hour"] = hour;
   int min = local_time -> tm_min;
   date_time["min"] = min;
   return date_time;
}

void ToDoList::notify_deadline() {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        std::string deadline = it -> get_deadline();
        int day = atoi(deadline.substr(0, 2).c_str()); 
        int month = atoi(deadline.substr(3, 2).c_str()); 
        int year = atoi(deadline.substr(6, 4).c_str()); 
        int hour = atoi(deadline.substr(11, 2).c_str()); 
        int min = atoi(deadline.substr(14, 2).c_str());    
        std::map<std::string, int> date = get_current_date_time();
        if (date["day"] == day && date["month"] == month && date["year"] == year 
            && date["hour"] == hour && date["min"] == min) { 
            std::cout << std::endl;
            std::cout << "Deadline for task: [" << it -> get_to_do().first  << "] is finished " << std::endl;
            std::cout << std::endl; 
        } 
        else if (date["day"] == day && date["month"] == month && date["year"] == year 
            && date["hour"] + 1 == hour) {
            std::cout << std::endl;
            std::cout << "Deadline for task: [" << it -> get_to_do().first  << "] is coming!!! You have only an hour to finish" << std::endl;
            std::cout << std::endl; 
        }
        else if (date["day"] + 1 == day && date["month"] == month && date["year"] == year) {
            std::cout << std::endl;
            std::cout << "Deadline for task: [" << it -> get_to_do().first  << "] is coming!!! You have only a day to finish" << std::endl;
            std::cout << std::endl; 
        }
    }
}

void ToDoList::save_to_file() {
    saver.save_in_file(tasks);
}





