/*************************************************************************
*	Projec name: CPU Scheduling Algorithum
*	Author:		 Rachel Vanderlely
*   Professor:   Dr.Zhao
*	Date:		 November 12, 2022
*	Class:		 CS3513
*	Purpose:	 To simulate CPU schdeduling algorithims FCFS, SJF and RR
*                at 4 and 8 quantum seconds.  
****************************************************************************/
#include <iostream>         //Input output
#include <iomanip>          //Needed for output manipulation
#include <cstdlib>          // for random number 
#include <ctime>            //For time function
#define MAXPROCESSES 5      //Number of processes. 
#define NUMBERRUNS 100      //Number of times to run program
using std::cout;        
using std::cin;
using std::sort;
using std::setw;
using std::fixed;
using std::setprecision;
/*************************************************************************
                                process_info
This structure holds information about a process. The CPU burst time, 
remaining CPU burst time, processPriority and the processID of a process. 
****************************************************************************/
struct process_info
{
    int processID;                  //The process ID
    int processPriority;            //The priority of the process. Lower number means higher priority.            
    double cpuBurstTime;            //The burst time needed
    double remainingCPUBurstTime;   //The remaining cpu burst time
};

/*************************************************************************
                            Function Prototypes
****************************************************************************/
double random_cpu_burst();
void fill_array_with_processes(int size, process_info arr[]);
void FCFS(int size, process_info arr[],double &awt, double &att);
void SJF(int size, process_info arr[],double &awt, double &att);
bool CompareCPUTimes(const process_info &process1,const process_info &process2 );
void Priority(int size, process_info arr[],double &awt, double &att);
void RoundRobin(int size, process_info arr[],double &awt, double &att, int quantum);
bool CompareProcessPriority(const process_info &process1,const process_info &process2 );
bool AllProcessesComplete(int size, process_info arr[]);
void PrintProcesses(int size, process_info arr[]);
bool ShouldPrint(int i);
int random_priority();
void fillArrayTester(int size, process_info arr[]);


