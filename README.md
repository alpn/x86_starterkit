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
* Qemu

Installing GCC cross compiler can be frustrating. Fortunately, there is a tool that helps ease up the installation. Check out - https://github.com/lordmilko/i686-elf-tools

Build / Run
---
```bash
    git clone https://github.com/alpn/x86_starterkit
    cd x86_starterkit
    ./build.sh
    qemu-system-i386 -cdrom bootable.iso

```

# Troubleshooting ⚙️
## (1) Can't find command i686-elf-gcc or i686-elf-objcopy
- This is caused by incorrect installation of GCC Cross Compiler. If you've compiled / downloaded the compiler alongside other prerequisites in some other directory you need to add the compiler to the path. (https://stackoverflow.com/questions/22668565/how-to-add-cross-compiler-to-the-path)

```
export PATH=/home/me/gcc_cross_compiler_location/output/linux/bin/:$PATH
export CROSS_COMPILE=i686-elf-
```

## (2) Qemu won't load the grub / boot from the ISO file.
- It was most likely that this was caused because the ISO file is not generated properly. Try removing build/ directory and the ISO file before re-running the build script. Check the console output for any errors. A proper output that generates a bootable ISO file should look something like this:

```Drive current: -outdev 'stdio:bootable.iso'
Media current: stdio file, overwriteable
Media status : is blank
Media summary: 0 sessions, 0 data blocks, 0 data,  216g free
Added to ISO image: directory '/'='/tmp/grub.Mpy9qk'
xorriso : UPDATE :     290 files added in 1 seconds
Added to ISO image: directory '/'='/home/dante/x86_os/build/run/iso'
xorriso : UPDATE :     294 files added in 1 seconds
xorriso : NOTE : Copying to System Area: 512 bytes from file '/usr/lib/grub/i386-pc/boot_hybrid.img'
ISO image produced: 2502 sectors
Written to medium : 2502 sectors at LBA 0
Writing to 'stdio:bootable.iso' completed successfully.
```

TODO
---
- [ ] add comprehensive documentation

Thanks
---
* The incredible [OSDev.org](https://wiki.osdev.org/) wiki
* [@travisg](https://github.com/travisg)'s [LK](https://github.com/littlekernel/lk) kernel
