#include "sheep_log.h"
#include <iostream>
#include <time.h>
using namespace sheep_log;
// cd ./temp_test/log 
// g++ test.cpp ../../log/sheep_log.cpp -o test -I "../../log/include"

#define MICRO_IN_SECOND 1000000
#define NANOS_IN_SECOND 1000000000
double currentTimeInMiliSeconds()
{
    struct timespec res;
    double ret = 0;
    clock_gettime(CLOCK_MONOTONIC, &res);
    ret = (double)(res.tv_sec * NANOS_IN_SECOND + res.tv_nsec) / MICRO_IN_SECOND;

    return ret;
}

int main()
{
    Logger logger("hzlyyds");

    std::shared_ptr<Handler> file_handler = std::make_shared<FileHandler>("log.txt");
    file_handler->SetFormat("%(asctime)s - %(name)s - %(levelname)s - %(message)s");
    file_handler->SetLevel(Warn);
    logger.AddHandler(file_handler);

    std::shared_ptr<Handler> stream_handler = std::make_shared<StreamHandler>();
    stream_handler->SetFormat("%(asctime)s - %(name)s - %(levelname)s - %(message)s");
    stream_handler->SetLevel(Info);
    logger.AddHandler(stream_handler);

    double t1 = currentTimeInMiliSeconds();

    logger[Info] << "hzlyyds " <<endl<<endl<<"123";
    logger[Error] << "champion yyds " <<endl<<" test "<<endl<<"123"<<endl;
    // double t2 = currentTimeInMiliSeconds();
    // std::cout << std::endl
    //           << t2 - t1 << std::endl;
    return 0;
}