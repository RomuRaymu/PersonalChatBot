#include "DirectoryManager.h"

string DirManager::GetUserDirectory() {
    struct passwd *userInfo;
    string userDir;

    userInfo = getpwuid(getuid());
    userDir = userInfo->pw_dir;
    userDir.append("/");
    userDir.append(CHATBOT_PATH);

    return userDir;
}

string DirManager::CheckUserDirectory() {
    string userDir = GetUserDirectory();

    mkdir(userDir.c_str(), CHATBOT_MODE);

    return userDir;
}

int DirManager::CreateFile(char *fileName, mode_t mode) {
    string userDir = CheckUserDirectory();
    userDir.append(fileName);

    return creat(userDir.c_str(), mode);
}

int DirManager::OpenFile(char *fileName, int flag) {
    string userDir = CheckUserDirectory();
    userDir.append(fileName);

    return open(userDir.c_str(), flag);
}

void DirManager::DeleteFile(char *fileName) {
    string userDir = CheckUserDirectory();
    userDir.append(fileName);

    unlink(userDir.c_str());
}
