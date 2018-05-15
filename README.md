# Catalyst
Catalyst (CST) is a new cryptocurrency based on CryptoNote/Bytecoin protocols. A coin for The People.

## THIS IS A WORK IN PROGRESS, expect errors to start popping up. Thank you for your patience.

## Building Catalyst on *nix

Make sure you have current versions of gcc, cmake, make, and boost. 
```
$ git clone https://github/dirtybits/catalyst.git
$ cd catalyst/
$ make
```

Building on Linux 64-bit
All commands below are adapted for Ubuntu, other distributions may need another command set.

Building with standard options
Create directory bcndev somewhere and go there:
`
$> mkdir dirtybits
$> cd dirtybits
`
To go futher you have to have a number of packages and utilities.

build-essential package:
`
$> sudo apt-get install build-essential
`
CMake (3.5 or newer):
`
$> sudo apt-get install cmake 
$> cmake --version
`
If version is too old, follow instructions on the official site.

Boost (1.62 or newer):

$> sudo apt-get install libboost-all-dev
$> cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
If version is too old, download boost from boost.org, unpack it into a folder inside bcndev and rename it from boost_1_66_0 or similar to just boost Build boost

$> cd boost
$dirtybits/boost> ./bootstrap.sh
$dirtybits/boost> ./b2 link=static -j 8 --build-dir=build64 --stagedir=stage
cd ..
Git-clone (or git-pull) Catalyst source code in that folder:

$dirtybits> git clone https://github.com/dirtybits/catalyst.git
Put LMDB source code in bcndev folder (source files are referenced via relative paths, so you do not need to separately build it):

$dirtybits> git clone https://github.com/LMDB/lmdb.git
Create build directory inside catalyst, go there and run CMake and Make:

$dirtybits> mkdir catalyst/build
$dirtybits> cd catalyst/build
$dirtybits/catalyst/build> cmake -DUSE_SSL=0 ..
$dirtybits/catalyst/build> time make -j4
Check built binaries by running them from ../bin folder

$dirtybits/catalyst/build> ../bin/catalystd -v
