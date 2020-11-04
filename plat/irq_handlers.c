#include "plat.h"
#include "utils/print.h"

static void *irq_routines[16] = {0};

void irq_register_handler(int irq, void (*handler)(x86_iframe_t*)){

    if((NULL == handler) || (irq<0) || (irq>15)) return;
    irq_routines[irq] = handler;

}

void irq_unregister_handler(int irq){

    irq_routines[irq] = 0;

}

void handle_platform_irq(x86_iframe_t* frame){

    void (*handler)(x86_iframe_t* frame);
    uint32_t irq = frame->vector -32;

    handler = irq_routines[irq];

    if (handler){
        handler(frame);
    }

    if(irq==IRQ_PIT){
        return;
    }

    pic_send_EOI(irq);
}

void sys_tick_handler(x86_iframe_t* frame){

    const char ticks_anim_chars[] = {'-', '/', '|', '\\'};
    ++ticks;
    size_t ti = ticks%4;
    terminal_tick(ticks_anim_chars[ti]);

    pic_send_EOI(IRQ_PIT);

}

void sys_key_handler(x86_iframe_t* frame){

    // scan code https://wiki.osdev.org/PS/2_Keyboard
    uint8_t scan_code = in8(0x60);

    if(0x01 == scan_code){ // ESC - pressed
        plat_reboot();
    }

    if (0x81 > scan_code){
        terminal_keypress(scan_code);
    }
}
