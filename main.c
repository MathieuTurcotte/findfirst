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

#include <stdio.h>
#include <stdint.h>

#ifdef WIN32
    #include <io.h>
#else
    #include "findfirst.h"
#endif

int main(int argc, char* argv[]) {
    struct _finddata_t data;
    intptr_t handle;

    if((handle = _findfirst(argc > 1 ? argv[1]: "", &data)) != -1L) {
        printf("RDO HID SYS ARC  FILE %19c DATE %25c SIZE\n", ' ', ' ');
        printf("--- --- --- ---  ---- %19c ---- %25c ----\n", ' ', ' ');

        do {
            printf(data.attrib & _A_RDONLY ? " Y  " : " N  ");
            printf(data.attrib & _A_SYSTEM ? " Y  " : " N  ");
            printf(data.attrib & _A_HIDDEN ? " Y  " : " N  ");
            printf(data.attrib & _A_ARCH   ? " Y  " : " N  ");
            printf(" %-24s %.24s  %9llud\n", data.name,
                                             ctime(&data.time_write),
                                             (unsigned long long) data.size);
        } while (_findnext(handle, &data) == 0);

        _findclose(handle);
    }

    return 0;
}
