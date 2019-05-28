#include "ContentManager.hpp"
#include <algorithm>
#include <iostream>
#include "IContentPipeline.hpp"
#if __APPLE__
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace gel {
ContentManager::ContentManager(const std::string& rootDir)
    : rootDir(rootDir), files(), pipes() {
        collect(rootDir);
}

void ContentManager::add(const std::shared_ptr<IContentPipeline>& pipe) {
        this->pipes.push_back(pipe);
}

void ContentManager::remove(const std::shared_ptr<IContentPipeline>& pipe) {
        //        auto iter = std::find(pipes.begin(), pipes.end(),
        //                              [pipe](auto& e) -> bool { return e ==
        //                              pipe; });
        // pipes.erase(iter);
}

void ContentManager::load() {
        std::for_each(files.begin(), files.end(), [&](auto file) {
                std::for_each(pipes.begin(), pipes.end(), [&](auto p) {
                        if (p->accept(file)) {
                                p->load(file);
                        }
                });
        });
}

void ContentManager::unload() {
        std::for_each(files.begin(), files.end(), [&](auto file) {
                std::for_each(pipes.begin(), pipes.end(), [&](auto p) {
                        if (p->accept(file)) {
                                p->unload(file);
                        }
                });
        });
}

// private
void ContentManager::collect(const std::string& dir) {
#if __APPLE__
        auto dp = ::opendir(dir.c_str());
        struct dirent* de;
        if (dp == NULL) {
                return;
        }
        struct stat path_stat;
        for (de = ::readdir(dp); de != NULL; de = ::readdir(dp)) {
                std::string name = de->d_name;
                if (name == "." || name == "..") {
                        continue;
                }
                name = dir + '/' + name;
                ::stat(name.c_str(), &path_stat);
                if (S_ISREG(path_stat.st_mode)) {
                        files.push_back(name);
                } else {
                        collect(name);
                }
        }
        ::closedir(dp);
#endif
}
}  // namespace gel
