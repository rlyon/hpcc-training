---
layout: default
title: Uses and Misconceptions
---


### Uses

At it's core, high performance compute clusters are a bunch of components linked together that can use special libraries to spread your workload across many hundreds of cores.  They have found a home in almost every corner of research.  Be it academic or private, supercomputers can be be used for many things including:

* Weather simulation and modeling
* Engineering simulations
* Biomedical and genomic research
* Molecular modeling
* Statistical and mathematical modeling

### Misconceptions

There are many misconceptions out there about clusters.  Here are a few that I have had to answer over the years.

* A supercomputer or cluster is not necessarily an extension to your desktop.  Programs can be written to launch jobs from your desktop or laptop, but you cannot expect a performance increase in your Notepad application just by connecting to a supercomputer.
* Clusters do not automatically make your programs faster.  In fact, because of queue wait times and setup and teardown, single applications may take longer to run.
* Applications not scale linearly in many cases as you increase the amount of cores.  Even with high speed low latency networks, you still may find congestion as hundreds or thousands of cores try to simultaneously synchronize their actions. 10 cores may be faster than 100 depending on the application.
* Your programs are not automatically able to benefit from all those distributed cores.  They must have been specifically compiled against special message passing libraries to work across multiple systems and cores in parallel. 
