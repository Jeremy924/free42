/*
 * SimpleMenu.h
 *
 *  Created on: Aug 12, 2025
 *      Author: Jerem
 */

#ifndef INC_RP_SIMPLEMENU_HH_
#define INC_RP_SIMPLEMENU_HH_

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

unsigned int show_simple_menu(const char* (*get_item)(unsigned int), bool (*item_selected)(unsigned int), unsigned int total_items);

int number_selector(const char* name, int min, int max, int default_val);


#ifdef __cplusplus
}
#endif

#endif /* INC_RP_SIMPLEMENU_HH_ */
