cmd_init/built-in.o :=  arm-cortexm3-uclinuxeabi-ld -EL    -r -o init/built-in.o init/main.o init/version.o init/mounts.o init/noinitramfs.o init/calibrate.o init/init_task.o 
