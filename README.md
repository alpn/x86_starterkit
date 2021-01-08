👷🏻‍♂️ x86 Starter Kit
===

What
---
This repo is meant to serve as an easy starting point for newcomer OS/Kernel development enthusiasts.
It includes everything you need to kick off a freestanding bootable `C` main, including support for basic stuff like printing to the terminnal and getting user input.

![](https://github.com/alpn/x86_starterkit/raw/master/.media/qemu_boot.gif)

Prerequisites
---
* GCC cross compiler - https://wiki.osdev.org/GCC_Cross-Compiler
* qemu

Build / Run
---
```bash
    git clone https://github.com/alpn/x86_starterkit
    cd x86_starterkit
    ./build.sh
    qemu-system-i386 -cdrom bootable.iso

```

TODO
---
- [ ] add comprehensive documentation

Thanks
---
* The incredible [OSDev.org](https://wiki.osdev.org/) wiki
* [@travisg](https://github.com/travisg)'s [LK](https://github.com/littlekernel/lk) kernel
