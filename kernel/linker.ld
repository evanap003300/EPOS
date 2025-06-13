ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS { 
    /* Place the code at 1MB */
    . = 1M;

    .text : {
        *(.text*)  /* Place all .text sections here (code) */
    }

    .rodata : {
        *(.rodata*)  /* Read-only data */
    }

    .data : {
        *(.data*)  /* Initialized global/static variables */
    }

    .bss : {
        *(.bss*)
        *(COMMON)
    }
}
