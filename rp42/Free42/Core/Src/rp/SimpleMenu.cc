/*
 * SimpleMenu.cpp
 *
 *  Created on: Aug 12, 2025
 *      Author: Jerem
 */


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <cstdio>
#include "rp/RP.hh"
#include <cstring>

void _render_menu(const char* items[4], unsigned int selected_item) {
	RP_CLEAR_LCD();
	uint8_t page = 0;
	uint8_t col = 0;

	for (unsigned int i = 0; i < 4; i++) {
		if (items[i] == 0) continue;
		page = i;
		col = 0;

		if (selected_item == i) RP_PRINT_TEXT(">", &page, &col);

		unsigned int max_length = 23;
		unsigned int len = strlen(items[i]);

		if (len > max_length) {
			char shortened[24];
			for (int cp = 0; cp < 20; cp++) shortened[cp] = items[i][cp];
			shortened[20] = '.';
			shortened[21] = '.';
			shortened[22] = '.';
			shortened[23] = '\0';

			RP_PRINT_TEXT(shortened, &page, &col);
		} else {
			RP_PRINT_TEXT(items[i], &page, &col);
		}
	}
}

unsigned int show_simple_menu(const char* (*get_item)(unsigned int), bool (*item_selected)(unsigned int), unsigned int total_items) {
	unsigned int selected_item = 1;
	unsigned int menu_window = 0;

	const char* selected_items[] = { get_item(0), get_item(1), get_item(2), get_item(3) };

	_render_menu(selected_items, selected_item - menu_window);

	uint8_t key;

	do {
		key = RP_WA_KEY();
	} while (key == 33);

	if (key == 255) {
		do {
			key = RP_WA_KEY();
		} while (key == 255);
	}

	while (1) {
		_render_menu(selected_items, selected_item - menu_window);

		if (key == 33) {
			while (RP_WA_KEY() == 33);
			_render_menu(selected_items, selected_item - menu_window);

			return -1;
		}
		else if (key == 18) {
			if (selected_item > 1) {
				selected_item--;

				if (selected_item < menu_window + 1 && menu_window != 0) {
					menu_window--;

					selected_items[1] = get_item(menu_window + 1);
					selected_items[2] = get_item(menu_window + 2);
					selected_items[3] = get_item(menu_window + 3);
				}
			}
		} else if (key == 23) {
			if (selected_item < total_items) {
				selected_item++;

				if (selected_item > menu_window + 3) {
					menu_window = selected_item - 3;

					selected_items[1] = get_item(menu_window + 1);
					selected_items[2] = get_item(menu_window + 2);
					selected_items[3] = get_item(menu_window + 3);
				}
			}
		} else if (key == 13) {
			while (RP_WA_KEY() == 13);

			if (item_selected == 0) return selected_item;

			if (item_selected(selected_item)) return selected_item;

			_render_menu(selected_items, selected_item - menu_window);
		} else if (key == 19 || key == 20 || key == 21 || key == 24 || key == 25 || key == 26 || key == 29 || key == 30 || key == 31) {
			while (RP_WA_KEY() == key);

			unsigned int selected_item;
			if (key >= 29) selected_item = key - 28;
			else if (key >= 24) selected_item = key - 23 + 3;
			else selected_item = key - 18 + 6;

			if (item_selected(selected_item)) return 1;
			_render_menu(selected_items, selected_item - menu_window);
		}

		key = RP_WA_KEY();
	}
}

void _render_number_selector(const char* name, int value) {
	RP_CLEAR_LCD();

	uint8_t page = 0;
	uint8_t col = 0;
	RP_PRINT_TEXT(name, &page, &col);

	page = 1;
	col = 10;

	char buf[10];
	sprintf(buf, "%d", value);

	RP_PRINT_TEXT(buf, &page, &col);

	page = 3;
	col = 0;

	RP_PRINT_TEXT("Use arrow keys", &page, &col);
}

int number_selector(const char* name, int min, int max, int default_val, int increment) {
	int value = default_val;

	_render_number_selector(name, value);

	uint8_t key;

	do {
		key = RP_WA_KEY();
	} while (key == 33);

	if (key == 255) {
		do {
			key = RP_WA_KEY();
		} while (key == 255);
	}

	while (1) {

		if (key == 13) { // enter
			return value;
		} else if (key == 33) return default_val;

		if (key == 18) { // increase by 1
			if (value + increment <= max) {
				value += increment;
				_render_number_selector(name, value);
			}
		} else if (key == 23) { // decrease by 1
			if (value - increment >= min) {
				value -= increment;
				_render_number_selector(name, value);
			}
		}

		key = RP_WA_KEY();
	}
}

#ifdef __cplusplus
}
#endif
