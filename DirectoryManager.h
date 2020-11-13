#include <pwd.h>
#include <string>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define CHATBOT_PATH "ChatBot/"
#define CHATBOT_MODE 0755

class DirManager {
  public:
    static string GetUserDirectory();
    static string CheckUserDirectory();
    static int CreateFile(char *fileName, mode_t mode);
    static int OpenFile(char *fileName, int flag);
    static void DeleteFile(char *fileName);
};
