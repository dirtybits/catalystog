# Catalyst 

Catalyst is an experimental digital currency and P2P payment system that allows users to send and receive payments to and from anyone in the world.

The following guide is based off of:
https://github.com/bcndev/bytecoin/blob/master/README.md

## Building on Linux 64-bit

All commands below are adapted for Ubuntu, other distributions may need a different command set.

### Building with standard options

Create directory `cstdev` somewhere and go there:
```
$> mkdir cstdev
$> cd cstdev
```

To go futher you have to have a number of packages and utilities. You need at least gcc 5.4.

* `build-essential` package:
    ```
    $cstdev> sudo apt-get install build-essential
    ```

* CMake (3.5 or newer):
    ```
    $cstdev> sudo apt-get install cmake
    $cstdev> cmake --version
    ```
    If version is too old, follow instructions on [the official site](https://cmake.org/download/).

* Boost (1.62 or newer):
    You'll need boost in the `cstdev` folder. We do not configure to use boost installed by `apt-get`, because it is sometimes updated without your control by installing some unrelated packages. Also some users reported crashes after `find_package` finds headers from one version of boost and libraries from different version, or if installed boost uses dynamic linking.
    ```
    $cstdev> wget -c 'http://sourceforge.net/projects/boost/files/boost/1.67.0/boost_1_67_0.tar.bz2/download'
    $cstdev> tar xf download
    $cstdev> rm download
    $cstdev> mv boost_1_67_0 boost
    $cstdev> cd boost
    $cstdev/boost> ./bootstrap.sh
    $cstdev/boost> ./b2 link=static -j 8 --build-dir=build64 --stagedir=stage
    cd ..
    ```

* OpenSSL (1.1.1 or newer):
    Install OpenSSL to `cstdev/openssl` folder. (In below commands use switch `linux-x86_64-clang` instead of `linux-x86_64` if using clang.)
    ```
    $cstdev> git clone https://github.com/openssl/openssl.git
    $cstdev> cd openssl
    $cstdev/openssl> ./Configure linux-x86_64 no-shared
    $cstdev/openssl> time make -j4
    $cstdev/openssl> cd ..
    ```

Git-clone (or git-pull) Catalyst source code in that folder:
```
$cstdev> git clone https://github.com/dirtybits/catalyst.git
```

Put LMDB source code in `cstdev` folder (source files are referenced via relative paths, so you do not need to separately build it):
```
$cstdev> git clone https://github.com/LMDB/lmdb.git
```

Create build directory inside catalyst, go there and run CMake and Make:
```
$cstdev> mkdir catalyst/build
$cstdev> cd catalyst/build
$cstdev/catalyst/build> cmake ..
$cstdev/catalyst/build> time make -j4
```

Check built binaries by running them from `../bin` folder
```
$cstdev/catalyst/build> ../bin/catalystd -v
```

### Building with specific options

Download amalgamated [SQLite 3](https://www.sqlite.org/download.html) and unpack it into `cstdev/sqlite` folder (source files are referenced via relative paths, so you do not need to separately build it).

Below are the commands which remove OpenSSL support and switch from LMDB to SQLite by providing options to CMake:

```
$cstdev> mkdir catalyst/build
$cstdev> cd catalyst/build
$cstdev/catalyst/build> cmake -DUSE_SSL=0 -DUSE_SQLITE=1 ..
$cstdev/catalyst/build> time make -j4
```
