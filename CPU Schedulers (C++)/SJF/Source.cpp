//computer operating systems
//SJF simulator
#include <iostream>
#include <string>
using namespace std;

class process {
public:
	int Event[20];
	bool iscpuBurst;	//display true if CPUBurst, false if IOTime.
	int cycle;			//index of array
	int waitTime;		//time waiting
	int completed;		//time process completed
	int responseTime;	//first time process respose
};

//function for finding the shortest job
int findLowest(process list[]);

int main() {
	//variable declaration
	process PROCESSES[8];
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

	//loading content
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
		PROCESSES[i].responseTime = 0;
		i++;
		j = 0;
	}
	i = 0;
	j = 0;


	//returns location in array of lowest process to be completed
	while (j != -1)
	{

		//all processes in IO
		if (PROCESSES[0].iscpuBurst == false && PROCESSES[1].iscpuBurst == false && PROCESSES[2].iscpuBurst == false &&
			PROCESSES[3].iscpuBurst == false && PROCESSES[4].iscpuBurst == false && PROCESSES[5].iscpuBurst == false &&
			PROCESSES[6].iscpuBurst == false && PROCESSES[7].iscpuBurst == false)
		{
			i = 0;
			//all processes in IO are negative or zero, meaning complete
			if (PROCESSES[0].Event[PROCESSES[0].cycle] <= 0 && PROCESSES[1].Event[PROCESSES[1].cycle] <= 0 &&
				PROCESSES[2].Event[PROCESSES[2].cycle] <= 0 && PROCESSES[3].Event[PROCESSES[3].cycle] <= 0 &&
				PROCESSES[4].Event[PROCESSES[4].cycle] <= 0 && PROCESSES[5].Event[PROCESSES[5].cycle] <= 0 &&
				PROCESSES[6].Event[PROCESSES[6].cycle] <= 0 && PROCESSES[7].Event[PROCESSES[7].cycle] <= 0)
			{
				cout << endl << endl << endl;
				cout << "All processes completed at time:" << time-- << endl << endl;
				i = 0;
				j = 0;

				//calculating time processes completed
				for (int k = 0; k != 8; k++)
				{
					PROCESSES[k].completed = time + PROCESSES[k].Event[PROCESSES[k].cycle];
				}

				while (i != 8)
				{
					//display data
					cout << "P" << i + 1 << ": ";
					cout << "Wait Time: " << PROCESSES[i].waitTime << endl;
					cout << "Turnaround Time: " << PROCESSES[i].completed << endl;
					cout << "Response Time: " << PROCESSES[i].responseTime << endl;
					cout << endl << endl;

					//add times for averaging
					averageWT = averageWT + PROCESSES[i].waitTime;
					averageRT = averageRT + PROCESSES[i].responseTime;
					averageTT = averageTT + PROCESSES[i].completed;
					i++;
					j = 0;
				}

				//calculations for averages and cpu utilization
				CPUtilization = ((time - timeNotUtilized));
				CPUtilization = CPUtilization / time;
				CPUtilization = CPUtilization * 100;
				averageWT = averageWT / 8;
				averageRT = averageRT / 8;
				averageTT = averageTT / 8;

				cout << "Total time: " << time-- << endl;
				cout << "CPUtilization: " << CPUtilization << "%" << endl;
				cout << "Average Wait Time: " << averageWT << endl;
				cout << "Average Turnaround Time: " << averageTT << endl;
				cout << "Average Response Time: " << averageRT << endl;
				return 0;
				//end of execution

			}

			//only while all processes in i/o
			while (i != 8)
			{
				//subtract one from current item
				PROCESSES[i].Event[PROCESSES[i].cycle]--;

				//if current item reaches zero, move to next item in array and update flag
				if (PROCESSES[i].Event[PROCESSES[i].cycle] == 0)
				{
					PROCESSES[i].cycle++;
					PROCESSES[i].iscpuBurst = true;
				}

				i++;
			}
			time++;
			timeNotUtilized++;
		}

		//there is at least one process not in i/o
		else
		{
			//select the lowest process and save index number in j
			j = findLowest(PROCESSES);
			i = 0;
			int placeholder = PROCESSES[j].cycle; //store index of current cycle

												  //if first time response to item, save time
			if (PROCESSES[j].cycle == 0)
			{
				PROCESSES[j].responseTime = time;
			}

			//Output formatting
			cout << endl << endl << endl << endl << endl << endl;
			cout << "CURRENT TIME: " << time << endl << endl;

			cout << "NOW RUNNING : P" << j + 1 << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "READY QUEUE:			PROCESS	BURST" << endl;
			for (int k = 0; k != 8; k++)
			{
				if (PROCESSES[k].iscpuBurst == true)
				{
					cout << "				P" << k + 1 << "	" << PROCESSES[k].Event[PROCESSES[k].cycle] << endl;
				}
			}

			cout << "-------------------------------------------------------" << endl;
			cout << "Now in I/O:	PROCESS:	REMAINING TIME IN I/O" << endl;
			for (int k = 0; k != 8; k++)
			{
				if (PROCESSES[k].iscpuBurst == false && PROCESSES[k].Event[PROCESSES[k].cycle] >= 0)
				{
					cout << "		P" << k + 1 << "		" << PROCESSES[k].Event[PROCESSES[k].cycle] << endl;
				}
			}
			cout << endl;

			cout << "-------------------------------------------------------" << endl;
			cout << "Completed Processes: ";
			for (int k = 0; k != 8; k++)
			{
				if (PROCESSES[k].iscpuBurst == false && PROCESSES[k].Event[PROCESSES[k].cycle] <= 0)
				{
					cout << "P" << k + 1 << ", ";
				}
			}
			cout << endl << endl << "_____________________________________________________________________" << endl;
			//end of output block

			//shortest job found
			if (j != -1)
			{
				do {
					//if end of array
					if (i == 8)
					{
						i = 0;
					}

					//if process is in I/O
					if (PROCESSES[i].iscpuBurst == false)
					{
						//subtract one each time application runs.
						PROCESSES[i].Event[PROCESSES[i].cycle]--;

						//if item hits 0, set to BURST, move cycle to next in array.
						if (PROCESSES[i].Event[PROCESSES[i].cycle] == 0)
						{
							PROCESSES[i].iscpuBurst = true;
							PROCESSES[i].cycle++;
						}
					}

					//if process is over the selected "Shortest" subtract time.
					if (i == j)
					{
						PROCESSES[i].Event[PROCESSES[i].cycle]--;

						//if shortest burst is now 0, set to I/O, move to next cycle
						if (PROCESSES[i].Event[PROCESSES[i].cycle] == 0)
						{
							PROCESSES[i].iscpuBurst = false;
							PROCESSES[i].cycle++;
							if (PROCESSES[i].Event[PROCESSES[i].cycle + 1] == 0)
							{
								cout << "P" << i << " Has completed all CPU Burst and I/O Stages at " << time << endl << endl;
							}
						}
					}

					//if item is on CPUBurst but not the shortest item, wait time +1
					if ((i != j) && (PROCESSES[i].iscpuBurst == true))
					{
						PROCESSES[i].waitTime++;
					}
					i++;

					//signal for one time unit
					if (i == 8)
					{
						time++;
					}

				} while ((PROCESSES[j].Event[placeholder] != 0) || (i != 8));
			}
		}
	}
}

//finds and returns index of array which has the shortest current cpu burst
int findLowest(process list[])
{
	process lowest;
	lowest.cycle = -1;
	int placeholder = -1;
	int i = 0;

	//select first item that != 0 and is not in I/O;
	while ((lowest.cycle == -1) && (i<8))
	{
		//item is greater than 0 and is in burst cycle
		if ((list[i].Event[list[i].cycle]>0) && (list[i].iscpuBurst == true))
		{
			lowest = list[i];
			placeholder = i;
		}
		i++;
	}

	//we have not found an item and have reached the end of the array
	if (i == 8)
	{
		cout << "ALL ITEMS COMPLETE, RETURNING" << endl;
		return -1;
	}

	i = 0;
	//selects lowest item that is not in i/o
	while (i<8)
	{
		//if selected lowest is greater than number being compared to, update
		if ((lowest.Event[lowest.cycle] > list[i].Event[list[i].cycle]) && (list[i].iscpuBurst != false))
		{
			lowest = list[i];
			placeholder = i;
		}
		i++;
	}
	return placeholder;
}

