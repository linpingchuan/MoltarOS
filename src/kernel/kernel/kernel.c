#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define __IS_MOLTAROS 1

#include <include/vga.h>
#include <include/gdt.h>
#include <include/idt.h>
#include <include/timer.h>
#include <include/rtc.h>

const char *msg = "When are we getting ready to leave?";

size_t ticks_x, ticks_y, time_x, time_y;

void kernel_init() {
	vga_init();
	gdt_init();
	idt_init();
}

static void kernel_tick(struct registers *regs) {
	(void) regs;
	static uint32_t ticks = 0;

	vga_set_x(ticks_x);
	vga_set_y(ticks_y);
	printf("%d", ++ticks);

	if(ticks % 1000 == 0) {
		vga_set_x(time_x);
		vga_set_y(time_y);
		rtc_print();
		vga_putc(' ');
	}
}

void kernel_main() {
	printf("Operating System: MoltarOS\nKernel: Moltar\nVersion: 0.001a\nTime: ");
	time_x = vga_get_x();
	time_y = vga_get_y();
	rtc_print();

	printf("\nTesting Clock at 1KHz...\nTicks: 0");
	ticks_x = vga_get_x() - 1;
	ticks_y = vga_get_y();

	init_timer(1000, kernel_tick);

	asm volatile ("sti");

	while(true)
		asm volatile ("hlt");
}