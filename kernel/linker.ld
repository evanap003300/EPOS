ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS { 
    /* Place the code at 1MB (typical for kernel loading) */
    . = 1M;

    .text : {
        *(.text)  /* Place all .text sections here (code) */
    }

    .rodata : {
        *(.rodata)  /* Read-only data */
    }

    .data : {
        *(.data)  /* Initialized global/static variables */
    }

    .bss : {
            bss_start = .;
        *(COMMON)
        *(.bss)
        bss_end = .;
    }
}
