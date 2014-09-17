---
layout: default
title: Job Information
---

# Getting Information About Jobs

There are several tools that are available for getting information about the jobs that run on our cluster.  The most common tools you will use are qstat and showq. 

## qstat

The qstat command (introduced in an earlier tutorial) will show the status of your current jobs on the system or can give you detailed information about a single job.  When used without any options the output will look similar to this:

```
Job id                    Name             User            Time Use S Queue
------------------------- ---------------- --------------- -------- - -----
4929338.mgt1               ..._hard_problem go.cougs        00:00:00 R batch
4929339.mgt1               and_done         go.cougs        00:00:00 C batch
4929340.mgt1               common_cold_cure go.cougs               0 Q batch
4929341.mgt1               due_tommorow     go.cougs               0 H batch
```

The columns that are displayed include the job identifier, the job name, the amount of time a job has been running, the state of the job, and the queue that the job is currently running in or waiting for.

The ***S*** column stands for ***State***.  This column will tell you where your job is in it's lifecycle.  Some of the most common states that you will see represented in the column are:

* ```C``` -  Job is completed after having run.
* ```E``` -  Job is exiting after having run.
* ```H``` -  Job is held.
* ```Q``` -  Job is queued, eligible to run or routed.
* ```R``` -  Job is running.
* ```W``` -  Job is waiting for its execution time.

To get detailed information on an existing job, use ```qstat -f <jobid>```.  There is alot of information that is output to the screen, but the items that you will probably use the most include:

* ```job_state```:  The state your job is in.  See above.
* ```resources_used```: The resources_used items can let you know how long your job has been running for, how much CPU time the job has consumed, and how much memory (real and virtual) the job is using.
* ```exec_host```:  This tells you what servers and processors the job is running on.  If the job is in a idle state this will be empty.
* ```comment```:  This item can contain information regarding why a job is not running. 
* ```Resource_List```: Shows several items related to requested or default resources that the scheduler has reserved for the job.

## showq

The ```showq``` command will give you information regarding all jobs that are currently running or waiting to be run on the cluster.  Unlike the ```qstat``` command, ```showq``` displays all jobs regardless of the user and it breaks up the output into 3 categories: ***active, eligible and blocked***.

***Active*** jobs are currently being run on the execution nodes and ***elegible*** jobs are jobs that meet all the requirements to be run, but are waiting on resources.  A job can be ***blocked*** for many reasons, but the most common is that a user has exceeded the quotas enforced by the scheduler and the jobs are blocked from running.

The output will look like this:

```text
active jobs------------------------
JOBID              USERNAME      STATE PROCS   REMAINING            STARTTIME

4917639            xxxxxxxx    Running     8    22:26:15  Sat Aug  9 11:25:20
4917934            xxxxxxxx    Running     4  1:12:21:19  Mon Aug 11 13:20:24
...
4917948            xxxxxxxx    Running    40 19:19:24:58  Tue Aug 12 08:24:03
4917712            xxxxxxxx    Running   420 28:08:43:03  Sun Aug 10 21:42:08

24 active jobs        1261 of 2064 processors in use by local jobs (61.09%)
                        103 of 167 nodes active      (61.68%)

eligible jobs----------------------
JOBID              USERNAME      STATE PROCS     WCLIMIT            QUEUETIME

4917687            xxxxxxxx       Idle    16  4:00:00:00  Sun Aug 10 14:20:16
4917724            xxxxxxxx       Idle    16  4:00:00:00  Mon Aug 11 10:02:35
...
4917955            xxxxxxxx       Idle    16  4:00:00:00  Tue Aug 12 09:01:38
4917956            xxxxxxxx       Idle    16  4:00:00:00  Tue Aug 12 09:02:17

15 eligible jobs   

blocked jobs-----------------------
JOBID              USERNAME      STATE PROCS     WCLIMIT            QUEUETIME

4917949            xxxxxxxx       Idle    24 20:00:00:00  Tue Aug 12 08:24:24
4917950            xxxxxxxx       Idle    20 10:00:00:00  Tue Aug 12 08:24:29

2 blocked jobs   

Total jobs:  41
```

All of the categories show the job ID, username, state, and the number of processors allocated to the job.  The eligible and blocked jobs show the wallclock limit and when the job was queued.  Unlike the last two sections, the active section reports the when the job started and how much time ti has left before the scheduler will terminate it.

During busy times there may be thousands of lines that are output depending on the number of jobs on the system.  The showq command also takes a number of options that will filter the output and tell you what you need to know.

* ```showq -u <your_username>```: Just view your jobs with showq.
* ```showq -r```: View only the running jobs.
* ```showq -i```: View only the elegible (idle) jobs.
* ```showq -b```: View only the blocked jobs.
* ```showq -w class=<queue>```: Only view the jobs in a specific queue.
 
You can even mix and match these options.  For instance, to view all the running jobs in the ```gp``` queue for the user ```go.cougs``` you would send the following command:

```
showq -r -u go.cougs -w class=gp
```

