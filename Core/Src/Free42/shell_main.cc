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
		}
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

	for (volatile int i = 0; i < 10000000; i++);

	return (uint8) psp - heap;
}


#define PRINT_WIDTH 166
#define PRINT_FRAMES 16

struct PrintFrame {
	uint8_t* print_data;
	uint8_t  actual_width;
	uint8_t  x_offset;
	uint8_t  height;
	int bytesperline;
};

struct PrintFrame print_frames[PRINT_FRAMES];
unsigned int frame_offset = 0;
bool is_first = true;

void initializePrintFrames() {
	for (int i = 0; i < PRINT_FRAMES; i++) {
		print_frames[i].print_data = 0;
	}

	is_first = false;
}

//uint8_t* print_frames[PRINT_FRAMES];
//uint8_t print_page = 255;
// Store output by blitting, then snapshot the full screen
void shell_print(const char *text, int length,
                 const char *bits, int bytesperline,
                 int x, int y, int width, int height)
{
    (void)text; (void)length;
    if (!bits || bytesperline <= 0 || width <= 0 || height <= 0) return;

    if (is_first) initializePrintFrames();

    struct PrintFrame* frame = &print_frames[frame_offset++];
    if (frame_offset >= PRINT_FRAMES) frame_offset = 0;

    // if this frame was in use, then make sure to de allocate the data first
    if (frame->print_data != 0) free(frame->print_data);

    // save data to new frame
    frame->print_data = (uint8_t*) malloc(bytesperline * height);
    if (frame->print_data == 0) return;
    memcpy(frame->print_data, bits, bytesperline * height);

    frame->x_offset = x;
    frame->height = height;
    frame->actual_width = width;
    frame->bytesperline = bytesperline;

    //printf("frame offset: %d, xoffset: %d, height: %d, width: %d\n", frame_offset - 1, frame->x_offset, frame->height, frame->actual_width);

    /*
    if (print_page == 255) {
    	print_frames[0] = (uint8_t*) malloc(PRINT_WIDTH);

    	if (print_page != 0)
    		print_page = 0;
    	else print_page = 255;
    }

    if (print_page == 255) return;

    int required_frames = height / 8;
    if (required_frames * 8 < height) required_frames++;

    uint8_t* target_frames[required_frames];

    for (int i = 0; i < required_frames; i++) {
    	int index = print_page + (required_frames - 1) - i;
    	if (index >= PRINT_FRAMES) {
    		index = 0;
    	}

    	if (print_page >= index) target_frames[i] = NULL; // don't overlap the start
    	else {
    		if (print_frames[index] == NULL) print_frames[index] = (uint8_t*) malloc(PRINT_WIDTH);
    		target_frames[i] = print_frames[index];
    	}

    	memset((void*) target_frames[i], 0, PRINT_WIDTH);
    }

	for (int yi = 0; yi < height; yi++) {
		for (int xi = x; xi < x + width; xi++) {
			uint8_t* target_frame = target_frames[yi / 8];

			if (((int) bits[xi / 8 + yi * bytesperline] & (1 << (xi % 8))) != 0) {
				target_frame[xi] |= (1 << yi % 8);
			}
		}
	}*/
}

void print_frame_to_screen(struct PrintFrame* pf, unsigned int yoffset_from_bottom)
{
    int y0 = 31 - (int)yoffset_from_bottom - (int)pf->height; // destination top y

    for (int sy = 0; sy < pf->height; sy++) {
        int dy = y0 + sy;                          // destination y
        if (dy < 0) continue;

        for (int sx = 0; sx < pf->actual_width; sx++) {
            int dx = pf->x_offset + sx;            // destination x
            if (dx < 0) continue;

            unsigned int index = dx + (dy / 8) * 132;
            if (index >= frame_size) continue;

            // Read source bit at (sx, sy)
            unsigned char b = (unsigned char)pf->print_data[(sx / 8) + sy * pf->bytesperline];
            int bit_on = (b & (1 << (sx % 8))) != 0;

            unsigned char mask = (unsigned char)(1u << (dy % 8));
            if (!bit_on) frame[index] &= (unsigned char)~mask;
            else         frame[index] |= mask;
        }
    }
}

/*
 * 	if (key == 255) {
		do {
			key = RP_WA_KEY();
		} while (key == 255);
	}
 */

#ifdef __cplusplus
extern "C" {
#endif
int shell_history_draw(int offset_rows, int control_mode)
{
    if (is_first) initializePrintFrames();

	uint8_t key = 255;
    bool anything_to_print = false;

    do {
    	key = 255;
        int rows_drawn = 0;
        int print_frame_id = frame_offset - 1;
        bool is_at_top = true;

		memset(frame, 0, frame_size);
		while (rows_drawn < 32 && print_frame_id >= 0) {

			if (print_frame_id >= PRINT_FRAMES) {
				// frame_offset is inconsistent; stop rather than wrap/clamp
				break;
			}

			struct PrintFrame *pf = &print_frames[print_frame_id];

			// If frames are stored contiguously and older ones are below 0, stop.
			if (pf->print_data == NULL || pf->height <= 0)
				break;

			// If this frame would be entirely off-screen above the top, stop.
			if (rows_drawn + pf->height > 32)
				break;

			anything_to_print = true;
			if (rows_drawn >= offset_rows) {
				print_frame_to_screen(pf, rows_drawn - offset_rows);
				is_at_top = false;
			}
			rows_drawn += pf->height;
			print_frame_id--;
		}

		RP_DISPLAY_DRAW(frame);

		if (control_mode == 1 && key == 255) {
			do {
				key = RP_WA_KEY();
			} while (key == 255);
			if (key == 18 && !is_at_top) offset_rows += 3;
			else if (key == 23) offset_rows -= 3;
			if (offset_rows < 0) offset_rows = 0;
		}

    } while (control_mode == 1 && (key == 18 || key == 23) && anything_to_print);

    if (!anything_to_print) {
        uint8_t row = 1, col = 10;
        RP_PRINT_TEXT("PRINTOUT BLANK", &row, &col);
    }
    return 0;
}
#ifdef __cplusplus
}
#endif
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
