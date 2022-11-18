cpu: rachel_cpu_job_scheduler.o
	g++ rachel_cpu_job_scheduler.o -o cpu

rachel_cpu_job_scheduler.o: rachel_cpu_job_scheduler.cpp
	g++ -c rachel_cpu_job_scheduler.cpp
clean:
	rm *.o cpu