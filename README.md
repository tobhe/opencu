# opencu - serial terminal emulator

This is a port of OpenBSD's serial terminal emulator [cu(1)](https://man.openbsd.org/cu.1) to Linux.

## Dependencies

Portable [cu(1)](https://man.openbsd.org/cu.1) is built using cmake. It requires a working C compiler, standard library and headers and libevent.

## Building from source

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Binary Packages

Pre-built binary packages for opencu are available in [Debian](https://tracker.debian.org/pkg/opencu), [Ubuntu](https://launchpad.net/ubuntu/+source/opencu)
and the [Arch User Repository (AUR)](https://aur.archlinux.org/packages/opencu). It is our hope that packagers take interest and help adapt opencu to
more distributions.

## Usage

To connect to the serial port at `/dev/ttyUSB0` with a baud rate of 115200 baud:

```
cu -l /dev/ttyUSB0 -s 115200
```

To close the connection and exit cu, enter `~.`. You can use `~?` to print a list of all supported commands.
