# osdev
Developing a tiny OS for a school project. The OS (codename **aba**) is written in *C* and *32-bit NASM*
## Installing
### Prerequisites
*The OS is tested only on Linux Mint 19*.

To run OS, you need to have *bochs*, *make*, *genisoimage* and *nasm* installed.
```
sudo apt-get install bochs make genisoimage nasm
```
Also [i686 GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) must be installed in *$HOME/opt/cross*

### Running
To compile and run OS, you need to execute the following commands:
```
cd build && make run
```
Then the bochs window will appear. If you type *c*, the OS will start to load.