/*************************************************************************
                                Main Function
****************************************************************************/
int main()
{    
    //Providing a seed value once for entire program
    srand((unsigned) time(NULL));

    //All variables needed to hold awt, att and averages for every algorithum
    double awtFCFS = 0;
    double attFCFS = 0;
    double awtSJF = 0;
    double attSJF = 0;
    double awtPri = 0;
    double attPri = 0;
    double awtRR = 0;
    double attRR = 0;
    double awtRR8 = 0;
    double attRR8 = 0;
    double awtFCFSAvg = 0;
    double attFCFSTAvg = 0;
    double awtSJFAvg = 0;
    double attSJFAvg = 0;
    double awtPriAvg = 0;
    double attPriAvg= 0;
    double awtRRAvg = 0;
    double attRRAvg = 0;
    double awtRRAvg8 = 0;
    double attRRAvg8 = 0;

    for (int i = 0; i< NUMBERRUNS; i++){
        cout<<fixed;                                    //Set every cout statement in the program to fixed
        struct process_info processes[MAXPROCESSES];    //Create an array of size MAXPROCESSES to hold MAXPROCESSES processes

        //Fill the process array infor with processes
        //fill_array_with_processes(MAXPROCESSES, processes);

        fillArrayTester(MAXPROCESSES,processes);

        //Print only processes 1,2,3 and 100, as per instructions
        if (ShouldPrint(i) == true)
        {
            cout<<"\n=====================================================\n";
            cout<<"\t\tRUN #: "<<i+1;
            cout<<"\n=====================================================\n";
            PrintProcesses(MAXPROCESSES,processes);
        }

        //Call FCFS and Print only runs processes 1,2,3 and 100, as per instructions
        FCFS(MAXPROCESSES, processes, awtFCFS,attFCFS);
        if (ShouldPrint(i) == true){
        cout<<"-----------------------\n";
        cout<<"FIRST COME FIRST SERVE\n";
        cout<<"-----------------------\n";
        cout<<fixed<<"The AWT is "<<setprecision(4)<<setw(9)<<awtFCFS<<" |\n";
        cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attFCFS<<" |\n";
        cout<<"-----------------------\n";
        }

        //Call SJF and Print only runs processes 1,2,3 and 100, as per instructions
        SJF(MAXPROCESSES, processes,awtSJF,attSJF);
        if (ShouldPrint(i) == true){
        cout<<"SHORTEST JOB FIRST \n";
        cout<<"-----------------------\n";
        cout<<"The AWT is "<<setprecision(4)<<setw(9)<<awtSJF<<" |\n";
        cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attSJF<<" |\n";
        cout<<"-----------------------\n";
        }

        //Call Priority and Print only runs processes 1,2,3 and 100, as per instructions
        Priority(MAXPROCESSES, processes,awtPri,attPri);
        if (ShouldPrint(i) == true)
        {
        cout<<"PRIORITY SCHEDULING \n";
        cout<<"-----------------------\n";
        cout<<"The AWT is "<<setprecision(4)<<setw(9)<<awtPri<<" |\n";
        cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attPri<<" |\n";
        cout<<"-----------------------\n";
        }

        //Call Round Robin and Print only runs processes 1,2,3 and 100, as per instructions
        RoundRobin(MAXPROCESSES, processes,awtRR,attRR,4);
        if (ShouldPrint(i) == true){
        cout<<"ROUND ROBIN QUANTUM 4\n";
        cout<<"-----------------------\n";
        cout<<"The AWT is "<<setprecision(4)<<setw(9)<<awtRR<<" |\n";
        cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attRR<<" |\n";;
        cout<<"-----------------------\n";
        }

        

        //Calculate and Incriment the total after each run
        awtFCFSAvg += awtFCFS;
        attFCFSTAvg += attFCFS;
        awtSJFAvg += awtSJF;
        attSJFAvg += attSJF;
        awtPriAvg += awtPri;
        attPriAvg += attPri;
        awtRRAvg += awtRR;
        attRRAvg += attRR;
    //End of for loop to run program 100 times
     }

    //Calculate the averages by dividing each total by the number of runs
    awtFCFSAvg  /= NUMBERRUNS;
    attFCFSTAvg /= NUMBERRUNS;
    awtSJFAvg   /= NUMBERRUNS;
    attSJFAvg   /= NUMBERRUNS;
    awtPriAvg   /= NUMBERRUNS;
    attPriAvg   /= NUMBERRUNS;
    awtRRAvg    /= NUMBERRUNS;
    attRRAvg    /= NUMBERRUNS;

    //Print the averages of all of the scheduling algos
    cout<<"\n=====================================================\n";
    cout<<"\t\tAVERAGE OF ALL RUNS:";
    cout<<"\n=====================================================\n";
    cout<<"AVERAGE FIRST COME FIRST SERVE\n";
    cout<<"--------------------------\n";
    cout<<"Average AWT is "<<setprecision(4)<<setw(9)<<awtFCFSAvg<<" |\n";
    cout<<"Average ATT is "<<setprecision(4)<<setw(9)<<attFCFSTAvg<<" |\n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE SHORTEST JOB FIRST \n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE AWT is "<<setprecision(4)<<setw(9)<<awtSJFAvg<<" |\n";
    cout<<"AVERAGE ATT is "<<setprecision(4)<<setw(9)<<attSJFAvg<<" |\n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE PRIORITY SCHEDULING \n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE AWT is "<<setprecision(4)<<setw(9)<<awtPriAvg<<" |\n";
    cout<<"AVERAGE ATT is "<<setprecision(4)<<setw(9)<<attPriAvg<<" |\n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE ROUND ROBIN QUANTUM 4\n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE AWT is "<<setprecision(4)<<setw(9)<<awtRRAvg<<" |\n";
    cout<<"AVERAGE ATT is "<<setprecision(4)<<setw(9)<<attRRAvg<<" |\n";;
    cout<<"--------------------------\n";
    cout<<"AVERAGE ROUND ROBIN QUANTUM 8\n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE AWT is "<<setprecision(4)<<setw(9)<<awtRRAvg8<<" |\n";
    cout<<"AVERAGE ATT is "<<setprecision(4)<<setw(9)<<attRRAvg8<<" |\n";;
    cout<<"--------------------------\n";
    return 0;
}


