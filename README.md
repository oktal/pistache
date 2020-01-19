

# Pistache
[![N|Solid](http://pistache.io/assets/images/logo.png)](https://www.github.com/oktal/pistache)
[![Travis Build Status](https://travis-ci.org/oktal/pistache.svg?branch=master)](https://travis-ci.org/oktal/pistache)

Pistache is a modern and elegant HTTP and REST framework for C++. It is entirely written in pure-C++14 and provides a clear and pleasant API. 

# Documentation

We are still looking for a volunteer to document fully the API. In the mean time, partial documentation is available at [http://pistache.io](http://pistache.io). If you are interested in helping with this, please open an issue ticket.

# Contributing

Pistache is released under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0). Contributors are welcome!

Pistache was originally created by Mathieu Stefani, but he is no longer actively maintaining Pistache. A team of volunteers has taken over. To reach the original maintainer, drop a private message to `@octal` in [cpplang Slack channel](https://cpplang.now.sh/).

For those that prefer IRC over Slack, the rag-tag crew of maintainers idle in `#pistache` on Freenode. Please come and join us!

The [Launchpad Team](https://launchpad.net/~pistache+team) administers the daily and stable Ubuntu pre-compiled packages.

# Precompiled Packages
If you have no need to modify the Pistache source, you are strongly recommended to use precompiled packages for your distribution. This will save you time.

## Debian and Ubuntu
We have submitted a [Request for Packaging](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=929593) downstream to Debian. Once we have an official Debian package maintainer intimately familiar with the [Debian Policy Manual](https://www.debian.org/doc/debian-policy/), we can expect to eventually see it become available in Debian and all derivatives (e.g. Ubuntu and many others).

But until then currently Pistache has partially compliant upstream Debianization. Our long term goal is to have our source package properly Debianized downstream by a Debian Policy Manual SME. In the mean time consider using our PPAs to avoid having to build from source.

### Supported Architectures
Currently Pistache is built and tested on a number of [architectures](https://wiki.debian.org/SupportedArchitectures). Some of these are suitable for desktop or server use and others for embedded environments. As of this writing we do not currently have any MIPS related packages that have been either built or tested. The `ppc64el` builds are occasionally tested on POWER9 hardware, courtesy of IBM.

- amd64
- arm64
- armhf
- i386
- ppc64el
- s390x


### Ubuntu PPA (Unstable)
The project builds [daily unstable snapshots](https://launchpad.net/~pistache+team/+archive/ubuntu/unstable) in a separate unstable PPA. To use it, run the following:

```console
$ sudo add-apt-repository ppa:pistache+team/unstable
$ sudo apt update
$ sudo apt install libpistache-dev
```

### Ubuntu PPA (Stable)
Currently there are no stable release of Pistache published into the [stable](https://launchpad.net/~pistache+team/+archive/ubuntu/stable) PPA. However, when that time comes, run the following to install a stable package:

```console
$ sudo add-apt-repository ppa:pistache+team/stable
$ sudo apt update
$ sudo apt install libpistache-dev
```

## Use via pkg-config

If you would like to automatically have your project's build environment use the appropriate compiler and linker build flags, [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/) can greatly simplify things. It is the portable international _de facto_ standard for determining build flags. The `libpistache-dev` package includes a pkg-config manifest.

To use with the GNU Autotools, as an example, include the following snippet in your project's `configure.ac`:

```

    # Pistache...
    PKG_CHECK_MODULES(
        [libpistache], [libpistache >= 0.0.2], [],
        [AC_MSG_ERROR([libpistache >= 0.0.2 missing...])])
    YOURPROJECT_CXXFLAGS="$YOURPROJECT_CXXFLAGS $libpistache_CFLAGS"
    YOURPROJECT_LIBS="$YOURPROJECT_LIBS $libpistache_LIBS"
    
```

# Building from source

To download the latest available release, clone the repository over github.

```console
    git clone https://github.com/oktal/pistache.git
```

Then, init the submodules:

```console
    git submodule update --init
```

Now, compile the sources:

```console
    cd pistache
    mkdir -p {build,prefix}
    cd build
    cmake -G "Unix Makefiles" \
        -DCMAKE_BUILD_TYPE=Release \
        -DPISTACHE_BUILD_EXAMPLES=true \
        -DPISTACHE_BUILD_TESTS=true \
        -DPISTACHE_BUILD_DOCS=false \
        -DPISTACHE_USE_SSL=true \
        -DCMAKE_INSTALL_PREFIX=$PWD/../prefix \
        ../
    make -j
    make install
```

If you chose to build the examples, then perform the following to build the examples.
```console
    cd examples
    make -j
```

Optionally, you can also build and run the tests (tests require the examples):

```console
    cmake -G "Unix Makefiles" -DPISTACHE_BUILD_EXAMPLES=true -DPISTACHE_BUILD_TESTS=true ..
    make test test_memcheck
```

Be patient, async_test can take some time before completing. And that's it, now you can start playing with your newly installed Pistache framework.

Some other CMAKE defines:

| Option                        | Default     | Description                                    |
|-------------------------------|-------------|------------------------------------------------|
| PISTACHE_BUILD_EXAMPLES       | False       | Build all of the example apps                  |
| PISTACHE_BUILD_TESTS          | False       | Build all of the unit tests                    |
| PISTACHE_ENABLE_NETWORK_TESTS | True        | Run unit tests requiring remote network access |
| PISTACHE_USE_SSL              | False       | Build server with SSL support                  |

# Example

## Hello World (server)

```cpp
#include <pistache/endpoint.h>

using namespace Pistache;

struct HelloHandler : public Http::Handler {
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request&, Http::ResponseWriter writer) override{
    writer.send(Http::Code::Ok, "Hello, World!");
  }
};

int main() {
  Http::listenAndServe<HelloHandler>(Pistache::Address("*:9080"));
}
```

