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

	return (uint8) psp - heap;
}




#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_FRAMES 50

struct PrintFrame {
    uint8_t* print_data;
    uint16_t print_data_len;
    uint8_t  actual_width;
    int16_t  x_offset;
    uint8_t  height;
    uint16_t bytesperline;
    bool     valid;
};

static struct PrintFrame print_frames[PRINT_FRAMES];

static uint8_t q_wr = 0;     // next write position
static uint8_t q_rd = 0;     // oldest frame position
static uint8_t q_count = 0;  // number of valid frames [0..PRINT_FRAMES]
static bool is_first = true;

static void initializePrintFrames(void) {
    for (int i = 0; i < PRINT_FRAMES; i++) {
        print_frames[i].print_data = (uint8_t*) malloc(162);
        print_frames[i].print_data_len = 162;
        print_frames[i].valid = false;
    }
    q_wr = q_rd = q_count = 0;
    is_first = false;
}

static void free_frame(struct PrintFrame *f) {
    if (f->print_data) free(f->print_data);
    f->print_data = NULL;
    f->valid = false;
}

// Store output frame in ring buffer (drops oldest on overflow)
void shell_print(const char *text, int length,
                 const char *bits, int bytesperline,
                 int x, int y, int width, int height)
{
    (void)text; (void)length; (void)y;

    if (is_first) initializePrintFrames();

    if (!bits || bytesperline <= 0 || width <= 0 || height <= 0) return;

    // overflow-safe size calc
    size_t bpl = (size_t)bytesperline;
    size_t h   = (size_t)height;
    if (h != 0 && bpl > (SIZE_MAX / h)) return;
    size_t nbytes = bpl * h;

    // If full, drop oldest
    // TODO: LOCK if concurrent with reader
    if (q_count == PRINT_FRAMES) {
    	if (print_frames[q_rd].print_data_len < nbytes)
    		free_frame(&print_frames[q_rd]);
        q_rd = (uint8_t)((q_rd + 1) % PRINT_FRAMES);
        q_count--;
    }

    struct PrintFrame *f = &print_frames[q_wr];

    // overwrite slot (it should be invalid, but free defensively)
    uint8_t* buf;
    if (f->print_data_len < nbytes) {
		free_frame(f);

		buf = (uint8_t*)malloc(nbytes);
		f->print_data_len = nbytes;
		if (!buf) return;
    } else buf = f->print_data;

    memcpy(buf, bits, nbytes);

    // publish frame (write metadata, then mark valid at end)
    f->print_data    = buf;
    f->x_offset      = (int16_t)x;
    f->height        = (uint8_t)height;
    f->actual_width  = (uint8_t)width;
    f->bytesperline  = (uint16_t)bytesperline;
    f->valid         = true;

    q_wr = (uint8_t)((q_wr + 1) % PRINT_FRAMES);
    q_count++;
    // TODO: UNLOCK
}

#define MIN(a,b) ((a > b) ? b : a)
#define MAX(a,b) ((a > b) ? a : b)

void print_frame_to_screen(struct PrintFrame* pf, unsigned int yoffset_from_bottom, bool should_shift)
{
    if (!pf || !pf->valid || !pf->print_data) return;

    int y0 = 31 - (int)yoffset_from_bottom - (int)pf->height;
    for (int sy = 0; sy < pf->height; sy++) {
        int dy = y0 + sy;
        if (dy < 0) continue;

        int dx_offset = MAX(0, 132 - pf->actual_width);
        int sx_offset = should_shift ? 0 : MAX(0, pf->actual_width - 132);
        for (int sx = 0; sx < MIN(132, pf->actual_width); sx++) {
            int dx = (int)pf->x_offset + sx + dx_offset;
            if (dx < 0) continue;
            if (dx >= 132 || dy >= 32) continue;

            unsigned int index = (unsigned int)dx + (unsigned int)(dy / 8) * 132u;
            if (index >= frame_size) continue;

            unsigned char b = pf->print_data[((sx + sx_offset) / 8) + sy * pf->bytesperline];
            int bit_on = (b & (1 << ((sx + sx_offset) % 8))) != 0;

            unsigned char mask = (unsigned char)(1u << (dy % 8));
            if (!bit_on) frame[index] &= (unsigned char)~mask;
            else         frame[index] |= mask;
        }
    }
}

#ifdef __cplusplus
extern "C" {
#endif

int shell_history_draw(int offset_rows, int control_mode)
{
    if (is_first) initializePrintFrames();

    uint8_t key = 255;
    uint8_t last_key = 255;
    bool anything_to_print = false;
    bool should_shift = false;
    int timer = 50;
    int timer_events = 0;

    do {
        key = 255;
        int rows_drawn = 0;
        bool is_at_top = true;

        memset(frame, 0, frame_size);

        // Snapshot queue state (recommended if concurrent)
        // TODO: LOCK
        uint8_t count = q_count;
        uint8_t rd = q_rd;
        // TODO: UNLOCK

        // draw newest -> oldest
        for (uint8_t i = 0; i < count && rows_drawn < (offset_rows + 32); i++) {
            // newest index = (rd + count - 1 - i) % PRINT_FRAMES
            uint8_t idx = (uint8_t)((rd + count - 1 - i) % PRINT_FRAMES);
            struct PrintFrame *pf = &print_frames[idx];

            if (!pf->valid || !pf->print_data || pf->height == 0) continue;

            anything_to_print = true;

            if (rows_drawn + pf->height >= offset_rows) {
                print_frame_to_screen(pf, (unsigned int)(rows_drawn - offset_rows), should_shift);
                is_at_top = false;
            }

            rows_drawn += pf->height;
        }

        RP_DISPLAY_DRAW(frame);

        if (control_mode == 1 && key == 255) {

        	while (key == 255) {
        		key = RP_WA_KEY();

        		if (key == 100 + timer) {
        			key = last_key;
        			timer_events++;
        		}

                if (key == 18 && !is_at_top) {
                	offset_rows += timer_events > 2 ? 12 : 8;
                	timer = RP_REGISTER_TIMER((timer_events > 2) ? 200 : 400, 0, 0);
                }
                else if (key == 23) {
                	offset_rows -= timer_events > 2 ? 12 : 8;
                    if (offset_rows < 0) offset_rows = 0;
                    else timer = RP_REGISTER_TIMER((timer_events > 2) ? 200 : 400, 0, 0);
                }
                else if (key == 28) should_shift = !should_shift;
                else if (key != 255) core_repaint_display();
                if (key != 255) last_key = key;
                else {
                	RP_UNREGISTER_TIMER(timer);
                	timer = 50;
                	timer_events = 0;
                }
        	}
        }
    } while (control_mode == 1 && (key == 18 || key == 23 || key == 28) && anything_to_print);

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
