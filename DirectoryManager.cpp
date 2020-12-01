#include "DirectoryManager.h"

const char *DirManager::CHATBOT_PATH = "ChatBot/";

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

int DirManager::CreateFile(const char *fileName, mode_t mode) {
    string userDir = CheckUserDirectory();
    userDir.append(fileName);

    return creat(userDir.c_str(), mode);
}

int DirManager::OpenFile(const char *fileName, int flag, mode_t mode) {
    string userDir = CheckUserDirectory();
    userDir.append(fileName);

    if (flag & O_CREAT)
        return open(userDir.c_str(), flag, mode);
    else
        return open(userDir.c_str(), flag);
}

void DirManager::DeleteFile(const char *fileName) {
    string userDir = CheckUserDirectory();
    userDir.append(fileName);

    unlink(userDir.c_str());
}
