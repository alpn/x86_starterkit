#include "x86.h"
#include "plat.h"
#include "print.h"

#define SYSTEM_TICKS_PER_SEC            100
#define X86_OK 0
#define APP_PRIORITY 16

#define IDLE_STACK_SIZE_BYTES 1024*16
#define APP_STACK_SIZE 1024*16 

static uint8_t idle_thread_stack[IDLE_STACK_SIZE_BYTES];
static uint8_t app_stack[APP_STACK_SIZE];

int x86_pc_init(void)
{
    gdt_install_flat();
    print("GDT installed\n");

    setup_idt();
    print("IDT installed\n");

    pit_init(SYSTEM_TICKS_PER_SEC);
    print("i8253 (PIT) initialized @%d hz\n", SYSTEM_TICKS_PER_SEC);

    pic_init();
    print("i8259 (PIC) initialized\n");

    irq_register_handler(0, sys_tick_handler);
    irq_register_handler(1, sys_key_handler);

    return X86_OK;
}

static void app_entry(uint32_t data);

void kernel_main (void)
{
    terminal_init();

    print("kernel_main()\n");

    if(X86_OK != x86_pc_init()) goto failure;

    x86_enable_int();
    app_entry(9);

failure:  

    print("[FAILURE]\n");
    x86_halt();
}

static void app_entry (uint32_t data)
{
    print_color("\n Hey x86!", COLOR_WHITE, COLOR_GREEN);

    print("\n\nPress Q to reboot\n");
    while(1);
}
