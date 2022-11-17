/*************************************************************************
*	Projec name: CPU Scheduling Algorithum
*	Author:		 Rachel Vanderlely
*   Professor:   Dr.Zhao
*	Date:		 November 12, 2022
*	Class:		 CS3513
*	Purpose:	 To simulate CPU schdeduling algorithims FCFS, SJF and RR
*                at 4 and 8 quantum seconds.  
****************************************************************************/
#include <iostream> //Input output
#include <iomanip>
#include <cstdlib> // for random number 
#include <ctime> 
#define MAXPROCESSES 5
#define NUMBERRUNS 100
using std::cout;
using std::cin;
using std::sort;
using std::setw;
using std::fixed;
using std::setprecision;
/*************************************************************************
                                process_info
This structure holds information about a process, namely the CPU
burst time and the processID of a process. 
****************************************************************************/
struct process_info
{
    int processPriority;
    int processID;
    double cpuBurstTime;
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

    //All variables needed to hold awt, att and averages
    double awtFCFS = 0;
    double attFCFS = 0;
    double awtSJF = 0;
    double attSJF = 0;
    double awtPri = 0;
    double attPri = 0;
    double awtRR = 0;
    double attRR = 0;
    double awtFCFSAvg = 0;
    double attFCFSTAvg = 0;
    double awtSJFAvg = 0;
    double attSJFAvg = 0;
    double awtPriAvg = 0;
    double attPriAvg= 0;
    double awtRRAvg = 0;
    double attRRAvg = 0;


    for (int i = 0; i< NUMBERRUNS; i++)
    {

    //Set every cout statement in the program to fixed
    cout<<fixed;
    
    //Create an array of size MAXPROCESSES to hold MAXPROCESSES processes
    struct process_info processes[MAXPROCESSES];

    //Fill the process array infor with processes
    //fill_array_with_processes(MAXPROCESSES, processes);

    fillArrayTester(MAXPROCESSES,processes);

    //Print only processes 1,2,3 and 100
     if (ShouldPrint(i) == true)
     {
        cout<<"\n=====================================================\n";
        cout<<"\t\tRUN #: "<<i+1;
        cout<<"\n=====================================================\n";
        PrintProcesses(MAXPROCESSES,processes);
     }

    //Call FCFS and Print only runs processes 1,2,3 and 100
    FCFS(MAXPROCESSES, processes, awtFCFS,attFCFS);
    if (ShouldPrint(i) == true)
    {
    cout<<"-----------------------\n";
    cout<<"FIRST COME FIRST SERVE\n";
    cout<<"-----------------------\n";
    cout<<fixed<<"The AWT is "<<setprecision(4)<<setw(9)<<awtFCFS<<" |\n";
    cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attFCFS<<" |\n";
    cout<<"-----------------------\n";
    }

    //Call SJF and Print only runs processes 1,2,3 and 100
    SJF(MAXPROCESSES, processes,awtSJF,attSJF);
    if (ShouldPrint(i) == true)
    {
    cout<<"SHORTEST JOB FIRST \n";
    cout<<"-----------------------\n";
    cout<<"The AWT is "<<setprecision(4)<<setw(9)<<awtSJF<<" |\n";
    cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attSJF<<" |\n";
    cout<<"-----------------------\n";
    }

    //Call Priority and Print only runs processes 1,2,3 and 100
    Priority(MAXPROCESSES, processes,awtPri,attPri);
    if (ShouldPrint(i) == true)
    {
    cout<<"PRIORITY SCHEDULING \n";
    cout<<"-----------------------\n";
    cout<<"The AWT is "<<setprecision(4)<<setw(9)<<awtPri<<" |\n";
    cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attPri<<" |\n";
    cout<<"-----------------------\n";
    }

    //Call Round Robin and Print only runs processes 1,2,3 and 100
    RoundRobin(MAXPROCESSES, processes,awtRR,attRR,4);
    if (ShouldPrint(i) == true)
    {
    cout<<"ROUND ROBIN \n";
    cout<<"-----------------------\n";
    cout<<"The AWT is "<<setprecision(4)<<setw(9)<<awtRR<<" |\n";
    cout<<"The ATT is "<<setprecision(4)<<setw(9)<<attRR<<" |\n";;
    cout<<"-----------------------\n";
    }

    //Calculate the total of MAXRUN runs
    awtFCFSAvg += awtFCFS;
    attFCFSTAvg += attFCFS;
    awtSJFAvg += awtSJF;
    attSJFAvg += attSJF;
    awtPriAvg += awtPri;
    attPriAvg += attPri;
    awtRRAvg += awtRR;
    attRRAvg += attRR;

    }

    //Calculate the averages by dividing the totals by the number of runs
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
    cout<<"AVERAGE ROUND ROBIN \n";
    cout<<"--------------------------\n";
    cout<<"AVERAGE AWT is "<<setprecision(4)<<setw(9)<<awtRRAvg<<" |\n";
    cout<<"AVERAGE ATT is "<<setprecision(4)<<setw(9)<<attRRAvg<<" |\n";;
    cout<<"--------------------------\n";
    return 0;
}


/*************************************************************************
                                random_cpu_burst
This function generates random numbers between 1.0 and 20.0 and returns
them as a double. 
****************************************************************************/
double random_cpu_burst()
{
return ( ((double)(rand()%21) / 20.0)  + (rand()%20));
}

/*************************************************************************
                                random_priorty
This function generates random priority between 1.0 and 20.0 and returns
them as a double. 
****************************************************************************/
int random_priority()
{
return  ((rand()%100)  + 1);
}

