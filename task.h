#ifndef TASK_H
#define TASK_H
#include <string>

class Task {
public:
    Task(const std::string& to_do = "", bool is_completed = false);
    std::pair<std::string, int> get_to_do() const;
    std::string get_deadline() const;
    bool get_completeness() const;
    void set_new_task(const std::string& new_task);
    void set_deadline(const std::string& deadline); 
    void set_completed(bool is_completed);
    void set_task_num(int task_num);
    static void dec_tasks_count();
    
private:
    std::pair<std::string, int> to_do;
    std::string deadline;
    bool is_completed;
    static int tasks_count;
};

#endif