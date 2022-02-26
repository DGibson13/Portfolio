//Computer Operating Systems
//MLFQ simulator
#include <iostream>
#include <string>
using namespace std;

class process {
public:
	int Event[20];
	bool iscpuBurst;	//display true if CPUBurst, false if IOTime.
	int cycle;			//index of array
	int waitTime;		//time waiting
	int completed;		//time all processes complete
	int responseTime;	//first response
	int arrivalTime;	//time item arrives in schedule
	int LEVEL;			//levels go 1 to 3, determines which algorithm is used, increments by 1 per completed algorithm
	int processNumber;	//Process 1,2,3,4,5,6,7 or 8
};

//function declaration
int findEarliest(process list[], int &time, int &timeNotUtilized);
void print(process list[], int time, int index);
process PRIORITY1(process list[], int earliestIndex, int &time);
process PRIORITY2(process list[], int earliestIndex, int &time, int &timeNotUtilized);
process PRIORITY3(process list[], int earliestIndex, int &time, int &timeNotUtilized);

process IODECREMENT(process list[], int &time);
int main() {
	//variable declarations
	process PROCESSES[8];
	int placeholder;
	int time = 0;
	int timeNotUtilized = 0;
	double CPUtilization = 0;
	double averageWT = 0;
	double averageRT = 0;
	double averageTT = 0;
	int numbers[8][20] = {
		{ 4, 24, 5, 73, 3, 31, 5, 27, 4, 33, 6, 43, 4, 64, 5, 19, 2 },
		{ 18, 31, 19, 35, 11, 42, 18, 43, 19, 47, 18, 43, 17, 51, 19, 32, 10 },
		{ 6, 18, 4, 21, 7, 19, 4, 16, 5, 29, 7, 21, 8, 22, 6, 24, 5 },
		{ 17 ,42 , 19, 55, 20, 54, 17, 52, 15, 67, 12, 72, 15, 66, 14 },
		{ 5, 81, 4, 82, 5, 71, 3, 61, 5, 62, 4, 51, 3, 77, 4, 61, 3, 42, 5 },
		{ 10, 35, 12, 41, 14, 33, 11, 32, 15, 41, 13, 29, 11 },
		{ 21, 51, 23, 53, 24, 61, 22, 31, 21, 43, 20 },
		{ 11, 52, 14, 42, 15, 31, 17, 21, 16, 43, 12, 31, 13, 32, 15 }
	};

	//loads content
	int i = 0;
	int j = 0;

	while (i != 8)
	{
		while (j != 20)
		{
			PROCESSES[i].Event[j] = numbers[i][j];
			j++;
		}
		PROCESSES[i].cycle = 0;
		PROCESSES[i].iscpuBurst = true;
		PROCESSES[i].waitTime = 0;
		PROCESSES[i].completed = 0;
		PROCESSES[i].responseTime = -5;
		PROCESSES[i].arrivalTime = 0;
		PROCESSES[i].LEVEL = 1;
		PROCESSES[i].processNumber = i + 1;
		i++;
		j = 0;
	}
	i = 0;
	j = 0;

	//finding earliest arrival time
	placeholder = findEarliest(PROCESSES, time, timeNotUtilized);
	do {

		//LEVEL 1 ROUND ROBIN
		if (PROCESSES[placeholder].LEVEL == 1 && PROCESSES[placeholder].iscpuBurst == true)
		{
			*PROCESSES = PRIORITY1(PROCESSES, placeholder, time);
		}

		//LEVEL 2 ROUND ROBIN
		else if (PROCESSES[placeholder].LEVEL == 2 && PROCESSES[placeholder].iscpuBurst == true)
		{
			*PROCESSES = PRIORITY2(PROCESSES, placeholder, time, timeNotUtilized);
		}

		//LEVEL 3 FIRST COME FIRST SERVE
		else if (PROCESSES[placeholder].LEVEL == 3 && PROCESSES[placeholder].iscpuBurst == true)
		{
			*PROCESSES = PRIORITY3(PROCESSES, placeholder, time, timeNotUtilized);
		}

		//if all items are in IO and all items are completed
		if ((PROCESSES[0].iscpuBurst == false && PROCESSES[1].iscpuBurst == false && PROCESSES[2].iscpuBurst == false &&
			PROCESSES[3].iscpuBurst == false && PROCESSES[4].iscpuBurst == false && PROCESSES[5].iscpuBurst == false &&
			PROCESSES[6].iscpuBurst == false && PROCESSES[7].iscpuBurst == false) &&
			(PROCESSES[0].Event[PROCESSES[0].cycle]<0 && PROCESSES[1].Event[PROCESSES[1].cycle]<0 && PROCESSES[2].Event[PROCESSES[2].cycle]<0) &&
			PROCESSES[3].Event[PROCESSES[3].cycle]<0 && PROCESSES[4].Event[PROCESSES[4].cycle]<0 && PROCESSES[5].Event[PROCESSES[5].cycle]<0 &&
			PROCESSES[6].Event[PROCESSES[6].cycle]<0 && PROCESSES[7].Event[PROCESSES[7].cycle]<0)
		{
			print(PROCESSES, time, placeholder);

			//calculate time processes completed
			for (int k = 0; k != 8; k++)
			{
				PROCESSES[k].completed = time + PROCESSES[k].Event[PROCESSES[k].cycle];
			}

			i = 0;
			while (i != 8)
			{
				//display data for each process
				cout << "P" << i + 1 << ": ";
				cout << "wait Time: " << PROCESSES[i].waitTime << endl;
				cout << "Turnaround Time: " << PROCESSES[i].completed << endl;
				cout << "Response Time: " << PROCESSES[i].responseTime << endl;
				cout << endl << endl;

				//add totals for the average calculation below
				averageWT = averageWT + PROCESSES[i].waitTime;
				averageRT = averageRT + PROCESSES[i].responseTime;
				averageTT = averageTT + PROCESSES[i].completed;
				i++;
			}
			//calculate CPU Utilization and averages
			CPUtilization = ((time - timeNotUtilized));
			CPUtilization = CPUtilization / time;
			CPUtilization = CPUtilization * 100;
			averageWT = averageWT / 8;
			averageRT = averageRT / 8;
			averageTT = averageTT / 8;

			//output end of program stats
			cout << "Total Time: " << time-- << endl;
			cout << "CPUtilization: " << CPUtilization << "%" << endl;
			cout << "Average Wait Time: " << averageWT << endl;
			cout << "Average Turnaround Time: " << averageTT << endl;
			cout << "Average Response Time: " << averageRT << endl;
			return 0;
		}

		//find earliest arrival time of highest priority
		placeholder = findEarliest(PROCESSES, time, timeNotUtilized);

	} while (placeholder != -1);
	return 0;
}

