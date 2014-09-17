---
layout: default
title: Connecting to the Cluster
---

# Connecting to the cluster

## Understanding clusters

To understand the environment you will be working in, you will need to understand the parts.  Our high performance compute clusters are made up 4 distinct parts:

1. ***Login Nodes:*** The login nodes are systems that are set up for you to interact with the cluster.  You will initially connect to these systems and they will have all the tools required for you to begin processing your data and submitting jobs to the cluster.
2. ***Management Nodes:***  Although you won't access these systems directly, they will be influencing everything that you do on the cluster.  The management nodes have all of the software required to schedule and monitor resources, authenticate your log in requests, and manage your jobs that will be run.
3. ***Execution Nodes:***  The execution nodes accept jobs from the queue and run them.  These systems and the running jobs are controlled by the management nodes.
4. ***Storage Nodes:***  The storage nodes hold all of your data.  Your home directory lives there as well as faster *scratch* or *temporary* space that you can use for even faster data access.  The login nodes and execution nodes contact the storage systems and attach the directories (folders), so your data can be accessed in the same place across all of the HPC systems.
 
All four of these components work together to manage and run your jobs.  To learn more you can visit the [Linux Clusters website](http://www.linuxclusters.com/).

## Connecting to the cluster

The WSU HPC cluster is a Linux based system that uses SSH to allow users to connect to a pseudo terminal (a fancy name for a command line or text device).  You will need to become comfortable operating in a command line environment and using the SSH program.  

For OSX you can use the ***Terminal*** application and Linux has several including ***XTerm*** and ***Gnome Terminal***.  

Windows does not come with SSH installed by default, but there are several options available including:

* [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html)
* [Bitvise Tunnelier](http://www.bitvise.com/download-area)

### SSH with Windows

For the purposes of this demonstration we will use the PuTTY application to connect to the login nodes on the cluster.  Assuming you have PuTTY installed already, double click on the application icon to start the program.  You will be greeted with a window that looks like this:

![PuTTY configuration](https://dl.dropboxusercontent.com/u/108911615/docimages/putty_configuration.png)

Fill in the hostname to be either *hpclogin1.wsu.edu* or *hpclogin2.wsu.edu* and click the open button.  If this is the first time connecting, you will receive a security alert that looks like this:

![PuTTY security alert](https://dl.dropboxusercontent.com/u/108911615/docimages/putty_security_alert.png)

It may seem like there is a problem, but this is just the way SSH works.  The first time you make a connection, your desktop or laptop and the server exchange keys.  These keys are used to identify and verify each other at the beginning of each connection so you can be certain that you are always talking to the correct server and that your connection has not been highjacked.  This message is just explaining that PuTTY has never seen this server and asking you if you want to trust it.  It is safe to say 'Yes' here.  You will then be greeted by the login screen:

![PuTTY login screen](https://dl.dropboxusercontent.com/u/108911615/docimages/putty_login_screen.png)

You will be asked for your login name and password that was sent to you when you registered for your HPCC account.  If you entered them correctly, you will be greeted with a prompt and can start typing commands.

### SSH with OSX and Linux

As stated before, you can use the ***Terminal*** Application for OSX or if you are using Linux you can use one of the many terminal applications available.  To interact with our systems you will use the ***ssh*** command directly from the terminal.  The ***ssh*** command at the very least requires the name of the server that you will be connecting to, but can also take the username and several other parameters as well.  If a username is not supplied, it will default to the *local* user that you are running the terminal with.  To connect using both a username and server name you will use something like this:

```sh
# ssh go.cougs@hpclogin1.wsu.edu
```

Where you would replace 'go.cougs' with your username.  If this is your first time connecting you will be asked to verify the authenticity of the host that you are connecting to.

```sh
The authenticity of host 'hpclogin1.wsu.edu (134.121.141.14)' can't be established.
RSA key fingerprint is 52:c6:6a:80:85:4c:07:34:8d:36:f0:72:b5:db:9a:6b.
Are you sure you want to continue connecting (yes/no)?
```

You can safely say yes here.  You will then be asked for your password and if you enter it correctly, will be greeted by a prompt and can start typing commands.
