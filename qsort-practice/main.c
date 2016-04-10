//
//  main.c
//  qsort-practice
//
//  Created by 雪竜 on 16/4/10.
//  Copyright © 2016年 雪竜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct __process
{
	int pid;
	int arrv_time;
	int priority;
}
process;

process parse_process_info(char* str)
{
	process p;
	
	p.pid = atoi(strtok(str, ","));
	p.arrv_time = atoi(strtok(NULL, ","));
	p.priority = atoi(strtok(NULL, ","));
	
	return p;
}

void print_process(process* p)
{
	printf("Process %d: %d, %d\n", p->pid, p->arrv_time, p->priority);
}

int linecount (char *file)
{
	int ch, total = 0;
	FILE *fp = fopen(file,"r");
	if (!fp) return -1;
	while ((ch=fgetc(fp)) != EOF) if (ch==10) total++;
	fclose(fp);
	return total;
}

int sort_by_arrivaltime(const void* p1, const void* p2)
{
	int arrv_p1 = ((process*)p1)->arrv_time;
	int arrv_p2 = ((process*)p2)->arrv_time;
	
	return arrv_p1 - arrv_p2;
}

int sort_by_priority(const void* p1, const void* p2)
{
	int priority_p1 = ((process*)p1)->priority;
	int priority_p2 = ((process*)p2)->priority;
	int arrv_p1 = ((process*)p1)->arrv_time;
	int arrv_p2 = ((process*)p2)->arrv_time;
	if (priority_p1 == priority_p2)
	{
		return arrv_p1 - arrv_p2;
	}
	else
	{
		return priority_p2 - priority_p1;
	}
}

int main(int argc, const char * argv[])
{
	
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	
	fp = fopen("process.txt", "r");
	if (!fp)
		exit(EXIT_FAILURE);
	
	int num_of_lines = linecount("process.txt") + 1;
	
	process* processes_sorted_by_arrivaltime = (process*)malloc(sizeof(process)*num_of_lines);
	process* processes_sorted_by_priority = (process*)malloc(sizeof(process)*num_of_lines);
	
	int counter = 0;
	while ((read = getline(&line, &len, fp)) != -1)
	{
		processes_sorted_by_arrivaltime[counter] = parse_process_info(line);
		processes_sorted_by_priority[counter] = processes_sorted_by_arrivaltime[counter];
		//print_process(&processes[counter]);
		counter++;
	}
	
	qsort(processes_sorted_by_arrivaltime, num_of_lines, sizeof(process), sort_by_arrivaltime);
	qsort(processes_sorted_by_priority, num_of_lines, sizeof(process), sort_by_priority);
	
	printf("Sorted by Arrival Time: \n");
	
	for (int i = 0; i < num_of_lines; i++)
	{
		print_process(&processes_sorted_by_arrivaltime[i]);
	}
	
	printf("\nSorted by Arrival Time: \n");
	
	for (int i = 0; i < num_of_lines; i++)
	{
		print_process(&processes_sorted_by_priority[i]);
	}
	
	free(processes_sorted_by_arrivaltime);
	free(processes_sorted_by_priority);
    return 0;
}


