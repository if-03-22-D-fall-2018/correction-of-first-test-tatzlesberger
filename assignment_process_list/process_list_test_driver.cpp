/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Arrays Frequency
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Calculate frequency of random numbers in an array.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

#include "process_list.h"

#include "shortcut.h"
#include "test_process_list.h"

int main(int argc, char *argv[])
{
	ADD_TEST(test_init_process_list);
	// ADD_TEST(test_get_length);
	ADD_TEST(test_add_entry);
	ADD_TEST(test_add_entries);
	ADD_TEST(test_get_process_with_id_when_process_list_is_empty);
	ADD_TEST(get_process_with_id_with_one_element);
	ADD_TEST(get_process_with_id_when_list_is_full);
	ADD_TEST(test_get_processes_with_state);
	ADD_TEST(test_get_process_with_highest_cpu_consumption);
	ADD_TEST(test_get_process_with_lowest_cpu_consumption);
	ADD_TEST(test_get_top_n_processes_cpu);
	ADD_TEST(test_get_bottom_n_processes_cpu);

	run_tests();
	return 0;
}
