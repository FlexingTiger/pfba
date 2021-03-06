//
// Created by cpasjuste on 19/12/16.
//

#include <sys/stat.h>
#include "psp2_utility.h"
#include "psp2_dirent.h"

bool Utility::FileExist(const char *file) {

    struct stat buf;
    return (stat(file, &buf) == 0);
}

std::vector<std::string> Utility::GetFileList(const char *path) {

    std::vector<std::string> files;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (SCE_S_ISREG(ent->d_stat.st_mode)) {
                files.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    }

    return files;
}
