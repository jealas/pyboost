# PyBoost - A Python wrapper for many Boost C++ libraries.

The [Boost C++](https://www.boost.org/) libraries contain high quality, high performance, industry hardened code
that can be useful in Python projects as well. The aim of this library is to expose as much of the Boost C++ libraries
as possible in a Pythonic fashion.

# Exposed Boost Libraries
- Circular buffer
- CRC
- Dynamic Bitset
- Multiprecision 

# Goals
- Feel like you are using Python code, not wrapped C++
    - Throw standard Python exceptions
    - Use the Python allocator
    - Play nicely with the Python GIL
- Expose Generic and specialized classes
- High quality modern C++ 11 Boost.Python wrapper code
- Minimize C++ wrapper duplication
- Handle special cases specially

# Installation Instructions

## Installation Dependencies

### Debian/Ubuntu
```sh
$ sudo apt install cmake python3-dev libboost-all-dev
```

### Arch Linux
```sh
$ sudo pacman -S cmake python3 boost
```

## Install PyBoost for Development
```sh
$ git clone --recursive git@github.com:jealas/pyboost.git
$ cd pyboost
$ pipenv install
```

# License

# Contributors
- Jesse Alas <jessealas94@gmail.com>
