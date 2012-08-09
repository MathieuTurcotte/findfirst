# Copyright (C) 2011 Mathieu Turcotte (mathieuturcotte.ca)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.

CC=cc
CFLAGS=-Wall -Wextra -O3
LDFLAGS=

test_spec_objs=spec.o test_spec.o
test_findfirst_objs=spec.o findfirst.o test_findfirst.o
main_objs=spec.o findfirst.o main.o

all: test_spec test_findfirst main

test_spec: $(test_spec_objs)
	$(CC) $(LDFLAGS) $(test_spec_objs) -o $@

test_findfirst: $(test_findfirst_objs)
	$(CC) $(LDFLAGS) $(test_findfirst_objs) -o $@

main: $(main_objs)
	$(CC) $(LDFLAGS) $(main_objs) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

spec.o:	spec.h
findfirst.o: findfirst.h

.PHONY : clean
clean:
	rm -v -f -r *.o test_spec test_findfirst main base
