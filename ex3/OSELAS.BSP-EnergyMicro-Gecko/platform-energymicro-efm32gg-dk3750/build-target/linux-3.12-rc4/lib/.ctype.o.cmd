cmd_lib/ctype.o := arm-cortexm3-uclinuxeabi-gcc -Wp,-MD,lib/.ctype.o.d  -nostdinc -isystem /opt/ex3/OSELAS.Toolchain-2012.12.0/arm-cortexm3-uclinuxeabi/gcc-4.7.2-uclibc-0.9.33.2-binutils-2.22-kernel-3.6-sanitized/lib/gcc/arm-cortexm3-uclinuxeabi/4.7.2/include -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi -Iinclude/generated/uapi -include /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-efm32/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -fno-dwarf2-cfi-asm -mno-unaligned-access -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -mthumb -Wa,-mimplicit-it=always -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-m -Wa,-march=armv7-m -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ctype)"  -D"KBUILD_MODNAME=KBUILD_STR(ctype)" -c -o lib/ctype.o lib/ctype.c

source_lib/ctype.o := lib/ctype.c

deps_lib/ctype.o := \
  include/linux/ctype.h \
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
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \

lib/ctype.o: $(deps_lib/ctype.o)

$(deps_lib/ctype.o):
