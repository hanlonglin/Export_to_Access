#include "log.h"

Log::Log()
{

}
Log::~Log()
{
}

/*写入文件*/
int Log::writeLog(string content)
{
    //获得当前时间

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char tmp[100];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %H:%M:%S", timeinfo);

    //检查文件长度
    ifstream in(LOG_FILE);
    in.seekg(0,ios::end);
    int len = in.tellg();
    //cout <<"文件长度："<< len<<endl;
    bool isDelete = false;
    if (len > (1024 * 1024 * 10))
    {
        //当log文件大于10M的时候删除
        isDelete = true;
    }
    in.close();

    //打开文件写入
    ofstream ofile;
    if (isDelete)
        ofile.open(LOG_FILE, ios::trunc);
    else
        ofile.open(LOG_FILE, ios::app);
    if (!ofile.is_open())
        return 0;

    ofile << tmp << "--" << content << endl;
    ofile.close();
    return 1;
}
