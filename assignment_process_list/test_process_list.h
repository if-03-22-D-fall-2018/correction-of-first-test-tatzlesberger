/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			test_grade_list.h
 * Author:			P. Bauer
 * Due Date:		November 18, 2010
 * ----------------------------------------------------------
 * Description:
 * Test functions for grade_list.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_PROCESS_LIST_H
#define ___TEST_PROCESS_LIST_H

#include "shortcut.h"

TEST(test_init_process_list);
TEST(test_add_entry);
TEST(test_add_entries);
TEST(test_get_process_with_id_when_process_list_is_empty);
TEST(get_process_with_id_with_one_element);
TEST(get_process_with_id_when_list_is_full);
TEST(test_get_processes_with_state);
TEST(test_get_process_with_highest_cpu_consumption);
TEST(test_get_process_with_lowest_cpu_consumption);
TEST(test_get_top_n_processes_cpu);
TEST(test_get_bottom_n_processes_cpu);
#endif
