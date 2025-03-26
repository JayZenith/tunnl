The Tunnl Language 
=========================

The Tunnl Lanauge is a work-in-progress, dynamically-typed scripting language, simple and easy to use. 



Building
---

Just run CMake like this:

```sh
# Create build directory
mdkir build && cd build

# Configure CMake in build dir
cmake <root-dir>
```

and then build 

```sh
 cmake --build .
```

Usage
---

Run a program using the following :

```sh
# in build dir
tunnl <program>
```

Or to activate the shell prompt just run:
```sh
# in build dir
tunnl
```


Project Structure
* include/ - Header Files
* src/ - Source Files
* tests/ - Test files 