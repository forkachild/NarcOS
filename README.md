# NarcOS - A bare metal ultralight kernel for Raspberry Pi 3 (BCM2837)

## Introduction
The Raspberry Pi 3 is the newest and most powerful "Ras Pi" yet. It is a simple credit card sized ARM based computer capable of HDMI & Composite video output. It features a **1.2GHz Quad Core CPU** with **1GB of RAM** and a mighty **VideoCore IV GPU**. It also boasts of **4 USB 2.0 High Speed Ports**, an **Ethernet Port**, **802.11 b/g/n WiFi Radio** and **Bluetooth**.

Most use a Raspbian or Ubuntu image in an SD card to code in a Linux environment. You get Python out of the box on the terminal, what more does one need right?

There are a few ones still out there who want to go *bare-metal* on the *BCM2837 SoC*. What is bare-metal? In short, bare-metal is the hardware without an OS. All the code goes linux independent. No taken-for-granted libraries in C. Forget Python and all. Each and every movement of the processor is fully in your control, and in turn you have to compromise on having a secure, OS environment. If this sounds scary, then I think maybe I should tell you, it is what the dare devil programmers do.

## First things first
Since it is compiled using GCC for ARM `arm-none-eabi-gcc`, it is machine independent. I personally built this on macOS. Anyhow, I'm gonna give the basic outline for ease of install

 - Goto [GNU ARM Embedded Toolchain Download](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) and grab the appropriate archive.
 - Open a terminal and `cd` to the Downloads folder where the tar was downloaded.
 - You need [MinGW](https://sourceforge.net/projects/mingw/files/latest/download?source=files) if on Windows.
 - Use `sudo tar -xvf gcc-arm-none-eabi-XXXXX.tar.bz2 -C /usr/local/gcc-arm-none-eabi` to untar the archive
 - Append `/usr/local/gcc-arm-none-eabi/bin` to the `$PATH` variable for your shell. I `echo`ed the line into my `~/.bash_profile` for a permanent change. Use `source ~/.bash_profile` for `$PATH` update in your current shell immediately.
 - Run `arm-none-eabi-gcc --version` on your shell. If it outputs a valid version, then congratulations, you have successfully installed a working toolchain for ARM.
 - Clone this archive into a folder. I use `/Documents/Experiments/ARM/NarcOS`.

## A little more preparation
If you already have an SD card with Raspbian or any other flavor of Linux installed then it already has the `kernel7.img` `config.txt` `bootcode.bin` and `start.elf` files in them. For our kernel to work, you simply need to replace the `kernel7.img` with our own `kernel7.img`.  

Unfortunately if you don't, nothing to worry about. Download the files from [here](https://github.com/raspberrypi/firmware/tree/master/boot). Format the SD card with a FAT partition and place these files there.

You can modify the `oscopy.sh` to compile, copy and unmount the SD card.

## On the road to bare-metal-ay
If you have completed all the steps above successfully, most probably your code will run. Currently it produces a weird pattern through HDMI and can blink an LED through GPIO18. It is a pretty basic example. It is under development.