OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
    . = 0x80000000;

    .text.init : {
        KEEP(*(.text.init))
    }

    . = 0x80001000;
    .tohost : {
        KEEP(*(.tohost))
    }

    . = 0x80002000;
    .text : {
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata .rodata.*)
    }

    .data : {
        *(.sdata .sdata.*)
        *(.data .data.*)
    }

    .bss (NOLOAD) : {
        __bss_start = .;
        *(.sbss .sbss.*)
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end = .;
    }

    . = ALIGN(16);
    __global_pointer$ = MIN(__bss_start + 0x800, MAX(__bss_start, __bss_end - 0x800));
    __stack_top = 0x80100000;
    _end = .;
}
