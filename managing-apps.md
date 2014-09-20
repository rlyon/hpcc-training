---
layout: default
title: Managing Your Own Applications and Modules
---

A bit of background first, just play along for a moment and see if this doesn't sound familiar.  While sipping the morning cup of coffee, we found a reference in the latest high impact journal to this great program that we really need for our research.  It's called ***freak*** and its the greatest word frequency counter.  We really need it now.  We email the system adminstrator in charge of the cluster (because they never answer their phones) and politely ask if they could install it for you.  The system administrator on the other end, without a moments hesitation says no.

The set of applications that facilities can support will be limited and you'll often find yourself needing to manage some applications that you or your group is responsible for.  By adding a single line to the ***.bashrc*** script anyone can share your personal module repository and your custom applications.  We are going to briefly cover installing applications in your home directory and setting up modules to access your them.

### Setup your folders

Organization of your directory can be key over time.  Of course you can do this any way you choose, but for the purposes of this tutorial, lets set up a directory for applications, one for source code and one for modulefiles.

```text
$ cd
$ mkdir {apps,modulefiles,src}
```

### Get the application

Next you need to download the file.  There are a couple of ways you could handle this, but the quickest way is to grab it right from your terminal.  Use the wget command with the address of the file.

```text
$ wget --no-check-certificate https://github.com/wsuops/hpcc-training/raw/master/src/freak-0.0.1.tar.gz
```

The file that you have downloaded has been archived and compressed with tar and gzip so you will need to uncompress and unarchive them before we continue.  Using the tar command, you can uncompress the archive into a new folder.

```text
$ tar zxvf freak-0.0.1.tar.gz
freak-0.0.1/
freak-0.0.1/Makefile.am
freak-0.0.1/missing
freak-0.0.1/configure
freak-0.0.1/freak.cpp
freak-0.0.1/autom4te.cache/
freak-0.0.1/autom4te.cache/traces.1
freak-0.0.1/autom4te.cache/output.0
freak-0.0.1/autom4te.cache/output.1
freak-0.0.1/autom4te.cache/traces.0
freak-0.0.1/autom4te.cache/requests
freak-0.0.1/Makefile.in
freak-0.0.1/aclocal.m4
freak-0.0.1/depcomp
freak-0.0.1/compile
freak-0.0.1/configure.ac
freak-0.0.1/config.status
freak-0.0.1/install-sh
$ cd freak-0.0.1
```

### Configure and install

There are often 3 steps to compiling and installing most applications in Linux.  The steps include configuring the application, building the application with a program called make and installing the application to it's final destination.  

Since you will not have access to other system directories outside your home or group directories, you will install the application into the apps folder that you created earlier.  There is an executable file in the directory called ***configure***.  We need to use this to set the options before we build.  Real applications will have several options and you can view all of the options with the following command:

```text
$ ./configure --help
```

The only option that we are interested in will be the ***--prefix*** option that will let us choose the location where the application will be installed.  Configure the application with the configure command, then build it, and install:

```text
$ ./configure --prefix=$HOME/apps/freak/0.0.1
$ make
$ make install
```

Once those commands have been run, if there were no errors, you will find your program installed in a directory called 'bin' at the prefix that we passed to the the configure command.

```text
$ ls $HOME/apps/freak/0.0.1/bin/
freak
```

In order to execute the file without typing the full path every time, you will either need to add $HOME/freak/0.0.1/bin to your PATH variable or since we are using modules, we can have the environment modules program make those adjustments for us when we load our freak module. This also helps with sharing the application across the system.

### Create your modulefile

Inside your modulefiles directory, you will need to create another directory with the name of the application you are creating the module file for.  In this case, create a directory called ***freak***

```text
$ cd modulefiles
$ mkdir freak
```

Modulefiles use a different scripting language than what we have been using called tcl (tool command language).  The file will generally look something like this:

```text
#%Module1.0
##  freak modulefile
##
proc ModulesHelp { } {
        puts stderr "Adds freak 0.0.1 to your environment."
}

module-whatis   "Adds freak 0.0.1 to your environment."

## Add freak bin directory to the path
prepend-path     PATH    ~/apps/freak/0.0.1/bin

## Set an aliases
set-alias       "ff"    "freak"

## Set an environment variable
setenv          FREAKDATA  ~/tutorial/hpcc-training/testdata
```

The first line contains a 'magic cookie' that will let the module application know that it should interperet the file.  If it is not there, the application will not read the file.  You can use the rest as a template to build your own.  You have the ability to prepend paths, append paths, set environemtn variables and aliases along with many others functions that are available.

Open up your favorite text editor and create a file in the freak directory named after the version.  Copy the contents above into the file.

```text
$ nano freak/0.0.1
```

### Let the module command know where to look

After you have added it, you will need to let the modules application know of your personal modulefiles directory by issuing the following command.

```text
$ module use ~/modulefiles
```

If everything is correct you can run the module avail command and you'll see this:

```text
$ module avail

---------------------- /home/username/modulefiles ----------------------
freak/0.0.1
```

You will now be able to access the application directly from the command line after you load it.

```text
$ module load freak/0.0.1
$ freak $FREAKDATA/shakespeare-life-54.txt
```

### Add another version of the application

As an exercise, there has been another version of freak that has been released.  Instead of outputing the frequencies in word sorted order, the author though it would be better to sort based on frequency.  Unfortunately, all of our old scripts expect the output to be the old way.  Install the latest version of freak from this address:

```text
https://github.com/wsuops/hpcc-training/raw/master/src/freak-0.0.2.tar.gz
```

You'll want to use the following path for the prefix:

```text
$HOME/apps/freak/0.0.2
```

Create the modulefile using the other one as a template and then run module avail.  You do not need to run the ```module use``` command again.  You should see both version of freak.

### Setting a default version

If you have more than one module you will want to set a default version to be loaded if you do not specify a version.  To do this you will need to create a file called ***.version*** in your ***modulefiles/freak*** directory.  In it you will need to have the 'magic cookie' line plus the command to set the version:

```text
#%Module1.0
set ModulesVersion "0.0.2"
```