/*************************************************************************
                                random_cpu_burst
This function generates random floating point numbers between 1.0 and 20.0
and returns them as a double. 
****************************************************************************/
double random_cpu_burst()
{
return ( ((double)(rand()%21) / 20.0)  + (rand()%20));
}

/*************************************************************************
                                random_priorty
This function generates random priority between 1 and 100 and returns
them as a integer. 
****************************************************************************/
int random_priority()
{
return  ((rand()%100)  + 1);
}

/*************************************************************************
                                FCFS 
This function take an array of processes and then calculates the individual 
AWT and ATT. Then add them all up and print out the averages. This function
takes in a size, and an array of processes. Also, this function returns 
the awt and att of all the processes in the array using a value result 
argument. 
****************************************************************************/
void FCFS(int size, process_info arr[],double &awt, double &att)
{
    awt = 0;                                        //Initial wait time is 0
    att=0;                                          //Initial turnaround time is 0
    double total_burst_time=0;                      //total burst time initalized to 0
    double total_wait = 0;                          //Total wait time initalized to 0

 for (int i=0; i <size;i++)                         //Iterate through all processes
 {
 total_wait += total_burst_time;                    //wait time starts at 0 then each subsequent process waits the 
                                                    //total burst time of all the processes before him
 total_burst_time += arr[i].cpuBurstTime;           //Add each process burst time to the total burst time. 
 }
    awt = total_wait / size ;                       //Calculate the average of all the wait times
    att = ((total_wait + total_burst_time) /size);  //Calculate the average of all the turn around times
}

/*************************************************************************
                    Void fill_array_with_processses
This function takes in an array, by referance, as well as its size and it 
fills the array with processes 1 through size with a process ID and random
CPUBurst times and random priorities.  
****************************************************************************/
void fill_array_with_processes(int size, process_info arr[])
{
    for (int i = 0;i<size;i++)
        {
        arr[i].processID = i+1;                             //Assign a process ID in order
        arr[i].cpuBurstTime = random_cpu_burst();           //Assign a random burst time
        arr[i].processPriority = random_priority();         //Assign a random priority
        arr[i].remainingCPUBurstTime = arr[i].cpuBurstTime; //Copy the burst time into the remaining burst time 
        }
    return;
}

/*************************************************************************
                                SJF
This scheduling algorithum takes in an array of processes and the size of 
the array. This algorithum then sorts the array in accending order by 
job length. After array is sorted this algorithum then call FCFS to solve. 
This algorithum uses value result arguments to return the awt and att of 
all of the processes in the array. 
****************************************************************************/
void SJF(int size, process_info arr[],double &awt, double &att)
{
    awt = 0;              //Initial wait time is 0
    att=0;                //Initial turnaround time is 0

    //Make a deep copy of all the processes so original is not changed
    process_info tempArr[size];
    for (int i = 0; i <size; i ++) {
        tempArr[i] = arr[i];
    }

    //Sort the array in assending order
    sort(tempArr,(tempArr + size),CompareCPUTimes);
    //Now call the FCFS function on the array sorted by CPU burst time
    FCFS(MAXPROCESSES,tempArr, awt, att);
}

/*************************************************************************
                                Priority 
This scheduling algorithum takes in an array of processes and the size of 
the array. This algorithum then sorts the array in accending order by 
priority. The lowest number has the highest priority. After array is sorted 
this algorithum then call FCFS to solve. This algorithum uses value result 
arguments to return the awt and att of all of the processes in the array. 
****************************************************************************/
void Priority(int size, process_info arr[],double &awt, double &att)
{
    awt = 0;                         //Initial wait time is 0
    att=0;                           //Initial turnaround time is 0
    double total_burst_time=0;       //total burst time initalized to 0
    double total_wait = 0;           //total wait time initalized to 0

    //Make a deep copy of all the processes so original is not changed
    process_info tempArr[size];
    for (int i = 0; i <size; i ++){
        tempArr[i] = arr[i];
    }

    //Sort the array in assending order
    sort(tempArr,(tempArr + size),CompareProcessPriority);
    //Now call the FCFS function on the array sorted by CPU burst time
    FCFS(MAXPROCESSES,tempArr, awt, att);
}

