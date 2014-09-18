---
layout: default
title: Understanding Clusters
---

To understand the environment you will be working in, you will need to understand the parts.  High performance compute clusters are generally made up 4 distinct parts, though you may find the functionality of these parts combined together on a single system.

### Login Nodes

Login nodes are the front facing servers that the users will interact with.  They will usually contain the tools required to compile and submit jobs.  Processes that are started on the login nodes will not automatically have full access to all of the clusters resources.  You will use the login nodes to prepare your data and add jobs to the queues through the use of the batch server tools.  In the PBS environment that will be covered in this guide, you will use a queue submission tool called [qsub](/hpcc-training/using-qsub).

In many cases access to software is is controlled through [environment modules](/hpcc-training/modules).  Environment modules can be used to select from many different versions of an application.  

### Management Nodes

Although you will not access these systems directly, they will be influencing everything that you do on the cluster.  The management nodes act as the hub of all operations for the cluster running several services including the batch server monitoring applications, and scheduling tools.  In some cases, the management nodes will even manage authentication and discovery services and act as a gateway to route network requests from the nodes to external resources.

Some of the more common applications that you will find running on a management node (but not at the same time) include:

* Torque (batch server)
* OpenGridEngine (batch server and scheduler)
* Maui (scheduler)
* Moab (scheduler)
* Ganglia (monitoring)
* Nagios (monitoring)
* Monit (monitoring)
* XCat (provisioning)
* Bind (name services)
* Dhcpd (host configuration)

### Execution Nodes

These nodes are the workhorse of the cluster.  All of the processing and analysis takes place on these systems.  Because these systems are physically seperated, they are controlled by the batch and scheduling systems on the management nodes.  Execution nodes are often grouped into homogenious sets and access is controlled through the use of queues or partitions.

It is important to remember that because these systems are managed by the batch and scheduling systems, that you should not use SSH to login and manually start jobs on these nodes directly unless you have previously reserved resources with the scheduling system.  Worse case senario, it you start a process or a set of processes on a system or systems, you could overload the machines, run them out of resources, and interupt the jobs of others in a shared environment.

### Storage Nodes

The storage nodes hold all of your data.  Many environments have central storage areas for home directories as well as faster *scratch* or *temporary* space that you can use for even faster data access.  In many systems login nodes and execution nodes contact the storage systems and attach the directories (folders), so your data can be accessed in the same place across all of the HPC systems.  

There are some clusters that do not have a central shared file system and require data staging before processing can occur.  These systems will usually have tools available to push and pull data from the execution nodes.

### More Information

All four of these components work together to manage and run your jobs.  To learn more you can visit the [Linux Clusters website](http://www.linuxclusters.com/).
