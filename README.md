C++ Simulated Fare Quote System Library
=======================================

# Summary
SimFQT aims at providing a clean API and a simple implementation, as
a C++ library, of a Travel-oriented fare engine. It corresponds to
the simulated version of the real-world Fare Quote or pricing system.

SimFQT makes an extensive use of existing open-source libraries for
increased functionality, speed and accuracy. In particular the
Boost (C++ Standard Extensions: http://www.boost.org) library is used.

SimFQT is the one of the components of the Travel Market Simulator
(https://travel-sim.org). However, it may be used in a
stand-alone mode.

# Installation

## On Fedora/CentOS/RedHat distribution
Just use DNF:
```bash
$ dnf -y install simfqt-devel simfqt-doc
```

You can also get the RPM packages (which may work on Linux
distributions like Novel Suse and Mandriva) from the Fedora repository
(_e.g._, for Fedora 32,
https://fr2.rpmfind.net/linux/RPM/fedora/32/x86_64/)


## Building the library and test binary from Git repository
The Git repository may be cloned as following:
```bash
$ git clone git@github.com:airsim/simfqt.git simfqtgit # through SSH
$ git clone https://github.com/airsim/simfqt.git # if the firewall filters SSH
$ cd simfqtgit
```

Then, you need the following packages (Fedora/RedHat/CentOS names here, 
but names may vary according to distributions):
* cmake
* gcc-c++
* boost-devel / libboost-dev
* python-devel / python-dev
* gettext-devel / gettext-dev
* sqlite3-devel / libsqlite3-dev
* readline-devel / readline-dev
* ncurses-devel
* soci-mysql-devel, soci-sqlite3-devel
* stdair-devel / libstdair-dev
* sevmgr-devel / libsevmgr-dev
* doxygen, ghostscript, graphviz
* tetex-latex (optional)
* rpm-build (optional)


## Building the library and test binary from the tarball
The latest stable source tarball (`simfqt*.tar.gz` or `.bz2`) can be found here:
https://github.com/airsim/simfqt/releases

To customise the following to your environment, you can alter the path
to the installation directory:
```bash
export INSTALL_BASEDIR="${HOME}/dev/deliveries"
export SFQ_VER="1.00.6"
if [ -d /usr/lib64 ]; then LIBSUFFIX="64"; fi
export LIBSUFFIX_4_CMAKE="-DLIB_SUFFIX=$LIBSUFFIX"
```

Then, as usual:
* To configure the project, type something like:
```bash
  mkdir build && cd build
  cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_BASEDIR}/simfqt-$SFQ_VER \
   -DWITH_STDAIR_PREFIX=${INSTALL_BASEDIR}/stdair-stable \
   -DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_TEST:BOOL=ON -DINSTALL_DOC:BOOL=ON \
   -DRUN_GCOV:BOOL=OFF ${LIBSUFFIX_4_CMAKE} ..
```
* To build the project, type:
```bash
  make
```
* To test the project, type:
```bash
  make check
```
* To install the library (`libsimfqt*.so*`) and the binary (`simfqt`),
  just type:
```bash
  make install
  cd ${INSTALL_BASEDIR}
  rm -f simfqt-stable && ln -s simfqt-$SFQ_VER simfqt-stable
  cd -
```
* To package the source files, type:
```bash
  make dist
```
* To package the binary and the (HTML and PDF) documentation:
```bash
  make package
```
* To browse the (just installed, if enabled) HTML documentation:
```bash
  midori file://${INSTALL_BASEDIR}/simfqt-$SFQ_VER/share/doc/simfqt/html/index.html
```
* To browse the (just installed, if enabled) PDF documentation:
```bash
  evince ${INSTALL_BASEDIR}/simfqt-$SFQ_VER/share/doc/simfqt/html/refman.pdf
```
* To run the local binary version:
```bash
  ./simfqt/simfqt -b
```
* To run the installed version:
```bash
  ${INSTALL_BASEDIR}/simfqt-$SFQ_VER/bin/simfqt -b
```

Denis Arnaud (June 2015)

