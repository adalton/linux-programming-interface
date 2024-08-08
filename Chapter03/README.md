# Exercise
1. When using the Linux-specific `reboot()` system call to reboot the system,
   the second argument, _magic2_, must be specified as one of a set of magic
   numbers (e.g., `LINUX_REBOOT_MAGIC2`).  What is the significance of these
   numbers? (Converting them to hexadecimal provides a clue.)

   Looking in `/usr/include/linux` for header files containing
   `LINUX_REBOOT_MAGIC` I see:

   ```
   $ find /usr/include/linux -type f -name '*.h' | xargs grep LINUX_REBOOT_MAGIC
   /usr/include/linux/reboot.h:#define LINUX_REBOOT_MAGIC1   0xfee1dead
   /usr/include/linux/reboot.h:#define LINUX_REBOOT_MAGIC2    672274793
   /usr/include/linux/reboot.h:#define LINUX_REBOOT_MAGIC2A    85072278
   /usr/include/linux/reboot.h:#define LINUX_REBOOT_MAGIC2B   369367448
   /usr/include/linux/reboot.h:#define LINUX_REBOOT_MAGIC2C   537993216
   ```

   Converting those values to hex, I see:
   ```
   $ for i in 672274793 85072278 369367448 537993216; do printf "%9d: 0x%08x\n" $i $i; done
   672274793: 0x28121969
    85072278: 0x05121996
   369367448: 0x16041998
   537993216: 0x20112000
   ```

   Those values look suspiciously like dates.  Some online research indicates
   that those dates correspond with:

   * Linus Torvalds' birthday is 28 December 1969 (`LINUX_REBOOT_MAGIC2`)
   * Patricia Miranda, Linus’ first daughter's birthday is 12 May 1996 (`LINUX_REBOOT_MAGIC2A`)
   * Daniela Yolanda, Linus’ second daughter's birthday is 16 April 1998 (`LINUX_REBOOT_MAGIC2B`)
   * Celeste Amanda, Linus’ third daughter's birthday is 20 November 2000 (`LINUX_REBOOT_MAGIC2C`)