/*************************************************************************
                                Round Robin 
This function takes an array of processes, the size and and a time quantum.
Then calculates the individual AWT and ATT for each process and adds them up.
Then find the average awt and att for all process and return them as value 
result arguments. 
****************************************************************************/
void RoundRobin(int size, process_info arr[],double &awt, double &att, int quantum)
{

    awt = 0;                                //Initial wait time is 0
    att = 0;                                //Initial turnaround time is 0
    double total_burst_time=0;              //total burst time initalized to 0
    double total_turnaround=0;              //Total Turn around time for all processes
    double total_wait = 0;                  //total wait time initalized to 0
    

    //Make a deep copy of all the processes so original is not changed
    process_info tempArr[size];
    for (int i = 0; i <size; i ++)
    {
        tempArr[i] = arr[i];
    }

    while (AllProcessesComplete(size,tempArr) != true)  //Make sure some processs still need the CPU
    for (int i = 0; i<size;i++)                         //Iterate through array
    {
        //If the process still needs CPU time greater than the time quantum
        if (tempArr[i].remainingCPUBurstTime >=quantum)
        {       
                //If the process needs exactly the quantum time of the cpu it will be his last time in the cpu
                if (tempArr[i].remainingCPUBurstTime == quantum)
                    {            
                    //Incriment the total burst time by the quantum (the amount of cpu time this process just used.)
                    total_burst_time += tempArr[i].remainingCPUBurstTime;

                    //Incriment total turnaround adding the time that this process finished. This process finished at the current total burst time.
                    total_turnaround += total_burst_time; 

                    //Current total_burst is the time this process just completed at.
                    //Find wait time using the (completion time - burst time) and add it to the running total_wait 
                    total_wait +=  total_burst_time - tempArr[i].cpuBurstTime; 
                    //Mark this process completed using a -1
                    tempArr[i].remainingCPUBurstTime = -1;                           
                    }
                
                //If process has more than quantum time left in cpu burst then it is not the processes last time in the CPU
                else
                    {
                        total_burst_time += quantum;                    //Add the quatum time to the burst time
                        tempArr[i].remainingCPUBurstTime -= quantum;    //Subtract the quantum time from the remaining cpu burst time
                    }
        }
        //Else if a process has less than the quantum time left it will be his last time in the cpu
        else if (tempArr[i].remainingCPUBurstTime < quantum && tempArr[i].remainingCPUBurstTime >0)
        {    
            //Incriment the total burst time by the remaining burst time (the amount of cpu time this process just used.)
            total_burst_time += tempArr[i].remainingCPUBurstTime;

            //Incriment total turnaround adding the time that this process finished. This process finished at the current total burst time.
            total_turnaround += total_burst_time; 

            //Current total_burst is the time this process just completed at.
            //Find wait time using the (completion time - burst time) and add it to the running total_wait 
            total_wait = total_wait + (total_burst_time - tempArr[i].cpuBurstTime); 
            //Mark the process as completed using a -1
            tempArr[i].remainingCPUBurstTime = -1;
        }
        //Else, the process is already completed, do nothing
        else 
        {
        tempArr[i].remainingCPUBurstTime = -1; //Keep a completed process set to -1
        }
    }

    //Calculate the totals
    awt = (total_wait/size);
    att = total_turnaround/size;
}

/*************************************************************************
                            CompareCPUTimes
This function will compare two process_info data structures using their CPU
times to compare. If CPU_time2 is greater than or equal to CPU_time1 then
this function will return true. Else, this function will return false.
This function will be called by the std::sort function. 
****************************************************************************/
bool CompareCPUTimes(const process_info &process1,const process_info &process2 )
{
if (process2.cpuBurstTime >= process1.cpuBurstTime) {
    return true; //the two processes are already in order
}
else {
    return false; //the two processes are out of order. 
}
}

/*************************************************************************
                            CompareProcessPriority
This function will compare two process_info data structures using their 
priority to compare. If CPU_priority2 is greater than or equal to CPU_priority1 
thenfunction will return true. Else, this function will return false. 
This function will be called by the std::sort function. 
****************************************************************************/
bool CompareProcessPriority(const process_info &process1,const process_info &process2)
{
if (process2.processPriority >= process1.processPriority) 
{
    return true; //the two processes are already in order
}
else {
    return false; //the two processes are out of order. 
}
}
/*************************************************************************
                            AllProcessesComplete
This function returns true if all processes have compelted. Processes that
are completed are marked with a -1. When all processes are marked with a 
-1 then all processes are completed. 
****************************************************************************/
bool AllProcessesComplete(int size, process_info arr[]) 
{
    for (int i = 0; i <size; i ++){
        if (arr[i].remainingCPUBurstTime != -1){
            return false;               
        }
    }
    return true;   
}

/*************************************************************************
                                ShouldPrint
This function determines if it should print the process information and 
results or not. Though, this program will run and record NUMRUMS times
it will not need to print ALL of the results. Instead, it will print the
first three and also print the last run.  Call this function to check if 
the process should be printed instad of using if statements in the program
use this function. This function will return true if i is 0,1,2 or NUMBERRUNS.
****************************************************************************/
bool ShouldPrint(int i)
{
    if (i >=0 && i < 3){
        return true;
    }
    else if (i == NUMBERRUNS-1){
        return true;
    }
    else{
        return false;
    }
}

/*************************************************************************
                                Print Processes
This function prints all processes and their respective information in a 
given array. Parameters are first the size and then the array itself.
This functoin prints the information in an organized form.  
****************************************************************************/
void PrintProcesses(int size, process_info arr[])
{
        cout<<"List of all processes:\n";
        for (int i = 0; i < size; i++)
        {
        cout<<setprecision(2);
        cout <<setw(4)<<"PID#"<< std::setw(3)<<arr[i].processID;
        cout <<setw(15)<<"Burst time :"<<std::setw(5)<<arr[i].cpuBurstTime;
        cout<<setw(13)<<"Priority :"<< arr[i].processPriority<<"\n";
        }
}

/*************************************************************************
                                Fill_Array_Tester
This function is not used within this program. Instead it can be used later
for testing purposes. If using this function to test, ensure to update the 
MAXPROCESSES at the top of the program in the define section.
****************************************************************************/
void fillArrayTester(int size, process_info arr[])
{
// arr[0].processID = 1;
// arr[0].cpuBurstTime = 24;
// arr[0].remainingCPUBurstTime = arr[0].cpuBurstTime;
// arr[0].processPriority = 6;

// arr[1].processID = 2;
// arr[1].cpuBurstTime = 3;
// arr[1].remainingCPUBurstTime = arr[1].cpuBurstTime;
// arr[1].processPriority = 3;

// arr[2].processID = 3;
// arr[2].cpuBurstTime = 3;
// arr[2].remainingCPUBurstTime = arr[2].cpuBurstTime;
// arr[2].processPriority = 1;


arr[0].processID = 1;
arr[0].cpuBurstTime = 4;
arr[0].remainingCPUBurstTime = 4;
arr[0].processPriority = 6;

arr[1].processID = 2;
arr[1].cpuBurstTime = 9;
arr[1].remainingCPUBurstTime = 9;
arr[1].processPriority = 3;

arr[2].processID = 3;
arr[2].cpuBurstTime = 4;
arr[2].remainingCPUBurstTime = 4;
arr[2].processPriority = 1;

arr[3].processID = 4;
arr[3].cpuBurstTime = 10;
arr[3].remainingCPUBurstTime = 10;
arr[3].processPriority = 9;

arr[4].processID = 5;
arr[4].cpuBurstTime = 6;
arr[4].remainingCPUBurstTime = 6;
arr[4].processPriority = 5;
}

