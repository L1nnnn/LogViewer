// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <dirent.h>
#include <string.h>
#include <iostream>

#include "log_utils.hh"

std::vector<LogItem> *LogUtils::logItems() {
    std::vector<LogItem> *logs = new std::vector<LogItem>();
    std::vector<std::string> *objs = new std::vector<std::string>();

    std::string base = "/var/log/";
    DIR *d;
    struct dirent *dir;
    d = opendir(base.c_str());
    if (d) {
        while ((dir=readdir(d))!=NULL) {
            if (strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0) {
                continue;
            }
            objs->push_back(dir->d_name);
        }
        closedir(d);
    }

    for (int i = 0; i<objs->size(); i++) {
        LogItem item;
        item.log = objs->at(i);
        item.logChildren = new std::vector<std::string>();

        std::string path = base+objs->at(i);
        if (isFolder(path)) {
            item.logChildren = filesInFolder(path);
            if (item.logChildren->size()==0) {
                item.logChildren->push_back("(Empty)");
            }
        }

        logs->push_back(item);
    }

    return logs;
}

bool LogUtils::isFolder(std::string path) {
    bool is = false;
    DIR *d;
    d = opendir(path.c_str());
    if (d) {
        is = true;
        closedir(d);
    }
    return is;
}

std::vector<std::string> *LogUtils::filesInFolder(std::string path) {
    std::vector<std::string> *files = new std::vector<std::string>();

    int len = path.length()-1;
    if (path.at(len)!='/') {
        path+="/";
    }

    DIR *d;
    struct dirent *dir;
    d = opendir(path.c_str());
    if (d) {
        while ((dir=readdir(d))!=NULL) {
            if (strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0) {
                continue;
            } else if (isFolder(path+dir->d_name)) {
                continue;
            } else {
                files->push_back(dir->d_name);
            }
        }
    }

    return files;
}
