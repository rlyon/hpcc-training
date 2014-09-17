---
layout: default
title: Understanding Clusters
---

To understand the environment you will be working in, you will need to understand the parts.  Our high performance compute clusters are made up 4 distinct parts:

### Login Nodes

Login nodes are the front facing servers that the users will interact with.  They will usually contain the tools required to compile and submit your jobs.  Processes that are started on the login nodes will not automatically have full access to all of the clusters resources.  You will use the login nodes to prepare your data and add jobs to the queues through the use of the batch server tools.  In a PBS environment, you will use a queue submission tool called qsub.

In many cases access to software is is controlled through [environment modules](/hpcc-training/modules).  Environment modules can be used to select from many different versions of an application.  

### Management Nodes

Although you will not access these systems directly, they will be influencing everything that you do on the cluster.  The management nodes act as the hub of all operations for the cluster running several services including the batch server monitoring applications, and scheduling tools.  In some cases, the management nodes will even manage authentication and discovery services and act as a gateway to route network requests from the nodes to external resources.

### Execution Nodes

These nodes are the workhorse of the cluster.  All of the processing and analysis takes place on these systems.  Because these systems are physically seperated, they are controlled by the batch and scheduling systems on the management nodes.  Execution nodes are often grouped into homogenious sets and access is controlled through the use of queues or partitions.

### Storage Nodes

The storage nodes hold all of your data.  In our environment, your home directory lives there as well as faster *scratch* or *temporary* space that you can use for even faster data access.  The login nodes and execution nodes contact the storage systems and attach the directories (folders), so your data can be accessed in the same place across all of the HPC systems.
 
All four of these components work together to manage and run your jobs.  To learn more you can visit the [Linux Clusters website](http://www.linuxclusters.com/).
