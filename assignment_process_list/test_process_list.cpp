/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			test_grade_list.c
 * Author:			P. Bauer
 * Due Date:		November 19, 2010
 * ----------------------------------------------------------
 * Description:
 * Test functions for grade_list.
 * ----------------------------------------------------------
 */
#include <stdio.h>

#include "shortcut.h"
#include "process_list.h"
#include "test_process_list.h"

#define TEST_ENTRIES_COUNT 13
												/*   pid,		p_name,			cpu,	time,	threads,	vsize,	state */
struct ProcessListEntry p1 = {12,		"cron",			5,		500,		1,		2,		SLEEPING};
struct ProcessListEntry p2 = {1,		"init",			3,		753,		2,		1,		IDLE};
struct ProcessListEntry p3 = {3550,		"top",			4,		1500,		1,		2718,	RUNNING};
struct ProcessListEntry p4 = {2693,		"bash",			0,		1100,		1,		2378,	SLEEPING};
struct ProcessListEntry p5 = {2692,		"login",		0,		22000,		1,		2379,	SLEEPING};
struct ProcessListEntry p6 = {241,		"Safari",		10,		31000,		10,		4926,	RUNNING};
struct ProcessListEntry p7 = {3038,		"Mail",			0,		22000,		7,		4844,	IDLE};
struct ProcessListEntry p8 = {2994,		"iCal",			0,		2718,		2,		2504,	STOPPED};
struct ProcessListEntry p9 = {3020,		"mdworker",		0,		420,		3,		2426,	ZOMBIE};
struct ProcessListEntry p10 = {2709,	"BBEdit",		1,		50246,		3,		2709,	RUNNING};
struct ProcessListEntry p11 = {246,		"WebKitPlugin", 0,		0,			2,		2410,	SLEEPING};
struct ProcessListEntry p12 = {120,		"Skype",		2,		4305400,	17,		1122,	RUNNING};
struct ProcessListEntry p13 = {7231,	"Tunnelblick",	10,		3205345,	5,		2486,	RUNNING};

#define MORE_ENTRIES_COUNT 12
static struct ProcessListEntry *more_entries[] = {
	&p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13
};
static ProcessList pl;

/* ---------------------------- Public functions ------------------------------------- */
TEST(test_init_process_list)
{
	init_process_list(&pl);
	ASSERT_EQUALS(0, pl.length);
}

TEST(test_add_entry)
{
	bool adding_possible;

	init_process_list(&pl);
	adding_possible = add_entry(&pl, &p1);
	ASSERT_TRUE(adding_possible, "Adding first entry must be possible");
	if (pl.processes[0]) {
		ASSERT_EQUALS(12, pl.processes[0]->pid);
	}
	ASSERT_EQUALS(1, get_length(&pl));
}

/* ---------------------------- Private function ------------------------------------ */
/** make_list_full adds test entries until the grade list is full
*** @return True if filling is possible, FALSE otherwise
*/
static bool make_list_full();
TEST(test_add_entries)
{
	struct ProcessListEntry* one_entry[] = {&p1};
	bool adding_possible;

	init_process_list(&pl);

	adding_possible = add_entries(&pl, one_entry, 1);
	ASSERT_TRUE(adding_possible, "Adding of one entry in empty list must be possible");
	ASSERT_EQUALS(1, get_length(&pl));

	init_process_list(&pl);
	ASSERT_EQUALS(0, get_length(&pl));

	add_entry(&pl, &p1);
	adding_possible = make_list_full();
	ASSERT_TRUE(adding_possible, "Making an empty list full must be possible");
	ASSERT_EQUALS(MAX_LIST_ENTRIES, get_length(&pl));
	if (pl.processes[MAX_LIST_ENTRIES - 1]) {
		ASSERT_EQUALS(7231, pl.processes[MAX_LIST_ENTRIES - 1]->pid);
	}
	adding_possible = add_entries(&pl, one_entry, 1);
	ASSERT_FALSE(adding_possible, "Adding entries in full list must NOT be possible");
	ASSERT_EQUALS(MAX_LIST_ENTRIES, get_length(&pl));
}

