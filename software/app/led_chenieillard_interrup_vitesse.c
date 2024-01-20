#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "sys/alt_sys_init.h"
#include "alt_types.h"
#include "io.h"
#include <unistd.h>

volatile int time=50000;
volatile int addr = 0x00;
volatile int val;

void blink_led();

static void irqhandler_btn(void *context);

static void irqhandler_switch(void *context);

static void irqhandler_btn(void *context)
{
    alt_printf("BUTTON INTERRUPT\n");
    val = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BTN_BASE);

    switch (val)
    {
    case 0b00:
        addr = 0x00;
        break;
    case 0b01:
        addr = 0x01;
        break;
    default:
        addr = 0x00;
        break;
    }
   IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BTN_BASE,0b11);
}

void blink_led()
{
        while (addr != 0x80)
        {
            addr = addr << 1;
            IOWR_ALTERA_AVALON_PIO_DATA(BLINKED_LED_BASE, addr);
            usleep(time);
        }
        while (addr != 0x01)
        {
            addr = addr >> 1;
            IOWR_ALTERA_AVALON_PIO_DATA(BLINKED_LED_BASE, addr);
            usleep(time);
        }
}

static void irqhandler_switch(void *context)
{
    int SW = 0;
    alt_printf("INTERRUPT switch\n");

    SW = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_BASE);

    time = SW * 20000 + 20000;

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_BASE,0b00001111);
}

int main()
{
    alt_printf("Dans le main\n");
    alt_printf("%x\n",time);

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSH_BTN_BASE, 0b11);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCH_BASE, 0b00001111);

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BTN_BASE, 0b11);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_BASE, 0b00001111);

    alt_ic_isr_register(SWITCH_IRQ_INTERRUPT_CONTROLLER_ID, SWITCH_IRQ, irqhandler_switch, NULL, NULL);
    alt_ic_isr_register(PUSH_BTN_IRQ_INTERRUPT_CONTROLLER_ID, PUSH_BTN_IRQ, irqhandler_btn, NULL, NULL);

    while (1)
    {
        blink_led();
    }
    return 0;
}
