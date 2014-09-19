---
layout: default
title: Wrapping Qsub
---

Our last submission script worked fine with a few files, but we should thing bigger.  What happens if those files were huge or if we had thousands or millions of them.  Our current submission script will process them all sequentially.  Because no one stats job is dependent on the other for output, we can run them all at the same time.

To do this we will either need to create submission scripts for each of the files, or we can create a script that give qsubs the information it need and submits everything for us.  

***Notice that I did not say we would create a script to generate the submission scripts or modify our stats script to make it specific to the job.***  It is common place to see these types of approaches in job submission but think of the consequences.  If you have a million files, you will need to generate a million scripts and then you will need to clean up a million scripts, or more commonly they will be left there and you will be forces to sort through them in the future.  Also, what happens if you need to make changes?  Do you regenerate all of your scripts?

This the script generation approach is generally due to a misunderstanding with how qsub works.  Qsub will not allow for inline arguments to be passed to the submission script, which means that some other method needs to be used to get that information there.

### Variables as arguments

Instead of arguments to the script we can use variables to pass information in and out of the submission scripts.

Modify your submission script to process a single file and receive that file from and argument:

```sh
cd $HOME/tutorial
./stats.sh $DATAFILE
```

Now you can pass the variable DATAFILE with qsub and the submission script will have access to it.

```text
$ qsub -v DATAFILE=$HOME/tutorial/hpcc-training/testdata/shakespeare-winters-19.txt stats.pbs
```
When finished the output file will contain something similare to this:

```text
Getting stats for /home/go.cougs/tutorial/hpcc-training/testdata/shakespeare-winters-19.txt
Lines: 4526
Words: 25947
Characters: 145677
```

Now that the submission script is working as intended, you can start on the wrapper.  All the wrapper will do is take all the text files in a directory and submit them individually.  Create a new file called ```stat-submit-wrapper.sh``` with your favorite text editor and add the following contents:

```sh
#!/bin/bash

if [ $# -lt 1 ]
then
	echo "You need to supply a directory"
	exit 1
fi

for i in $@
do
	echo "Submitting file: $i"
	qsub -N stats -j oe -v DATAFILE=$i stats.pbs
done

```

Give the wrapper execute permissions and run it

```text
$ ./stat-submit-wrapper.sh $HOME/tutorial/hpcc-training/testdata/*.txt
```

```text
$ qstat
Job id                    Name             User            Time Use S Queue
------------------------- ---------------- --------------- -------- - -----
4952303.mgt1               stats            go.cougs       00:00:00 C batch          
4952304.mgt1               stats            go.cougs       00:00:00 C batch          
4952305.mgt1               stats            go.cougs       00:00:00 C batch          
4952306.mgt1               stats            go.cougs       00:00:00 C batch          
4952307.mgt1               stats            go.cougs       00:00:00 C batch          
4952308.mgt1               stats            go.cougs       00:00:00 C batch          
4952309.mgt1               stats            go.cougs       00:00:00 C batch          
4952310.mgt1               stats            go.cougs       00:00:00 E batch          
4952311.mgt1               stats            go.cougs              0 R batch          
4952312.mgt1               stats            go.cougs              0 R batch          
4952313.mgt1               stats            go.cougs              0 Q batch          
4952314.mgt1               stats            go.cougs              0 Q batch          
4952315.mgt1               stats            go.cougs              0 Q batch          
4952316.mgt1               stats            go.cougs              0 Q batch 
```

As you can see we are now processing them individually and when I ran qsub many had already completed, there was one in the process of exiting and there were a few more queued.  You can use this pattern for many different applications and it will come in even more handy when we start working with pipelines.

If you need your log files in one place just cat them together.

```text
$ cat stats.o* > stats.log
$ rm stats.o*
$ cat stats.log 
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-antony-23.txt
Lines: 5689
Words: 27190
Characters: 158248
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-comedy-7.txt
Lines: 2851
Words: 16252
Characters: 89439
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-hamlet-25.txt
Lines: 5877
Words: 32242
Characters: 182399
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-julius-26.txt
Lines: 3961
Words: 20981
Characters: 117902
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-life-54.txt
Lines: 4534
Words: 27695
Characters: 154933
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-life-55.txt
Lines: 4551
Words: 26110
Characters: 148351
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-life-56.txt
Lines: 3583
Words: 21838
Characters: 122448
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-loves-8.txt
Lines: 4265
Words: 22965
Characters: 129916
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-romeo-48.txt
Lines: 4579
Words: 25919
Characters: 144138
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-second-52.txt
Lines: 4736
Words: 27992
Characters: 157146
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-taming-2.txt
Lines: 4039
Words: 22207
Characters: 124128
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-tragedy-58.txt
Lines: 5588
Words: 31681
Characters: 180293
Getting stats for /home/admins/rob.lyon/tutorial/hpcc-training/testdata/shakespeare-winters-19.txt
Lines: 4526
Words: 25947
Characters: 145677
```

They are all there and we were able to break up the problem into managable chunks.
