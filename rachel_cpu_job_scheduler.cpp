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
#include <cstdlib> // for random number 
#include <ctime> 
#define MAXPROCESSES 10
using std::cout;
using std::cin;
using std::sort;

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
int random_priority();

/*************************************************************************
                                Main Function
****************************************************************************/
int main()
{
    //if need to run 100 times then make variables here
    double awtFCFS = 0;
    double attFCFS = 0;
    double awtSJF = 0;
    double attSJF = 0;
    double awtPri = 0;
    double attPri = 0;
    double awtRR = 0;
    double attRR = 0;

    // Providing a seed value once for entire program
    srand((unsigned) time(NULL));

    //Create an array of size 100 to hold 100 processes
    struct process_info processes[MAXPROCESSES];

    //Fill the process array infor with processes
    fill_array_with_processes(MAXPROCESSES, processes);

    //Call FCFS and Print
    cout<<"\n\nFIRST COME FIRST SERVE:\n";
    cout<<"---------------------------\n";
    FCFS(MAXPROCESSES, processes, awtFCFS,attFCFS);
    cout<<"The AWT is "<<awtFCFS<<"\n";
    cout<<"The ATT is "<<attFCFS<<"\n";
    cout<<"---------------------------\n";

    //Call SJF and Print
    cout<<"SHORTEST JOB FIRST :\n";
    cout<<"---------------------------\n";
    SJF(MAXPROCESSES, processes,awtSJF,attSJF);
    cout<<"The AWT is "<<awtSJF<<"\n";
    cout<<"The ATT is "<<attSJF<<"\n";
    cout<<"---------------------------\n";

    //Call Priority and Print
    cout<<"PRIORITY SCHEDULING :\n";
    cout<<"---------------------------\n";
    Priority(MAXPROCESSES, processes,awtPri,attPri);
    cout<<"The AWT is "<<awtPri<<"\n";
    cout<<"The ATT is "<<attPri<<"\n";
    cout<<"---------------------------\n";

    //Call Round Robin
    cout<<"ROUND ROBIN :\n";
    cout<<"---------------------------\n";
    RoundRobin(MAXPROCESSES, processes,awtRR,attRR,4);
    cout<<"The AWT is "<<awtRR<<"\n";
    cout<<"The ATT is "<<attRR<<"\n";
    cout<<"---------------------------\n";
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
 total_wait = total_burst_time;             //wait time starts at 0 then each subsequent process waits
 //cout<<"\n\nTotal wait time is:"<<total_wait<<"";
 total_burst_time += arr[i].cpuBurstTime;     //Calculate burst time of all processes
 //cout<<"\nTotal burst time is:"<<total_burst_time<<"\n"; 
 }
    cout<< "Total burst"<<total_burst_time<<"\n";
    cout<< "Total wait"<<total_wait<<"\n";
    //Calculate the awt and att and change them by reference
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
    cout<<"List of all processes:\n";
    cout<<"---------------------------------------\n";
    for (int i = 0;i<size;i++)
        {
        //assign a process ID in order
        arr[i].processID = i+1;
        cout<<"The process ID "<< arr[i].processID;
        //assign a CPU Burst time
        arr[i].cpuBurstTime = random_cpu_burst();
        cout<<" Burst time :"<< arr[i].cpuBurstTime;
        arr[i].processPriority = random_priority();
        cout<<"Priority :"<< arr[i].processPriority<<"\n";
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

    // //Print the array
    // cout<<"Before sorting:\n";
    //     for (int i = 0; i <size; i ++){
    //     if (i%10 == 0 ){cout<<"\n";}
    //     cout<<tempArr[i].cpuBurstTime<< "\t";
    // }

    //Sort the array in assending order
    sort(tempArr,(tempArr + size),CompareCPUTimes);

    // //Print the sorted array 
    //   cout<<"\n\nAfter sorting:\n";
    //     for (int i = 0; i <size; i ++){
    //     if (i%10 == 0 ){cout<<"\n";}
    //     cout<<tempArr[i].cpuBurstTime<< "\t";
    // }
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

    // //Print the array
    // cout<<"Before sorting Priority:\n";
    // cout<<"\n\nAfter sorting by priority:\n";
    // for (int i = 0; i <size; i ++){
    // if (i%10 == 0 ){cout<<"\n";}
    // cout<<tempArr[i].processPriority<< "\t";
    // }

    //Sort the array in assending order
    sort(tempArr,(tempArr + size),CompareProcessPriority);

    // //Print the sorted array 
    //   cout<<"\n\nAfter sorting by priority:\n";
    //     for (int i = 0; i <size; i ++){
    //     if (i%10 == 0 ){cout<<"\n";}
    //     cout<<tempArr[i].processPriority<< "\t";
    // }

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
            //cout<<"Inside IF ";
            //cout<<"process "<<tempArr[i].processID<<" CPU time was: "<<tempArr[i].cpuBurstTime<<" ";
            tempArr[i].cpuBurstTime -= quantum;
            total_wait = total_burst_time;  //wait time starts at 0 then each subsequent process waits
            total_burst_time += quantum;
            //cout<<"New burst time is:"<<total_burst_time<<"\n";
            //cout<<"process "<<tempArr[i].processID<<" time quantum is now: "<<tempArr[i].cpuBurstTime<<" \n";
            }
            else if (tempArr[i].cpuBurstTime < 4 && tempArr[i].cpuBurstTime >0)
            {        
            //cout<<"Inside ELSE ";
            //cout<<"process "<<tempArr[i].processID<<" time quantum was: "<<tempArr[i].cpuBurstTime<<" ";
            total_wait = total_burst_time;  //wait time starts at 0 then each subsequent process waits
            total_burst_time += tempArr[i].cpuBurstTime;
            tempArr[i].cpuBurstTime -= tempArr[i].cpuBurstTime;
           // cout<<"New burst time is:"<<total_burst_time<<"\n";
            //cout<<"process"<<tempArr[i].processID<<"The time quantum is now: "<<tempArr[i].cpuBurstTime<<" \n";
            }
            else 
            {
            tempArr[i].cpuBurstTime = -1;
            //cout<<"process"<<tempArr[i].processID<<"The time quantum is now: "<<tempArr[i].cpuBurstTime<<" \n";
            }
        }

    cout<< "Total burst"<<total_burst_time<<"\n";
    cout<< "Total wait"<<total_wait<<"\n";

    awt = total_wait/size;
    att = ((total_burst_time + total_wait)/size);
    // need to minus the quantum each time until you hit 

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
    if (process2.processPriority >= process1.processPriority) {
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