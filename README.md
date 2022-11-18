# CPU Job Scheduling Solver/Calulator 
# How To Run
In order to run this program you must first download all source code. Next, in a terminal or IDE you will navigate to the location where the 
saved source code is located. This program contains a makefile which will automatically compile the c++ code and turn it into an executible.
In order to take advantage of the makefile you must go to the terminal and type "make" without the quotation marks. This will create the executible
file which will be named "cpu". In order to run this executible file you must type ./cpu in your termial. Ensure that you are in the correct location
in the terminal where the executible file and all source code are located or this will not work. After typing ./cpu the program will be run and the
results will be displayed on your screen. In order to remove any executible files you may type "make clean" inside of the terminal.


## Description

This program was created for Operating Systems class at Cameron University. This program fufills all assignment requirements. Namely, it solved the 
the average turn around time (ATT) and the the average wait time (AWT) for 4 CPU job scheduling algorithums for 10 processes all arriving at time zero. 
This program uses a random number generator to create random burst time for x amount of processes. Each process will be represented
as a structure containing important information about the process such as ID, burst time, remaining burst time and priority. 
The strucures representing the processes will be stored in a fixed array. The number of processes may be changed by changing the define
MAXPROCESSES at the top in the hard code. This program assumes that all processes are arriving at time zero. This may be something to update later, to allow 
for differnt arrival times. This program then is able to solve for 4 different CPU job scheduling algorithums namely, it solves for 
First Come First Serve (FCFS), Shortest Job First (SJF), Priority Queue and Round Robin. Each scheduling algorithum, once called, 
will return by value result argument (by refernece) the average wait time (AWT) and the average turn around time (ATT) for the total of all 
processes within the array. The results will be printed in main. This program, based on the instrcutions given, must run in a loop 100 times. 
This will generate random arrays of processes and find their averages of the 100 runs and display them on the screen. Inside of main, a 
running loop will be kept to find the average of all 100 averages, as per instructions. 


## Getting Started

### Dependencies
The instructions for this program are written for running on a UNIX or LINUX with all c++ dependencies already installed. 

### Installing
https://github.com/rvanderlely/CPU-Job-Scheduler


### Executing program

```
make 
```
```
./cpu
```

## Help

Ensure that you are in the proper folder before attempting to run program. 
Type in your termial:
```
ls
```
to ensure that the rachel_cpu_job_scheduler.cpp and rachel_cpu_job_scheduler.o and cpu files are all in the current location.
If you are not in the correct folder you must navigate to the correct folder before attempting to run.
## Authors

Rachel Vanderlely  
[@Rachel Vanderlely](https://github.com/rvanderlely)

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## License

This project is licensed under the Rachel Vanderlely License - see the LICENSE.md file for details

## Acknowledgments

Instructions for project given by Dr.Zhao of Cameron University
