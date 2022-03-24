Automatic resource cleanup minimal example
==========================================
This branch contains GDB scripts to inject panics on arbitrary instruction boundaries, the frontend
`table` shell script that shows how many objects are allocated and leaked after various numbers of
instructions have executed, the `epilogue.s` workaround for epilogue unwinding, and a `minimal.rs`
program for testing on.

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
