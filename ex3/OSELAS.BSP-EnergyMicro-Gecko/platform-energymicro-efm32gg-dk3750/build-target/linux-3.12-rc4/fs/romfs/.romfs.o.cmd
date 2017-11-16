cmd_fs/romfs/romfs.o := arm-cortexm3-uclinuxeabi-ld -EL    -r -o fs/romfs/romfs.o fs/romfs/storage.o fs/romfs/super.o fs/romfs/mmap-nommu.o 