/*************************************************************************
                                FCFS 
This function take an array of processes and then calculate the individual 
AWT and ATT. Then add them all up and print out the averages. 
****************************************************************************/
void FCFS(int size, process_info arr[],double &awt, double &att)
{
    awt = 0;                                //Initial wait time is 0
    att=0;                                  //Initial turnaround time is 0
    double total_burst_time=0;              //total burst time initalized to 0
    double total_wait = 0;                  //total wait time initalized to 0

 for (int i=0; i <size;i++)                 //Iterate through all processes
 {
 total_wait += total_burst_time;             //wait time starts at 0 then each subsequent process waits
 total_burst_time += arr[i].cpuBurstTime;   //Calculate burst time of all processes
 }
    awt = total_wait / size ;
    att = ((total_wait + total_burst_time) /size);
}

/*************************************************************************
                    Void fill_array_with_processses
This function takes in an array, by referance as well as its size and it 
fills the array with processes 1 through size with random CPUBurst times 
****************************************************************************/
void fill_array_with_processes(int size, process_info arr[])
{
    for (int i = 0;i<size;i++)
        {
        //Assign a process ID in order
        arr[i].processID = i+1;
        arr[i].cpuBurstTime = random_cpu_burst();
        arr[i].processPriority = random_priority();
        }
    return;
}

/*************************************************************************
                                SJF
****************************************************************************/
void SJF(int size, process_info arr[],double &awt, double &att)
{
    awt = 0;                         //Initial wait time is 0
    att=0;                           //Initial turnaround time is 0
    

    //Make a deep copy of all the processes so original is not changed
    process_info tempArr[size];
    for (int i = 0; i <size; i ++)
    {
        tempArr[i] = arr[i];
    }

    //Sort the array in assending order
    sort(tempArr,(tempArr + size),CompareCPUTimes);
    //Now call the FCFS function on the array sorted by CPU burst time
    FCFS(MAXPROCESSES,tempArr, awt, att);
}

/*************************************************************************
                                Priority 
****************************************************************************/
void Priority(int size, process_info arr[],double &awt, double &att)
{
    awt = 0;                         //Initial wait time is 0
    att=0;                           //Initial turnaround time is 0
    double total_burst_time=0;              //total burst time initalized to 0
    double total_wait = 0;                  //total wait time initalized to 

    //Make a deep copy of all the processes so original is not changed
    process_info tempArr[size];
    for (int i = 0; i <size; i ++)
    {
        tempArr[i] = arr[i];
    }

    //Sort the array in assending order
    sort(tempArr,(tempArr + size),CompareProcessPriority);
    //Now call the FCFS function on the array sorted by CPU burst time
    FCFS(MAXPROCESSES,tempArr, awt, att);
}

/*************************************************************************
                                Round Robin 
This function take an array of processes and then calculate the individual 
AWT and ATT. Then add them all up and print out the averages. 
****************************************************************************/
void RoundRobin(int size, process_info arr[],double &awt, double &att, int quantum)
{

    awt = 0;                                //Initial wait time is 0
    att = 0;                                  //Initial turnaround time is 0
    double total_burst_time=0;              //total burst time initalized to 0
    double total_wait = 0;                  //total wait time initalized to 0
    

    //Make a deep copy of all the processes so original is not changed
    process_info tempArr[size];
    for (int i = 0; i <size; i ++)
    {
        tempArr[i] = arr[i];
    }

    while (AllProcessesComplete(size,tempArr) != true)
        for (int i = 0; i<size;i++)
        {
            if (tempArr[i].cpuBurstTime >=4)
            {
            tempArr[i].cpuBurstTime -= quantum;
            total_wait = total_burst_time;  //wait time starts at 0 then each subsequent process waits
            total_burst_time += quantum;
            }
            else if (tempArr[i].cpuBurstTime < 4 && tempArr[i].cpuBurstTime >0)
            {        
            total_wait = total_burst_time;  //wait time starts at 0 then each subsequent process waits
            total_burst_time += tempArr[i].cpuBurstTime;
            tempArr[i].cpuBurstTime -= tempArr[i].cpuBurstTime;
            }
            else 
            {
            tempArr[i].cpuBurstTime = -1;
            }
        }

    awt = total_wait/size;
    att = ((total_burst_time + total_wait)/size);
}

/*************************************************************************
                                CompareCPUTimes
This function will compare two process_info data structures using their CPU
times to compare. If CPU_time2 is greater than or equal to CPU_time1 then
this function will return true. Else, this function will return false. 
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

****************************************************************************/
bool AllProcessesComplete(int size, process_info arr[]) 
{
    for (int i = 0; i <size; i ++)
    {
        if (arr[i].cpuBurstTime != -1)
        {
            return false;               //Some processes still have burst time left
        }
    }
    return true;
    
}

/*************************************************************************
                                ShouldPrint
This function determines if it should print the process information and 
results or not. Though, this program will run and record NUMRUMS times
it will not need to print ALL of the results. Instead, we will print the
first three and also print the last one. Instread of having just a bunch 
of if statements in the program we will call this function to check if 
the process should be printed. 
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
****************************************************************************/
void PrintProcesses(int size, process_info arr[])
{
        cout<<"List of all processes:\n";
        //cout<<"--------------------------------------------------\n";
        //Assign a process ID in order
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
****************************************************************************/
void fillArrayTester(int size, process_info arr[])
{
arr[0].processID = 1;
arr[0].cpuBurstTime = 4;
arr[0].processPriority = 6;
arr[1].processID = 2;
arr[1].cpuBurstTime = 9;
arr[1].processPriority = 3;
arr[2].processID = 3;
arr[2].cpuBurstTime = 4;
arr[2].processPriority = 1;
arr[3].processID = 4;
arr[3].cpuBurstTime = 10;
arr[3].processPriority = 9;
arr[4].processID = 5;
arr[4].cpuBurstTime = 6;
arr[4].processPriority = 5;
}
