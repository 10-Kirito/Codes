cc = g++

objects_1 = Process_schedule.o Process.o Cpu.o




test1 : $(objects_1)
	g++ -o test1 $(objects_1)

Process_schedule.o: Process.h Cpu.h

Process.o: Process.h

Cpu.o: Cpu.h tools.h

.PHONY :clean
clean:
	del test1 $(objects_1)
