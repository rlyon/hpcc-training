---
layout: default
title: Environment Modules
---

Because we need to manage multiple versions of software, most of our software is not installed in the standard paths that you would normally find executable files.  To customize the users environment we use a utility called **environment modules**.  This program manages all of the various paths and environment variables required for you to access the software on the cluster.  

## Using the module command

### module avail

To display the available applications available to the user, use the ```module avail``` command.

```
$ module avail

------------------------------ /home/software/Modules/versions ------------------------------
3.2.8

------------------------- /home/software/Modules/3.2.8/modulefiles --------------------------
dot         module-cvs  module-info modules     modulestest null        use.own

-------------------------------- /home/software/modulefiles ---------------------------------
BEAST/1.6.2                                 lammps/31Oct13_intel_mpi
PETSc/petsc-3.1-p8_openmpi_intel            libcvd/20120202
PETScExt/linux_x86_64_openmpi_intel         libffi/3.0.13
R/R-3.0.2                                   libgd/2.1.0
R/R-3.0.3                                   libpcap/1.2.1_gcc
R/R-3.0.3a                                  libpng/1.6.10
R/R-3.1.0                                   lunzip/1.4
...
he25/v1.3_intel                             scons/2.1.0
intel/11.1.075                              structure/2.3.3
intel/composer_xe_2011_sp1.9.293            szip/2.1_gcc
isl/0.12.2                                  szip/2.1_intel
jdk/1.6.0_25                                szip/2.1_intel_12.1.3.293
jdk/1.7.0_51                                underworld/1.6.0_intel
```

The applications are displayed in the form ```name/version```.  

### module load

To load a module use the ```module load``` command with the name and version of the application you would like to load.  For example, if you would like to load the BEAST application, use the following:

```
$ module load BEAST/1.6.2
```

There is no output unless there is an error.  

### module list

The application and all the commands associated with it will now be available to you.  To list the modules that you currently have loaded, you can use the ```module list``` command.

```
$ module list
Currently Loaded Modulefiles:
  1) modules       2) BEAST/1.6.2

```

### module help

To get information about individual modules, use the ```module help``` command.

```
$ module help BEAST/1.6.2

----------- Module Specific Help for 'BEAST/1.6.2' ----------------

    BEAST is a cross-platform program for Bayesian MCMC analysis of molecular sequences

	This adds /home/software/BEASTv1.6.2/* to several of the
	environment variables.

	Version 1.6.2
```

### module unload

To remove the changes a module has made to your environment, you will need to unload the module.

```
$ module unload BEAST/1.6.2
$ module list
Currently Loaded Modulefiles:
  1) modules
```

## Loading modules automatically when you log in

There is a hidden file at the root (top) your home directory named ```.bashrc``` the contents of this file are evaluated everytime you log in (assuming you are still using the default Bash shell).  To load a module or modules when you log in, open the file in your favorite text editor and add the ```module load <name/verision>``` command to the end of the file.

