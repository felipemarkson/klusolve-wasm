# KLUSolve for WebAssembly

This repository has scripts, instructions, and modifications to compile KLUSolve for WebAssembly.

The original KLUSolve code can be found in the `original-svn` branch or in [KLUSolve repository](https://sourceforge.net/projects/klusolve/).

As explicit in `LICENSE`, this repository uses the same license, LGPL 2.1 or later.

For the KLUSolve's original copyrights, please see `Readme_original.txt`.


## Requirements

The build and the tests were made in an linux based distribution.

- An C11 or later compiler.
- [Emscripten SDK](https://emscripten.org/index.html) v3.1.32 or higher.
- [CMake](https://cmake.org/) v3.25.2 or higher.

## How to build

An example of how to build can be found in `scripts/build_wasm.sh`

An example of usage can be found in `test_wasm/main.c` and how to build it can be found in `scripts/build_test_wasm.sh`.

## Copyrights

KLUSolve for WebAssembly, Copyright (c) 2023, Felipe M. dos S. Monteiro
All rights reserved.

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

All rights reserved.

KLUSolve for WebAssembly is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

KLUSolve for WebAssembly is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this Module; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA