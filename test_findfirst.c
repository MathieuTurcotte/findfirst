/*
 * Copyright (C) 2011 Mathieu Turcotte (mathieuturcotte.ca)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#ifdef WIN32
    #include <io.h>
    #include <direct.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
    #include "findfirst.h"
#endif

#ifdef WIN32
    #define mkdir(path, mode) _mkdir(path)
#endif

int main() {
    int count;
    intptr_t handle;
    struct _finddata_t data;

    mkdir("base", 0766);
    mkdir("base/folder1", 0766);
    mkdir("base/folder2", 0766);

    fclose(fopen("base/file1.txt", "w"));
    fclose(fopen("base/file2.txt", "w"));

    /* Empty specifications should return no entries. */
    errno = 0;
    assert(_findfirst("", &data) == -1L);
    assert(errno == ENOENT);

    errno = 0;
    assert(_findfirst("/", &data) == -1L);
    assert(errno == ENOENT);

    errno = 0;
    assert(_findfirst("./", &data) == -1L);
    assert(errno == ENOENT);

    /* . should return the name of the directory. */
    errno = 0;
    handle = _findfirst("base/.", &data);
    assert(handle != -1L);
    assert(strcmp("base", data.name) == 0);
    assert(_findnext(handle, &data) == -1);
    assert(errno == ENOENT);
    assert(_findclose(handle) == 0);

    /* .. should return the name of the parent directory. */
    errno = 0;
    handle = _findfirst("base/folder1/..", &data);
    assert(handle != -1L);
    assert(strcmp("base", data.name) == 0);
    assert(_findnext(handle, &data) == -1);
    assert(errno == ENOENT);
    assert(_findclose(handle) == 0);

    /* *. should only return directories, . and .. included. */
    errno = count = 0;
    handle = _findfirst("base/*.", &data);
    assert(handle != -1L);
    do {
        count++;
        assert(data.attrib & _A_SUBDIR);
    } while (_findnext(handle, &data) == 0);
    assert(count == 4);
    assert(errno == ENOENT);
    assert(_findclose(handle) == 0);

    /* *.* should return every entries, folders and files. */
    errno = count = 0;
    handle = _findfirst("base/*.*", &data);
    assert(handle != -1L);
    do {
        count++;
    } while (_findnext(handle, &data) == 0);
    assert(count == 6);
    assert(errno == ENOENT);
    assert(_findclose(handle) == 0);

    /* * should return every entries, folders and files. */
    errno = count = 0;
    handle = _findfirst("base/*", &data);
    assert(handle != -1L);
    do {
        count++;
    } while (_findnext(handle, &data) == 0);
    assert(count == 6);
    assert(errno == ENOENT);
    assert(_findclose(handle) == 0);

    /* *.txt should return files ending with .txt. */
    errno = count = 0;
    handle = _findfirst("base/*.txt", &data);
    assert(handle != -1L);
    do {
        count++;
        /* Anything but a directory... */
        assert(!(data.attrib & _A_SUBDIR));
    } while (_findnext(handle, &data) == 0);
    assert(count == 2);
    assert(errno == ENOENT);
    assert(_findclose(handle) == 0);

    return 0;
}

