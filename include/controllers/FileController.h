#pragma once
#include "utilities/CustomString.h"

class FileController {
private:
    FileController() = default;
    FileController(const FileController&) = delete;
    FileController& operator=(const FileController&) = delete;

public:
    static FileController& getInstance();
    void initialize();
    bool fileExists(const CustomString& path) const;
    void writeLog(const CustomString& user, const CustomString& action) const;
};