static bool make_list_full()
{
	int empty_space = MAX_LIST_ENTRIES - get_length(&pl);

	if (empty_space > TEST_ENTRIES_COUNT - get_length(&pl)) {
		return false;
	}
	else {
		return (add_entries(&pl, more_entries, MORE_ENTRIES_COUNT));
	}
}


TEST(test_get_process_with_id_when_process_list_is_empty)
{
	struct ProcessListEntry *proc_list[MAX_LIST_ENTRIES];
	int length;

	init_process_list(&pl);
	length = get_process_with_id(&pl, 1, proc_list);
	ASSERT_EQUALS(0, length);
}

TEST(get_process_with_id_with_one_element)
{
	struct ProcessListEntry *proc_list[MAX_LIST_ENTRIES];
	int length;

	add_entry(&pl, &p1);
	length = get_process_with_id(&pl, 12, proc_list);
	ASSERT_EQUALS(1, length);
	if (length == 1) {
		ASSERT_EQUALS(12, proc_list[0]->pid);
	}

	length = get_process_with_id(&pl, 1, proc_list);
	ASSERT_EQUALS(0, length);
}

TEST(get_process_with_id_when_list_is_full)
{
	struct ProcessListEntry *proc_list[MAX_LIST_ENTRIES];
	int length;

	make_list_full();
	length = get_process_with_id(&pl, 1, proc_list);
	ASSERT_EQUALS(1, length);

	if (length == 1) {
		ASSERT_EQUALS(1, proc_list[0]->pid);
	}
}

TEST(test_get_processes_with_state)
{
	struct ProcessListEntry *proc_list[MAX_LIST_ENTRIES];
	int length;

	init_process_list(&pl);
	length = get_processes_with_state(&pl, RUNNING, proc_list);
	ASSERT_EQUALS(0, length);

	add_entry(&pl, &p1);
	length = get_processes_with_state(&pl, RUNNING, proc_list);
	ASSERT_EQUALS(0, length);

	length = get_processes_with_state(&pl, SLEEPING, proc_list);
	ASSERT_EQUALS(1, length);

	make_list_full();

	length = get_processes_with_state(&pl, SLEEPING, proc_list);
	ASSERT_EQUALS(4, length);
	if (length == 4) {
		ASSERT_EQUALS(12, proc_list[0]->pid);
		ASSERT_EQUALS(2693, proc_list[1]->pid);
		ASSERT_EQUALS(2692, proc_list[2]->pid);
		ASSERT_EQUALS(246, proc_list[3]->pid);
	}
}

TEST(test_get_process_with_highest_cpu_consumption)
{
	struct ProcessListEntry *p;

	init_process_list(&pl);
	p = get_process_with_highest_cpu_consumption(&pl);
	ASSERT_TRUE(p == 0, "Empty process list can't return any process, 0 expected");

	add_entry(&pl, &p1);
	p = get_process_with_highest_cpu_consumption(&pl);
	ASSERT_TRUE(p != 0, "Process list with one process must return first element");
	if (p != 0) {
		ASSERT_EQUALS(12, p->pid);
	}

	make_list_full();

	p = get_process_with_highest_cpu_consumption(&pl);
	ASSERT_TRUE(p != 0, "Full process list must return a highest cpu process");
	if (p!= 0) {
		ASSERT_EQUALS(241, p->pid);
	}
}

