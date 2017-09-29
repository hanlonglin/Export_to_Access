#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#define LOG_FILE               "log.log"

using namespace std;

class Log
{
public:
    Log();
    ~Log();
    /*写入log文件*/
    static int writeLog(string content);
};

#endif // LOG_H