int findEarliest(process list[], int &time, int &timeNotUtilized)
{
	process earliest;
	earliest.cycle = -1;
	earliest.LEVEL = 4;
	earliest.arrivalTime = 0;
	int placeholder = -1;
	int i = 0;

	//select first item that != 0 and is not in I/O;
	while ((earliest.cycle == -1) && (i<8))
	{
		//item is greater than 0 and is in burst cycle
		if ((list[i].Event[list[i].cycle]>0) && (list[i].iscpuBurst == true))
		{
			earliest = list[i];
			placeholder = i;
		}
		i++;
	}

	//All processes are in i/o
	if (i == 8 && (list[0].iscpuBurst == false && list[1].iscpuBurst == false && list[2].iscpuBurst == false &&
		list[3].iscpuBurst == false && list[4].iscpuBurst == false && list[5].iscpuBurst == false &&
		list[6].iscpuBurst == false && list[7].iscpuBurst == false))
	{
		//decrement all items in i/o, add timers
		*list = IODECREMENT(list, time);
		timeNotUtilized++;
		time++;
		return -2;
	}

	i = 0;
	//selects earliest item that is not in i/o
	while (i<8)
	{
		//if selected earliest is greater than number being compared to and that item is in burst, and that item is of higher priority, update
		if (((earliest.arrivalTime > list[i].arrivalTime) && (list[i].iscpuBurst != false)) || (earliest.LEVEL > list[i].LEVEL) && (list[i].iscpuBurst != false))
		{
			earliest = list[i];
			placeholder = i;
		}
		i++;
	}
	//if first time item is being responded to, set response time
	if (list[placeholder].cycle == 0 && list[placeholder].responseTime == -5)
	{
		list[placeholder].responseTime = time;
	}
	return placeholder;
}

