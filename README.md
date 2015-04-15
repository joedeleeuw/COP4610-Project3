 COP4610-Project3
================
## A user-space program that access' and manipluates a FAT32 file system image. 

+ The program consists of a main file called fatmod.cpp which handles all the commands and delegates them accordingly.
 - filesystem.cpp takes care of the majority of the parsing, and other command functionality(i.e. ls, cd).
+ The utility was written entirely in C and no pre-existing kernel, or userspace code was utilized.
+ The utility is robust, and leaves the file system in a consistent state. 


