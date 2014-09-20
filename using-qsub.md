---
layout: default
title: Using qsub
---

All of our clusters have a batch server referred to as the cluster management server running on the headnode. This batch server monitors the status of the cluster and controls/monitors the various queues and job lists. Tied into the batch server, a scheduler makes decisions about how a job should be run and its placement in the queue. 

Qsub interacts with the batch server to add jobs to the queue.  Once a job has been recieved, the batch server will route the job to the appropriate queue, make sure that the appropriate resources are (or will be) available to run the job and then send back a job identifier to qsub, which in turn will output that identifier to the console.

There are several options available and we will cover the basics.  The format for qsub is:

```sh
qsub [options] <script>
```

Remember, you can always use the ```man qsub``` command to get detailed information about the qsub command.

## Common options

There are several options that can be passed to qsub that range from how to contact you when a job moves through its states on the cluster, deciding when a job is eligeble for execution, and creating multiple jobs from a single call.

Some of the most common that you will encounter are:

### Changing the name of a job

By default, your job will be named using the name of the submission file and the numerical identifier.  Often it will be beneficial to create a descriptive name for your job to help differentiate it from other jobs especially if you are using the same submission script to submit thousands of jobs.  You can use the ```-N``` option to define its name.

#### Examples

Use ```submission_1``` for the name of a job.

```sh
qsub -N submission_1 myscript.pbs
```

### Sending emails

In a busy cluster environment, it is often helpful to know when your job has made it through the milestones of the batch server.  The ```-m``` and ```-M``` options let you define the what and who.

The  ```-m``` option is used to set the conditions in which the bactch server will send mail about a job.  This option takes the following values:

* ```b``` - When the job begins.
* ```e``` - When the job ends.
* ```a``` - When the job has been aborted.

The ```-M``` specifies the email address or addresses that will be contacted.  Multiple email addresses are seperated by commas.

#### Examples

Send a notification when the job begins, ends and if it is aborted to a single email address.

```sh
qsub -m abe -M user1@wsu.edu myscript.pbs
```

Send a notification when the job ends to multiple email addresses.

```sh
qsub -m e -M user1@wsu.edu,user@wsu.edu myscript.pbs
```

### Modifying output

By default the batch server creates output files in that are in the following format:

```text
[Name].[oe][Numerical ID]
```

Where the name is the job name that was defined by the user or system, ```o``` or ```e``` represents the output stream (standard out or error) and the numerical identifier being the integer portion of the job ID.

You can control the names of the files and where both the output and error streams will go with the ```-o```, ```-e``` and ```-j``` options.

#### Examples

Write the output stream to a file called *output.log*  and the error stream to a file called *error.log* in the current working directory.

```sh
qsub -o output.log -e error.log myscript.pbs
```

Combine the error and output streams and write them to a file called *output.log*

```sh
qsub -j oe -o output.log
```

### Passing variables

Just as in the section on shell scripting, it can be benificial to generalize scripts so they can be used for many situations.  Since we cannot pass arguments directly to the script at the time of submission, variables can be used to define the environment.  You can pass variables to your scripts at by using the ```-v``` option.

#### Example

Pass a variable called ```NAME``` to the submission script.  The script will be able access it by using ```$NAME```.

```sh
qsub -v NAME="Butch" myscript.pbs
```

### Passing your environment

In certain cases you may want to pass your entire environment to a script.  In the previous section introduced you to the shell, you used a command called ```env``` to list out all of your current environment variables.  Use the ```-V``` option to send all variables listed in this output along with the script to the batch server.

#### Example

```sh
qsub -V myscript.pbs
```

### Environment variables available to scripts
There are several variables that are set by the batch server at times throughout the lifecycle of a job.  These variables are available to any script that is passed to the batch server using ```qsub```.  In the next section, you will use some of these to modify the file stats script that was created in the previous section.

#### PBS\_O\_WORKDIR

Probably, the most common environment variable you will use, this is the directory where the qsub command was run from.

#### PBS_JOBID

Each job is assigned an identifier, is variable holds that identifier.

#### PBS_JOBNAME

The job name that has been assigned to the job.

#### PBS_ENVIRONMENT

This will be set to the value *PBS_BATCH* to indicate the job is being run as a non interactive job, or *PBS_INTERACTIVE* to indicate the job is being run as interactive.

#### PBS\_O\_QUEUE

The name of the original queue that the job was submitted to.

#### PBS_QUEUE

The name of the queue from which the job was executed from.

#### PBS\_O\_HOST

The name of the host where the qsub command was run from.  In our environment it will be *login1* or *login2*.

#### PBS_SERVER

The name of the server that manages the queues and cluster resources.  In our environment it will be *mgt1*.

#### PBS_ARRAYID

The identifier This will be explained in more detail in a later tutorial.

#### PBS_NODEFILE

The path to the temporary file that contains a list of the nodes assigned to the job.  Although this is not used often in our environment, it can be used for setting up custom mpi rings or with other *distributed* applications that are not tightly integrated into our batch system.

### Specifying the length of time a job will run

By default, the maximum time a job will be allowed to run is 4 days.  Unless you let the scheduler know how long a job will run, the job will be terminated once the limit has been reached.  You can use the ```-l``` option to specify the ***walltime*** (wall clock time) that is required for your job.

Walltime is assigned a value in the following format:

```text
[days:[hours:[minutes:[seconds]]]
```

#### Examples

Submit a job that will run for 16 days:

```sh
qsub -l walltime=16:00:00:00 myscript.pbs
```

Submit a job that will run for 4 hours:

```sh
qsub -l walltime=4:00 myscript.pbs
```

