#include "controllers/FileController.h"
#include "exceptions/TransitExceptions.h"
#include "utilities/CustomDate.h"
#include <fstream>
#include <sys/stat.h>
#ifdef _WIN32
#  include <direct.h>   // _mkdir on MinGW / MSVC
#endif

FileController& FileController::getInstance() {
    static FileController instance;
    return instance;
}

void FileController::initialize() {
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0755);
#endif
}

bool FileController::fileExists(const CustomString& path) const {
    std::ifstream f(path.c_str());
    return f.good();
}

void FileController::writeLog(const CustomString& user, const CustomString& action) const {
    std::ofstream log("data/transit_log.txt", std::ios::app);
    if (!log.is_open())
        throw FileNotFoundException(
            CustomString("Cannot open log file"),
            CustomString("FileController"), 7001);
    log << "[" << CustomDate::today().toString().c_str() << "] "
        << "[" << user.c_str() << "] "
        << action.c_str() << "\n";
}