//function to print state of processes in execution
void print(process list[], int time, int index)
{
	int i = 0;
	int j = 0;

	//Output formatting
	cout << endl << endl << endl << endl << endl << endl;
	cout << "CURRENT TIME: " << time << endl << endl;

	cout << "NOW RUNNING : P" << list[index].processNumber << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "READY QUEUE:			PROCESS	BURST" << endl;
	for (int k = 0; k != 8; k++)
	{
		if (list[k].iscpuBurst == true)
		{
			cout << "				P" << k + 1 << "	" << list[k].Event[list[k].cycle] << endl;
		}
	}

	cout << "-------------------------------------------------------" << endl;
	cout << "Now in I/O:	PROCESS:	REMAINING TIME IN I/O" << endl;
	for (int k = 0; k != 8; k++)
	{
		if (list[k].iscpuBurst == false && list[k].Event[list[k].cycle] >= 0)
		{
			cout << "		P" << k + 1 << "		" << list[k].Event[list[k].cycle] << endl;
		}
	}
	cout << endl;

	cout << "-------------------------------------------------------" << endl;
	cout << "Completed Processes: ";
	for (int k = 0; k != 8; k++)
	{
		if (list[k].iscpuBurst == false && list[k].Event[list[k].cycle] <= 0)
		{
			cout << "P" << k + 1 << ", ";
		}
	}
	cout << endl << endl << "_______________________________________________________________________" << endl;
	//END OF SPAM OUTPUT BLOCK
}


//algorithm for priority 1 items (6 second round robin tq, non preemptive)
process PRIORITY1(process list[], int earliestIndex, int &time)
{
	int i = 0;

	//while time quantum is not complete, and the current burst is greater than 0
	while ((i<6) && (list[earliestIndex].Event[list[earliestIndex].cycle] > 0))
	{
		//decrement
		*list = IODECREMENT(list, time);
		list[earliestIndex].Event[list[earliestIndex].cycle]--;

		//if process in queue is ready but not running
		for (int j = 0; j < 8; j++)
		{
			if (list[j].iscpuBurst == true && j != earliestIndex)
			{
				list[j].waitTime++;
			}
		}
		time++;
		i++;
	}

	//if our highest priority burst reaches zero
	if (list[earliestIndex].Event[list[earliestIndex].cycle] == 0)
	{
		//move to i/o state
		time++;
		list[earliestIndex].iscpuBurst = false;
		list[earliestIndex].cycle++;
		//status change report
		print(list, time, earliestIndex);
	}
	//if our process does not reach zero and our time quantum has been reached
	else if ((i == 7) && (list[earliestIndex].Event[list[earliestIndex].cycle] != 0))
	{
		list[earliestIndex].arrivalTime = time;
		list[earliestIndex].LEVEL++;
		cout << "Process has not completed but has reached the TQ, moving to priority 2" << endl;
		print(list, time, earliestIndex);
	}

	return *list;
}

