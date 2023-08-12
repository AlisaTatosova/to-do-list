#ifndef FILEHANDLER_H
#define FILE_HANDLER
#include <iostream>
#include "task.h"
#include <fstream>
#include <vector>

class Saver {
public:
    virtual void save_in_file(const std::vector<Task>& tasks) = 0;
};

class FileSaver : public Saver {
public:
    void save_in_file(const std::vector<Task>& tasks) override;
};

#endif