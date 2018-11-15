/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			grade_list.c
 * Author:			P. Bauer
 * Due Date:		November 18, 2010
 * ----------------------------------------------------------
 * Description:
 * Implementation of grade_list.h.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <stdbool.h>

#include "process_list.h"

#define MAX_LIST_ENTRIES 13 //hinzugefügt

void init_process_list(ProcessList* pl) //Methode implementiert
{
    pl->length = 0;
    for (int i = 0; i < MAX_LIST_ENTRIES; i++)
    {
        pl->processes[i] = 0;
    }
}

int get_length(const ProcessList* pl) //Methode implementiert
{
    return pl->length;
}

bool add_entry(ProcessList* pl, struct ProcessListEntry* e) //const auf struct geändert + Methode implementiert
{
    if (pl->length < MAX_LIST_ENTRIES)
    {
        pl->processes[pl->length] = e;
        pl->length++;
        return true;
    }
    return false;
}

bool add_entries(ProcessList* pl, struct ProcessListEntry* e[], int n) //const auf struct geändert + Methode implementiert
{
    if ((pl->length + n) <= MAX_LIST_ENTRIES)
    {
        int added_entries = 0;
        for (int i = 0; i < n; i++)
        {
            if (e[i] != 0)
            {
                pl->processes[pl->length + i] = e[i];
                added_entries++;
            }
        }
        pl->length += added_entries;
        return true;
    }
    return false;
}

int get_process_with_id(const ProcessList* pl, int id, struct ProcessListEntry* result_list[]) //const auf struct geändert + Methode implementiert
{
    int entries_found = 0;
    for (int i = 0; i < pl->length; i++)
    {
        if (pl->processes[i] != 0 && pl->processes[i]->pid == id)
        {
            result_list[entries_found] = pl->processes[i];
            entries_found++;
        }
    }
    return entries_found;
}

int get_processes_with_state(const ProcessList* pl, enum ProcessState state, struct ProcessListEntry* result_list[]) //const auf struct geändert + Methode implementiert
{
    int entries_found = 0;
    for (int i = 0; i < pl->length; i++)
    {
        if (pl->processes[i] != 0)
        {
            if (state == pl->processes[i]->state)
            {
                result_list[entries_found] = pl->processes[i];
                entries_found++;
            }
        }
    }
    return entries_found;
}

struct ProcessListEntry* get_process_with_highest_cpu_consumption(const ProcessList* pl) //Methode implementiert
{
    int highest_cpu_usage = 0;
    int max_cpu_usage = 0;

    ProcessListEntry* highest_cpu_usage_entry = 0;

    for (int i = 0; i < pl->length; i++)
    {
        if (pl->processes[i] != 0 && pl->processes[i]->cpu_usage >= highest_cpu_usage)
        {
            highest_cpu_usage = pl->processes[i]->cpu_usage;
            if (highest_cpu_usage > max_cpu_usage)
            {
                max_cpu_usage = highest_cpu_usage;
                highest_cpu_usage_entry = pl->processes[i];
            }
        }
    }
    return highest_cpu_usage_entry;
}

struct ProcessListEntry* get_process_with_lowest_cpu_consumption(const ProcessList* pl) //Methode implementiert
{
    int lowest_cpu_usage;
    struct ProcessListEntry* process_with_highest_cpu_usage = get_process_with_highest_cpu_consumption(pl);
    struct ProcessListEntry* lowest_cpu_usage_entry = 0;

    if (process_with_highest_cpu_usage == 0)
    {
        lowest_cpu_usage = 0;
    }
    else lowest_cpu_usage = get_process_with_highest_cpu_consumption(pl)->cpu_usage;

    int min_cpu_usage = lowest_cpu_usage;


    if (pl->length == 1)
        return pl->processes[0];

    for (int i = 0; i < pl->length; i++)
    {
        if (pl->processes[i] != 0 && pl->processes[i]->cpu_usage <= lowest_cpu_usage)
        {
            lowest_cpu_usage = pl->processes[i]->cpu_usage;
            if (lowest_cpu_usage < min_cpu_usage)
            {
                min_cpu_usage = lowest_cpu_usage;
                lowest_cpu_usage_entry = pl->processes[i];
            }
        }
    }
    return lowest_cpu_usage_entry;
}

bool containsIndex(int indices[], int index) //Methode implementiert
{
    for (int i = 0; i < MAX_LIST_ENTRIES; i++)
    {
        if (indices[i] == index)
        {
            return true;
        }
    }
    return false;
}

int getFreeIndex(int indices[]) //Methode implementiert
{
    for (int i = 0; i < MAX_LIST_ENTRIES; i++)
    {
        if (indices[i] == -1)
        {
            return i;
        }
    }
    return -1;
}

void addIndex(int* indices, int index) //Methode implementiert
{
    int i = getFreeIndex(indices);
    indices[i] = index;
}

/*
 * Bubblesort für die Sortierung der CPU Auslastung implementiert
 */
void sortCPU_incrementing(ProcessList* pl) //Methode implementiert
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < pl->length - 1; i++)
        {
            if (pl->processes[i]->cpu_usage > pl->processes[i + 1]->cpu_usage)
            {
                struct ProccessListEntry* p1 = pl->processes[i];
                pl->processes[i] = pl->processes[i + 1];
                pl->processes[i + 1] = p1;
                swapped = true;
            }
        }
    } while (swapped);
}

int get_top_n_processes_cpu(const ProcessList* pl, int n, struct ProcessListEntry* result_list[]) //const auf struct geändert + Methode implementiert
{
    int found = 0;
    ProcessList

    if (n > 0)
    {
        sortCPU_incrementing()
    }

    return found;
}

int get_bottom_n_processes_cpu(const ProcessList* pl, int n, struct ProcessListEntry* result_list[]) //const auf struct geändert + Methode implementiert
{
    return 0;
}
