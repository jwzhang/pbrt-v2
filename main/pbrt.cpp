
/*
    pbrt source code Copyright(c) 1998-2009 Matt Pharr and Greg Humphreys.

    This file is part of pbrt.

    pbrt is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.  Note that the text contents of
    the book "Physically Based Rendering" are *not* licensed under the
    GNU GPL.

    pbrt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */


// main/pbrt.cpp*
#include "pbrt.h"
#include "api.h"
#include "probes.h"
#include "parser.h"
#include "parallel.h"
#ifdef PBRT_HAS_LIBSDL
#include "SDL_main.h"
#endif // PBRT_HAS_LIBSDL

// main program
int main(int argc, char *argv[]) {
    // Print welcome banner
    printf("pbrt version %s of %s at %s [%d core(s) detected]\n",
           PBRT_VERSION, __DATE__, __TIME__, NumSystemCores());
    printf("Copyright (c)1998-2009 Matt Pharr and "
           "Greg Humphreys.\n");
    printf("The source code to pbrt (but *not* the book contents) is covered by the GNU GPL.\n");
    printf("See the file COPYING.txt for the conditions of the license.\n");
    fflush(stdout);
    pbrtInit();
    // Process scene description
    PBRT_STARTED_PARSING();
    if (argc == 1) {
        // Parse scene from standard input
        ParseFile("-");
    } else {
        // Parse scene from input files
        for (int i = 1; i < argc; i++)
            if (!ParseFile(argv[i]))
                Error("Couldn't open scene file \"%s\"", argv[i]);
    }
    pbrtCleanup();
    return 0;
}