//algorithm for second tier processes (round robin 11tq, preemptive) 
process PRIORITY2(process list[], int earliestIndex, int &time, int &timeNotUtilized)
{
	int i = 0;
	int updatedEarliest = earliestIndex;


	//while tq not complete, and the the current burst is greater than 0 AND we do not have a queue that is of higher priority
	while ((i<11) && (list[earliestIndex].Event[list[earliestIndex].cycle] > 0))
	{
		//decrement items in io and selected item
		*list = IODECREMENT(list, time);
		list[earliestIndex].Event[list[earliestIndex].cycle]--;

		//increment wait time for each item in ready queue
		for (int j = 0; j < 8; j++)
		{
			if (list[j].iscpuBurst == true && j != earliestIndex)
			{
				list[j].waitTime++;
			}
		}
		time++;
		i++;
		
		//check if higher process arrived
		updatedEarliest = findEarliest(list, time, timeNotUtilized);
		//if updated earliest returns a different integer and we have not completed our current event
		if ((updatedEarliest != earliestIndex) && (i != 14) && (list[earliestIndex].Event[list[earliestIndex].cycle]>0))
		{
			//a higher priority process has arrived, return what we have immediately
			cout << "higher priority arrival" << endl;
			list[earliestIndex].arrivalTime = time;
			print(list, time, earliestIndex);
			return *list;
		}
	}

	//if our current highest priority burst reaches zero
	if (list[earliestIndex].Event[list[earliestIndex].cycle] == 0)
	{
		//move to i/o state
		time++;
		list[earliestIndex].iscpuBurst = false;
		list[earliestIndex].cycle++;
		print(list, time, earliestIndex);
	}
	//if our process does not reach zero and our tq has been reached
	else if ((i == 14) && (list[earliestIndex].Event[list[earliestIndex].cycle] != 0))
	{
		list[earliestIndex].LEVEL++;
		list[earliestIndex].arrivalTime = time;
		cout << "Process not finished, TQ limit reached, moving to priority 3" << endl;
		print(list, time, earliestIndex);
	}

	return *list;
}

//tier 3 algorithm (FCFS)
process PRIORITY3(process list[], int earliestIndex, int &time, int &timeNotUtilized)
{
	int updatedEarliest = earliestIndex;
	int i = 0;
	//while our list item has an IO burst greater than zero, and a higher priority does not arrive AND our current item is not in i/o
	while (list[earliestIndex].Event[list[earliestIndex].cycle]>0 && updatedEarliest == earliestIndex && list[earliestIndex].iscpuBurst == true)
	{
		//decrement selected item, add wait time for those in ready queue not executing
		list[earliestIndex].Event[list[earliestIndex].cycle]--;
		for (int j = 0; j < 8; j++)
		{
			if (list[j].iscpuBurst == true && j != earliestIndex)
			{
				list[j].waitTime++;
			}
		}
		*list = IODECREMENT(list, time);
		//process reaches zero (completed)
		if (list[earliestIndex].Event[list[earliestIndex].cycle] == 0)
		{
			list[earliestIndex].iscpuBurst = false;
			list[earliestIndex].cycle++;
			print(list, time, earliestIndex);
			time++;
		}

		time++;
		updatedEarliest = findEarliest(list, time, timeNotUtilized);
		//our item has been preempted by a higher priority. return immediately
		if ((list[earliestIndex].Event[list[earliestIndex].cycle] > 0 && list[earliestIndex].iscpuBurst == true) && (earliestIndex != updatedEarliest))
		{
			cout << "Preempted by higher priority" << endl;
			list[earliestIndex].arrivalTime = time;
			print(list, time, earliestIndex);
			return *list;
		}
	}
	//process has finished its burst
	return *list;
}

//decrement all items in i/o state
process IODECREMENT(process list[], int &time)
{
	int i = 0;
	while (i<8)
	{
		if (list[i].iscpuBurst == false)
		{
			list[i].Event[list[i].cycle]--;
			if (list[i].Event[list[i].cycle] == 0)
			{
				list[i].iscpuBurst = true;
				list[i].cycle++;
				list[i].arrivalTime = time;
			}
		}
		i++;
	}
	return *list;
}

