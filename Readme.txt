KLUSolve 1.0, Copyright (c) 2008, EnerNex Corporation
All rights reserved.

GCC Makefiles, Copyright (c) 2016, Thomas E. McDermott
All rights reserved.

Cmake scripts, Copyright (c) 2020, Battelle Memorial Institute
All rights reserved.

KLU Version 1.0, May 31, 2007, by Timothy A. Davis and Ekanathan Palamadai.
Copyright (C) 2004-2007, University of Florida

CSparse: a Concise Sparse Matrix package.
Version 2.2.0, Copyright (c) 2006-2007, Timothy A. Davis, Mar 31, 2007.

AMD Version 2.2, Copyright (c) 2007 by Timothy A.
Davis, Patrick R. Amestoy, and Iain S. Duff.  All Rights Reserved.

BTF Version 1.0, May 31, 2007, by Timothy A. Davis
Copyright (C) 2004-2007, University of Florida

CZSparse, Copyright (c) 2008, EnerNex Corporation. All rights reserved.

==========================================================================

KLUSolve is a complex sparse matrix library tailored to electric power 
systems, licensed under LGPL version 2.1 (see files License.txt and 
lgpl_2_1.txt in this directory). For an example of use, see the OpenDSS 
project at www.sourceforge.net/projects/electricdss

Contact: Tom McDermott, t dot mcdermott at ieee dot org

==========================================================================

KLUSolve is based on the KLU, CSparse, and supporting libraries developed
by Timothy A. Davis and his students, which are also licensed under LGPL 
version 2.1.  All source files used in KLUSolve are included in the 
SourceForge SVN repository for KLUSolve

Current versions: http://http://faculty.cse.tamu.edu/davis/suitesparse.html

Contact: davis at tamu dot edu, or 

  Tim Davis, Professor
  425E HRBB
  Texas A&M University
  College Station, TX 77843-3112
  1-979-845-4094

Reference Book: "Direct Methods for Sparse Linear Systems," Timothy A. Davis,
SIAM, Philadelphia, 2006.

===========================================================================
Build Instructions - Windows

Install compiler and Cmake from: https://visualstudio.microsoft.com/downloads/ 
(find `Build Tools for Visual Studio 2019` under `Tools for Visual Studio 2019`)

Then follow these instructions:

1. Open the `x64 Native Tools Command Prompt for VS 2019`
2. From the _KLUSolve_ project directory:
   a. `md build`
   b. `cd build`
   c. `cmake ..`
   d. `cmake --build . --config Release`
   e. `cmake --build . --config Debug`
   f. `cmake --install .`
3. Test _KLDemo.exe_ from the project-level Test subdirectory
   a. `unzip kundert_test_matrices.zip`
   b. `run_concat.bat`
   c. results are in _summary.out_
   d. when finished, `del *.mat`
4. Link _KLUSolve.dll_ from the project-level Lib subdirectory

(The Makefiles work with mingw32 and msys2, but are no longer maintained.)

===========================================================================
Build Instructions - Linux and Mac OS X

Install Make and then follow these instructions:

1. From the _KLUSolve_ project directory:
   a. `mkdir build`
   b. `cd build`
   c. `cmake -DCMAKE_BUILD_TYPE=Release ..`
   d. `make`
   e. `make install`
2. Test _KLDemo_ from the project-level Test subdirectory
   a. `unzip kundert_test_matrices.zip`
   b. `./run_concat.sh`
   c. results are in _summary.out_
   d. when finished, `rm *.mat`
3. Link the KLUSolve _so_ or _dylib_ from the project-level Lib subdirectory

(The standalone Makefiles are no longer maintained.)

===========================================================================


