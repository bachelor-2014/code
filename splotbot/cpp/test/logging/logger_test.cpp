#include "../../logging/logger.h"
#include "../../logging/filelogger.h"

using namespace std;

int test_logger_instantiation()
{
    Logger l = Logger("loller");
    FileLogger fl = FileLogger("file");
}

int test_write(){
    Logger l = Logger("loller");
    l.Write((void*)"aaa");


    FileLogger fl = FileLogger("file");
    fl.Write((void*)"bbb");
}

int main() {
    test_logger_instantiation();
    test_write();
    return 0;
}
