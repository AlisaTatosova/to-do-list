#include "filehandler.h"

void FileSaver::save_in_file(const std::vector<Task>& tasks) {
    std::ofstream file("ToDoList.txt");
    file << "            To do list           " << std::endl;
    file << "---------------------------------" << std::endl;
    for (auto& task : tasks) {
        if (file.is_open()) {
            file << task.get_to_do().second << ")" << task.get_to_do().first;
            file << " [" << task.get_deadline() << "]" << std::endl;
        }
    }
}

