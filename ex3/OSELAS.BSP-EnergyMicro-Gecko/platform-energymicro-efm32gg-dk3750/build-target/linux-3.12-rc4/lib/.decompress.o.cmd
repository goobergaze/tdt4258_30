cmd_lib/decompress.o := arm-cortexm3-uclinuxeabi-gcc -Wp,-MD,lib/.decompress.o.d  -nostdinc -isystem /opt/ex3/OSELAS.Toolchain-2012.12.0/arm-cortexm3-uclinuxeabi/gcc-4.7.2-uclibc-0.9.33.2-binutils-2.22-kernel-3.6-sanitized/lib/gcc/arm-cortexm3-uclinuxeabi/4.7.2/include -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi -Iinclude/generated/uapi -include /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-efm32/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -fno-dwarf2-cfi-asm -mno-unaligned-access -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -mthumb -Wa,-mimplicit-it=always -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-m -Wa,-march=armv7-m -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(decompress)"  -D"KBUILD_MODNAME=KBUILD_STR(decompress)" -c -o lib/decompress.o lib/decompress.c

source_lib/decompress.o := lib/decompress.c

deps_lib/decompress.o := \
    $(wildcard include/config/decompress/gzip.h) \
    $(wildcard include/config/decompress/bzip2.h) \
    $(wildcard include/config/decompress/lzma.h) \
    $(wildcard include/config/decompress/xz.h) \
    $(wildcard include/config/decompress/lzo.h) \
    $(wildcard include/config/decompress/lz4.h) \
  include/linux/decompress/generic.h \
  include/linux/decompress/bunzip2.h \
  include/linux/decompress/unlzma.h \
  include/linux/decompress/unxz.h \
  include/linux/decompress/inflate.h \
  include/linux/decompress/unlzo.h \
  include/linux/decompress/unlz4.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi/linux/posix_types.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi/asm/posix_types.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi/asm-generic/posix_types.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /opt/ex3/OSELAS.Toolchain-2012.12.0/arm-cortexm3-uclinuxeabi/gcc-4.7.2-uclibc-0.9.33.2-binutils-2.22-kernel-3.6-sanitized/lib/gcc/arm-cortexm3-uclinuxeabi/4.7.2/include/stdarg.h \
  include/uapi/linux/string.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/string.h \
  include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/modules.h) \

lib/decompress.o: $(deps_lib/decompress.o)

$(deps_lib/decompress.o):
