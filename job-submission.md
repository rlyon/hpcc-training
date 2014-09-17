---
layout: default
title: Submitting Jobs to the Cluster
---

At it's core, submitting a job to the cluster requires little more than adding the command that you would like to run to a text file much like the scripts that you created previously and passing that file to a program called qsub.  In fact, by default, the batch server will treat the file that is passed as a bash script.   

## Submission Scripts

In our basic example, your submission script will only contain the command that you want to run.  Using the stats.sh script that we created in the last section, we can submit a job to the cluster by adding the command to a file and running with qsub.

Change to the ```tutorial``` directory where you created the ```stats.sh``` script in the previous tutorial.  Now using the text editor, create a file called ```stats.pbs``` and put the following line in it:

```sh
./stats.sh *.txt 
```

You will notice that even though the script is technically a shell script, that I used the file extension ```pbs```.  You can use any extension when you create your file and it will work the same.  Using the ```pbs``` extension will help to differentiate your submission scripts from other regular shell scripts. 

Hand off the submission script to the cluster by running the ```qsub``` command:

```text
go.cougs@login1 ~/tutorial $ qsub stats.pbs 
4917957.mgt1.wsuhpc.edu
```
## Qsub

The ```qsub``` command that was run above displayed a job identifier that you can use to track the job. Your identifier will not be identical to the one in the example. 

It may take a few minutes for the job to get picked up by the scheduler and if the cluster is busy, it may take a while for it to actually be run.  You can check on the status of your job with the ```qstat``` command.

```text
go.cougs@login1 ~/tutorial $ qstat
Job id                    Name             User            Time Use S Queue
------------------------- ---------------- --------------- -------- - -----
4917957.mgt1              stats.pbs        go.cougs        0        Q batch
```

Let's look at the columns.  

* The ***Job id*** column is just that.  It is an identifier that allows the batch server, the scheduler and you to track the job throughout its lifecycle.  We will use the job ID more in a later tutorial when we start developing scripts that can handle job dependencies.
* The ***Name*** column is a human name for your job.  As you will see in the next section, we can actually define the name to create meaningful tracking.  By default this is set as the name of the file that was passed to qsub.
* The ***User*** column will be your username.
* The ***Time Use*** column will show how long the job has been running.
* The ***S*** column stands for ***State***.  This column will tell you where your job is in it's lifecycle.  Some of the most common states that you will see represented in the column are:
    * ```C``` -  Job is completed after having run.
    * ```E``` -  Job is exiting after having run.
    * ```H``` -  Job is held.
    * ```Q``` -  Job is queued, eligible to run or routed.
    * ```R``` -  Job is running.
    * ```W``` -  Job is waiting for its execution time.
* The last column is the ***Queue*** column and will be discused in a later tutorial.
 
Looking back to the ```qstat``` output, the job that was just submitted is now in a queued state.  If you keep running the qstat command, you may see it in a running state and then finally in a completed state.

```text
go.cougs@login1 ~/tutorial $ qstat
Job id                    Name             User            Time Use S Queue
------------------------- ---------------- --------------- -------- - -----
4917957.mgt1              stats.pbs        go.cougs        00:00:00 C batch  
```

When you list the files in the directory you will see two new files.  

```text
go.cougs@login1 ~/tutorial $ ls
hello.sh          shakespeare-comedy-7.txt   shakespeare-taming-2.txt    stats.pbs.e4917957  World.txt.backup
hello.txt.backup  shakespeare-hamlet-25.txt  shakespeare-tragedy-58.txt  stats.pbs.o4917957
moved             shakespeare-romeo-48.txt   stats.pbs                   stats.sh
```

The new files for this run are ```stats.pbs.o4917957``` and ```stats.pbs.e4917957```.  Some of the components of this file name should look familiar.  The stats.pbs portion is the filename that we gave to ```qsub```, but it is also the job name.  The numerical value on the end of the file name is the numerical portion of the job ID.  The ```o``` and the ```e``` portion of the file represent the output and error streams.

Taking a look at the output or ```o``` file, you will find that it is empty:

```text
go.cougs@login1 ~/tutorial $ cat stats.pbs.o4917957

```

We are missing is the output seen previously that came from the stats.sh script.

To figure out what happened, go to the error file and print its contents to the screen.

```text
go.cougs@login1 ~/tutorial $ cat stats.pbs.e4917957
/var/spool/torque/mom_priv/jobs/4917957.mgt1.wsuhpc.edu.SC: line 1: ./stats.sh: No such file or directory
```

It looks like it couldn't find the stats.sh file when we tried to run it in the script.  There's a very easy fix for this and a good learning opportunity.  ***When a job is run on an execution node the path is automatically set to the top of your home directory.***  To fix this, we just need to modify the submission script to change into the *tutorial* directory that the ```stats.sh``` script lives in before it is run.  Once modified, your ```stats.pbs``` file should look similar to this:

```sh
cd $HOME/tutorial
./stats.sh *.txt
```

Use ```qsub``` to submit the job again.

```text
go.cougs@login1 ~/tutorial $ qsub stats.pbs
4917959.mgt1.wsuhpc.edu
```
Once ```qstat``` shows the run as complete, then check the output file.  You will find the output of the stats.sh script:

```text
Getting stats for shakespeare-comedy-7.txt
Lines: 2851
Words: 16252
Characters: 89439
Getting stats for shakespeare-hamlet-25.txt
Lines: 5877
Words: 32242
Characters: 182399
Getting stats for shakespeare-romeo-48.txt
Lines: 4579
Words: 25919
Characters: 144138
Getting stats for shakespeare-taming-2.txt
Lines: 4039
Words: 22207
Characters: 124128
Getting stats for shakespeare-tragedy-58.txt
Lines: 5588
Words: 31681
Characters: 180293
```

The next section will describe some of the basic options and variables that you can use with your submission scripts and the ```qsub``` command.
