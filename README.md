_libac-safe_
============
This proof-of-concept library makes POSIX asynchronous cancellability safe to use, although it will
still cause resource leaks without a carefully-crafted cleanup handler.

License
-------
The entire contents and history of this repository are distributed under the following license:
```
Copyright 2022 Carnegie Mellon University

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

Building _libac-safe_
---------------------
 1. `$ rmdir libgotcha`
 1. `$ ln -s ../path/to/libgotcha`
 1. `$ make -Clibgotcha libgotcha.a libgotcha.mk`
 1. `$ make`

Using _libac-safe_
------------------
Either link your program against `libac-safe.so` or request it at load time via `$LD_PRELOAD`.
