#include <pwd.h>
#include <string>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

class DirManager {
  public:
    static const char *CHATBOT_PATH;
    static const int CHATBOT_MODE = 0755;

  public:
    static string GetUserDirectory();
    static string CheckUserDirectory();
    static int CreateFile(char *fileName, mode_t mode);
    static int OpenFile(char *fileName, int flag, mode_t mode = 0);
    static void DeleteFile(char *fileName);
};
