---
layout: default
title: Introduction to MPI
---

### Parallel computing models

Parallel models are usually divided into 3 models depending on process interation and problem decomposition.

#### SIMD

SIMD is a data parallel model where the same instructions are carried out simultaniously on multiple data items.  When we created the wrapper for submitting all of our files as jobs at the same time we were following a SIMD model.

#### MIMD

MIMD is a task parallel model where different instructions are carried out simultaniously on multiple data items.  

#### SPMD

SPMD refers to a single program perfoming operations on multiple data items.  SMPD can be can be equivalent to MIMD as each MIMD program can be made SMPD.



### Message passing interface

Message passing is used for SPMD and MIMD parallelism and the message passing interface (MPI) is an interface into the message passing model, abstracting the difficult tasks of communication and synchronization.

MPI provides a language agnostic protocol that is used to program parallel sytems.  Although not officially sanctioned by any major standards body, MPI has become the standard for process communication when running on a distributed memory system.  There are many implementations of this standard across multiple languages.  Most implementations combine C, C++ and assembly. Some languages that have MPI bindings to the C implementations include R, Perl, Ruby, python, fortran and java.

The power of MPI is that it provides a virtual topology which in simple terms, helps to disolve the physical boundaries of machines.

![A single server running an application](images/mpi-single-server.jpg)

 Laptops, desktops, and regular servers have a physical boundary even if you plug them into the internet.  Unless there are applications installed that can connect remotely with specific protocols, it cannot talk to or share data with lets say, the system that I am typing this on.

![Multiple servers running the same application](images/mpi-multi-server.jpg)

Even with the same application running on several other servers, there is still that physical boundry.  MPI softens those physical boundaries and allows the application to span multiple systems synchronizing and coordinating processes and memory.

![Multiple servers running the same application with MPI](images/mpi-application.jpg)

### Running an MPI program

There is no specifically defined way to run an mpi progam and in general, starting the program can vary depending on the implimentation and the environment.  In most environments you will usually find two programs used to start programs that have been compiled against MPI libraries.  The programs ```mpiexec``` and ```mpirun``` at one time had different uses, but with the MPI-2 standard, they are usually synonyms for the same program.  Using any of the programs to run will produce the same behavior.

If you are looking to run a simple MPI program, you will just preface your command with mpirun.

```text
$ mpirun [-np X ] [ --hostfile <filename> ] [program]
```

In certain tightly integrated environments where the mpi implimentation has been compiled with knowledge of the batch server, mpirun will contact the batch server for information regarding the number of processors and hosts leaving the user to only specify the program.

```text
$ mpirun [[program]
```