TEST(test_get_process_with_lowest_cpu_consumption)
{
	struct ProcessListEntry *p;

	init_process_list(&pl);
	p = get_process_with_lowest_cpu_consumption(&pl);
	ASSERT_TRUE(p == 0, "Empty process list can't return any process, 0 expected");

	add_entry(&pl, &p1);
	p = get_process_with_lowest_cpu_consumption(&pl);
	ASSERT_TRUE(p != 0, "Process list with one process must return first element");
	if (p != 0) {
		ASSERT_EQUALS(12, p->pid);
	}

	make_list_full();

	p = get_process_with_lowest_cpu_consumption(&pl);
	ASSERT_TRUE(p != 0, "Full process list must return a lowest cpu process");
	if (p != 0) {
		ASSERT_EQUALS(2693, p->pid);
	}
}

TEST(test_get_top_n_processes_cpu)
{
	struct ProcessListEntry *proc_list[MAX_LIST_ENTRIES];
	int length;

	init_process_list(&pl);
	length = get_top_n_processes_cpu(&pl, 5, proc_list);
	ASSERT_EQUALS(0, length);

	add_entry(&pl, &p1);
	length = get_top_n_processes_cpu(&pl, 5, proc_list);
	ASSERT_EQUALS(1, length);
	if (length == 1) {
		ASSERT_EQUALS(12, proc_list[0]->pid);
	}

	make_list_full();

	length = get_top_n_processes_cpu(&pl, 1, proc_list);
	ASSERT_EQUALS(1, length);
	if (length == 1) {
		ASSERT_EQUALS(241, proc_list[0]->pid);
	}

	length = get_top_n_processes_cpu(&pl, 5, proc_list);
	ASSERT_EQUALS(5, length);
	if (length == 5) {
		ASSERT_EQUALS(241, proc_list[0]->pid);
		ASSERT_EQUALS(7231, proc_list[1]->pid);
		ASSERT_EQUALS(12, proc_list[2]->pid);
		ASSERT_EQUALS(3550, proc_list[3]->pid);
		ASSERT_EQUALS(1, proc_list[4]->pid);
	}

	length = get_top_n_processes_cpu(&pl, 0, proc_list);
	ASSERT_EQUALS(0, length);

	length = get_bottom_n_processes_cpu(&pl, TEST_ENTRIES_COUNT + 1, proc_list);
	ASSERT_EQUALS(TEST_ENTRIES_COUNT, length);
}

TEST(test_get_bottom_n_processes_cpu)
{
	struct ProcessListEntry *proc_list[MAX_LIST_ENTRIES];
	int length;

	init_process_list(&pl);
	length = get_bottom_n_processes_cpu(&pl, 5, proc_list);
	ASSERT_EQUALS(0, length);

	add_entry(&pl, &p1);
	length = get_bottom_n_processes_cpu(&pl, 5, proc_list);
	ASSERT_EQUALS(1, length);
	if (length == 1) {
		ASSERT_EQUALS(12, proc_list[0]->pid);
	}

	make_list_full();

	length = get_bottom_n_processes_cpu(&pl, 1, proc_list);
	ASSERT_EQUALS(1, length);
	if (length == 1) {
		ASSERT_EQUALS(2693, proc_list[0]->pid);
	}

	length = get_bottom_n_processes_cpu(&pl, 7, proc_list);
	ASSERT_EQUALS(7, length);
	if (length == 7) {
		ASSERT_EQUALS(2693, proc_list[0]->pid);
		ASSERT_EQUALS(2692, proc_list[1]->pid);
		ASSERT_EQUALS(3038, proc_list[2]->pid);
		ASSERT_EQUALS(2994, proc_list[3]->pid);
		ASSERT_EQUALS(3020, proc_list[4]->pid);
		ASSERT_EQUALS(246, proc_list[5]->pid);
		ASSERT_EQUALS(2709, proc_list[6]->pid);
	}

	length = get_bottom_n_processes_cpu(&pl, 0, proc_list);
	ASSERT_EQUALS(0, length);

	length = get_bottom_n_processes_cpu(&pl, TEST_ENTRIES_COUNT + 1, proc_list);
	ASSERT_EQUALS(TEST_ENTRIES_COUNT, length);
}
