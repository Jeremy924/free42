#include "core_main.h"
#include "main.h"

#include <algorithm>
#include <string.h>
#include <memory.h>
#include <rp/RP.hh>
#include <unistd.h>
#include <stdio.h>
#include <string>


const int frame_size = 132 * 4;
char frame[132 * 4];
bool frame_ready = false;
bool should_power_off = false;

int ann_shift = 0;
int ann_run = 0;

void shell_get_time_date(unsigned int*, unsigned int*, int*) {

}

void shell_powerdown() {
	should_power_off = true;
}


void shell_message(char const*) {

}


void shell_request_timeout3(int delay) {
	RP_DELAY_UNTIL(delay);
}

bool shell_wants_cpu() {
    return false;
}

void shell_delay(int delay) {
	RP_DELAY(delay);
}

const char* shell_number_format() {
    return ".,33";
}

int8 shell_random_seed() {
    return 0;
}
//0x20017ee0 0x900485fa

char shf_pixels_copy = 0;
bool was_shifted = false;

int out_of_bounds_counter = 0;
__attribute__((section(".RamFunc"))) void shell_blitter(char const* bits, int bytesperline, int x, int y, int width, int height) {

	for (int yi = y; yi < y + height; yi++) {
		for (int xi = x; xi < x + width; xi++) {
			unsigned int index1 = xi+(yi*2)/8*132;
			unsigned int index2 = xi+(yi*2+1)/8*132;

			if (index1 >= frame_size || index2 >= frame_size) {
				out_of_bounds_counter++;
				continue;
			}

			if (index1 == 131 || index2 == 131) continue;

            if (((int) bits[xi / 8 + yi * bytesperline] & (1 << (xi % 8))) == 0) {
                frame[index1] &= 0xff ^ (1 << ((yi*2) % 8));
                frame[index2] &= 0xff ^ (1 << ((yi*2+1) % 8));
            } else {
                frame[index1] |= (1 << ((yi*2+1) % 8));
                frame[index2] |= (1 << (yi*2 % 8));
            }
            //std::cout << (((int) bits[xi / 8 + yi * bytesperline] & (1 << (xi % 8))) == 0 ? ' ' : '#');

			//frame[xi + yi / 8 * 132] |= (bits[xi / 8 + yi * bytesperline] & (1 << (xi % 8)) == 0) ? 0: 1;//(1 << (yi%8));
		}
        //std::cout << std::endl;
	}

	int shift_index = 132 * 1 - 1;//132 * 4 - 1;
	int run_index = 132 * 2 - 1;

	if (ann_shift == 1) frame[shift_index] = 0xff;
	else frame[shift_index] = 0x00;
	if (ann_run == 1) frame[run_index] = 0xff;
	else frame[run_index] = 0x00;

	RP_DISPLAY_DRAW((char*)frame);
}

uint4 shell_milliseconds() {
	return RP_MILLIS();
}

void shell_beeper(int) {

}

uint8 shell_get_mem() {
	uint32_t psp;
	__asm volatile ("mov %0, sp" : "=r" (psp));

	uint32_t heap = (uint32_t) sbrk(0);

	return (uint8) psp - heap;
}

void shell_print(char const* content, int length, char const*, int, int, int, int, int) {
	write(STDOUT_FILENO, content, length);
}

void shell_check_for_copy() {
	char* buf = (char*) malloc(256);

	if (buf == 0) return;

	uint8_t result = RP_COPY(buf, 256);

	if (result == 0) core_paste(buf);

	free(buf);
}

const char* PLATFORM = "RP-42";
const char* shell_platform() {
    return PLATFORM;
}

int shell_date_format() {
    return 0;
}

bool shell_clk24() {
    return false;
}

bool shell_low_battery() {
    return false;
}

int skin_getchar() {
    return 0;
}


void skin_put_pixels(unsigned char const*) {

}

void skin_finish_image() {

}



void shell_annunciators(int updn, int shf, int prt, int run, int g, int rad) {
	ann_shift = shf;
	ann_run = run;

	core_repaint_display();
}
