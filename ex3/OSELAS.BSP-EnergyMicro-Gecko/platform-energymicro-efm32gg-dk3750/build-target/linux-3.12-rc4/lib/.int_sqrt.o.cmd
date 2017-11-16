cmd_lib/int_sqrt.o := arm-cortexm3-uclinuxeabi-gcc -Wp,-MD,lib/.int_sqrt.o.d  -nostdinc -isystem /opt/ex3/OSELAS.Toolchain-2012.12.0/arm-cortexm3-uclinuxeabi/gcc-4.7.2-uclibc-0.9.33.2-binutils-2.22-kernel-3.6-sanitized/lib/gcc/arm-cortexm3-uclinuxeabi/4.7.2/include -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi -Iinclude/generated/uapi -include /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-efm32/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -fno-dwarf2-cfi-asm -mno-unaligned-access -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -mthumb -Wa,-mimplicit-it=always -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-m -Wa,-march=armv7-m -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(int_sqrt)"  -D"KBUILD_MODNAME=KBUILD_STR(int_sqrt)" -c -o lib/int_sqrt.o lib/int_sqrt.c

source_lib/int_sqrt.o := lib/int_sqrt.c

deps_lib/int_sqrt.o := \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /opt/ex3/OSELAS.Toolchain-2012.12.0/arm-cortexm3-uclinuxeabi/gcc-4.7.2-uclibc-0.9.33.2-binutils-2.22-kernel-3.6-sanitized/lib/gcc/arm-cortexm3-uclinuxeabi/4.7.2/include/stdarg.h \
  include/linux/linkage.h \
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
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/linkage.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
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
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi/asm/posix_types.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi/asm-generic/posix_types.h \
  include/linux/bitops.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/irqflags.h \
    $(wildcard include/config/cpu/v7m.h) \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/hwcap.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi/asm/hwcap.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/uapi/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  include/uapi/linux/swab.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/swab.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/uapi/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
  include/linux/kern_levels.h \
  include/linux/dynamic_debug.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/uapi/linux/string.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/arch/arm/include/asm/string.h \
  include/linux/errno.h \
  include/uapi/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi/asm-generic/errno.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi/asm-generic/errno-base.h \
  include/uapi/linux/kernel.h \
  /home/tdt4258/Desktop/support_files/ex3/OSELAS.BSP-EnergyMicro-Gecko/platform-energymicro-efm32gg-dk3750/build-target/linux-3.12-rc4/include/uapi/linux/sysinfo.h \

lib/int_sqrt.o: $(deps_lib/int_sqrt.o)

$(deps_lib/int_sqrt.o):
