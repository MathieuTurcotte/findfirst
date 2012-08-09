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

#include <assert.h>

#include "spec.h"

int main() {
    assert(match_spec("foobar.txt", "foobar.txt") == 1);

    assert(match_spec("?oobar.txt", "foobar.txt") == 1);
    assert(match_spec("foo?ar.txt", "foobar.txt") == 1);
    assert(match_spec("foobar.tx?", "foobar.txt") == 1);
    assert(match_spec("??????????", "foobar.txt") == 1);

    assert(match_spec("foo*bar.txt", "foobar.txt") == 1);
    assert(match_spec("foobar.txt*", "foobar.txt") == 1);
    assert(match_spec("*foobar.txt", "foobar.txt") == 1);
    assert(match_spec("fo*ar.txt", "foobar.txt") == 1);
    assert(match_spec("*bar.txt", "foobar.txt") == 1);
    assert(match_spec("foo*", "foobar.txt") == 1);
    assert(match_spec("**", "foobar.txt") == 1);
    assert(match_spec("*", "foobar.txt") == 1);

    assert(match_spec("?*", "foobar.txt") == 1);
    assert(match_spec("*?", "foobar.txt") == 1);
    assert(match_spec("foo*?ar.txt", "foobar.txt") == 1);

    assert(match_spec("abc", "") == 0);
    assert(match_spec("abc", "def") == 0);
    assert(match_spec("abc?", "abc") == 0);
    assert(match_spec("ab", "abc") == 0);
    assert(match_spec("", "abc") == 0);

    return 0;
}

