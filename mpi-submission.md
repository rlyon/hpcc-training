---
layout: default
title: Submitting MPI Jobs
---

In the mpi folder of the hpcc-tutorials directory there is a test file that we can use to get an understanding of how an MPI program is compiles and submitted.  Move to the directory and open it up.

```c
######################################################
# hello.c
# http://www.slac.stanford.edu/comp/unix/farm/mpi.html
######################################################
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);

  printf("Process %d on %s out of %d\n", rank, processor_name, numprocs);

  MPI_Finalize();
}

```

The contents and function of the file are beyond the scope of this section, but keep in mind that in order for an program to run in parallel on a cluster or between distributed systems, it must include and recognize MPI specific functions.

Passing a program that has not been programmed and compiled specifically for a parallel environment to mpirun, will result in the program running with only a single process.  It's the MPI functions that allow the original or starting process to spawn processes on multiple systems.

The program will be compiled with mpi specific compiler that will add the appropriate libraries and header paths to the underlying compiler (be it gcc, Intel or PGI).  To compile the hello.c program make sure you have the our openmpi module loaded and run the mpicc command.

```text
$ module load openmpi
$ mpicc hello.c -o hello
```

Next make the submission script.  Place the following into a file called mpi-hello.pbs

```sh
#PBS -l nodes=4:ppn=4
#PBS -j oe
#PBS -o hello.out
module load openmpi

cd $PBS_O_WORKDIR

mpirun hello
```

In this submission script we are using ```directives``` to pass options to qsub.  In a PBS environment, the directive lines will allways begin with ```#PBS```.  The script also ensures that the 


```text
$ cat hello.out 
Process 3 on node5 out of 4
Process 0 on node5 out of 4
Process 1 on node5 out of 4
Process 2 on node5 out of 4
Process 7 on node5 out of 16
Process 1 on node5 out of 16
Process 11 on node5 out of 16
Process 2 on node5 out of 16
Process 0 on node5 out of 16
Process 8 on node5 out of 16
Process 3 on node5 out of 16
Process 6 on node5 out of 16
Process 10 on node5 out of 16
Process 4 on node5 out of 16
Process 5 on node5 out of 16
Process 9 on node5 out of 16
Process 15 on node4 out of 16
Process 12 on node4 out of 16
Process 14 on node4 out of 16
Process 13 on node4 out of 16
```

One thing to notice is that the processes did not report back in order.  MPI does not guarantee order.  The main process spawns the others and they report back when they have finished.  The time that it takes can be affected by may different things including latency, other processes running on the nodes, system load etc.

Also note that even though we asked for 4 different nodes, that we only ran on 2 distinct nodes.  In this case the scheduler asked the batch server for a node with 4 processors and the batch server responded with node5.  When it asked again node 5 still had resources available so it was passed back to the scheduler.  It was only when node 5 did not have any more resources that node 4 was passed back.
