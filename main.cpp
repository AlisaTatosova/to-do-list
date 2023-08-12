#include "todolist.h"
#include <string>
#include <iostream>

enum CHOICE {
    ADD_TASK = 1,
    DELETE_TASK,
    UPDATE_TASK,
    MENTION_COMPLETED,
    CHECK_TASKS_COMPLETNESS,
    EXIT,
};

int main() {
    FileSaver file_saver;
    ToDoList list(file_saver);
    std::cout << "   Welcome to your to do list " << std::endl;
    std::cout << "--------------------------------" << std::endl;
    while (true) {
        std::cout << std::endl;
        list.menu();
        int choice{};
        std::cout << "Enter the number of your choice: ";
        std::cin >> choice;
        
        if (choice == ADD_TASK) {
            list.add_task();
        }
        else if (choice == DELETE_TASK) {
            list.delete_task();
        }
        else if (choice == UPDATE_TASK) {
            list.update_task();
        }
        else if (choice == MENTION_COMPLETED) {
            list.mention_completed();
        }
        else if (choice == CHECK_TASKS_COMPLETNESS) {
            std::cout << std::endl;
            list.check_tasks_completeness();
        }
        else if (choice == EXIT) {
            list.save_to_file();
            break;
        }

        list.notify_deadline();
    }

    return 0;
}




