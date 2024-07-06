#include "mmapper.h"

#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

template <typename T>
struct TD;

namespace argoko
{
MMapper::MMapper(const std::string& _fn, const uint32_t _size, const int _mode,
                 const bool expand)
    : fn(_fn), size(_size), mode(_mode), closed(false)
{
    fd = open(fn.c_str(), mode, (mode_t)0660);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    cout << "Opened file fd is " << fd << endl;
    if (expand) {
        int result = lseek(fd, size - 1, SEEK_SET);
        if (result == -1) {
            ::close(fd);
            perror("Error calling lseek() to 'stretch' the file");
            exit(EXIT_FAILURE);
        }

        result = write(fd, "", 1);
        if (result != 1) {
            ::close(fd);
            perror("Error writing last byte of the file");
            exit(EXIT_FAILURE);
        }
    }

    cout << "About to mmap" << endl;
    map = mmap(0, size, mode, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        ::close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    cout << "Map is " << map << endl;
}

void MMapper::close()
{
    if (!closed) {
        if (munmap(map, size) == -1) {
            perror("Error un-mmapping the file");
            /* Decide here whether to close(fd) and exit() or not. Depends... */
        }
        ::close(fd);
    }
}

MMapper::~MMapper()
{
    // Mucky pups
    if (!closed) {
        close();
    }
}
} // namespace argoko
