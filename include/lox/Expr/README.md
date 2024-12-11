C++ implementation of Lox 
=========================

Writing the Lox Interpreter from [Crafting Interpreters book](http://craftinginterpreters.com/) by
Bob Nystrom and writing Lox interpreter in C++. Will look to do this in Rust soon after. 

Chapters complete
---

4. Scanning
5. Represening code
6. Parsing Expressions
7. Evaluating Expressions

Building
---

Just run CMake like this:

```sh
# in build dir
cmake <src-dir>
```

and then

```sh
cmake --build . --target lox
```


Usage
---

Run a simple example:

```sh
lox examples/test.lox
```

