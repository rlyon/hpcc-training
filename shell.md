---
layout: default
title: The Shell
---

Now that you have logged into the cluster, you are now in what is called ***the shell***.  This shell is a text driven program that will help you navigate the complexities of the operating system.  You type in commands and the shell responds to you with output.

There are many different ***shells*** available for Linux.  By default you will be using the ***bourne-again shell*** shell or ***bash*** which was created as a free replacement to an older shell - ***sh*** - written by a programmer named Bourne.  You can find many great tutorials online that will teach you how to navigate in ***bash***.

* [Unix tutorial for beginners](http://www.ee.surrey.ac.uk/Teaching/Unix/index.html)
* [Bash guide for beginners](http://www.tldp.org/LDP/Bash-Beginners-Guide/html/)
* [Advanced bash scripting guide](http://www.tldp.org/LDP/abs/html/)
 
Since there are many tutorials on how to use bash out there already, we will only cover a few common commands that you will use in file management.  When you first log into the system, you will be greeted by a banner and a prompt as well as some additional information about how much storage you have available (we will cover that later).

```text
$ ssh go.cougs@hpclogin1
go.cougs@hpclogin1's password: 
Last login: Mon Jul 28 12:10:06 2014 from 134.121.10.42
          __      __ ___  _   _   _  _  __    ___  ___
          \ \    / // __|| | | | | || || _ \ / __|/ __|
           \ \/\/ / \__ \| |_| | | __ ||  _/| (__| (__
            \_/\_/  |___/ \___/  |_||_||_|   \___|\___|
            
 *****************************************************************
 * Access to electronic resources at Washington State University *
 * is restricted to faculty, staff and students, or individuals  *
 * authorized by the University or its affiliates. Use of this   *
 * system is subject to all policies and procedures set forth by *
 * Wasington State  University. These policies are located at:   *
 *                                                               *
 * http://infotech.wsu.edu/about/policies/computeruse.html       *
 *                                                               *
 * Unauthorized use is prohibited and may result in              *
 * administrative or legal action.  Washington State University  *
 * may monitor the use of this system for purposes related to    *
 * security management, system operations, and intellectual      *
 * property compliance.                                          *
 *****************************************************************
 
 QUESTIONS? Please submit all questions, requests, and system 
            issues to: hpc.support@wsu.edu.

 VOL          TOTAL     AVAIL   TOTAL %    YOUR     YOUR   YOUR %
              SPACE     SPACE     USAGE   USAGE    QUOTA    QUOTA
 HOME       74500.0   34308.0    53.95%   112.0   5120.0    2.19%
 SCRATCH    33467.0    7234.0    78.38%     0.0      0.0     0.0%
 
 go.cougs@login1 ~ $
```

***Note:  When creating this tutorial, my prompt was "go.cougs@login1 ~ $", the commands you will be typing are found to the right of the "$".  Don't type the prompt.***

### Viewing the command help pages

At anytime you can view the help pages for the commands that will be used throughout the tutorial to get information about what the command does, options, and even some examples by typing ***man*** (manual) and then the command name.  In otherwords, to find out more information on the ***ls*** command that we will be using next, type:

```text
go.cougs@login1 ~ $ man ls
```

Use the up and down arrows on your keyboard to go forward and backward and use the ***Q*** key to exit the manual

### List the files or folders in your directory

At this point you should have no visible files or folders in your home directory.  You can use the ***ls*** or 'list' command to check:

```text
go.cougs@login1 ~ $ ls
go.cougs@login1 ~ $
```

As you can see there was nothing returned, but there are some files there.  Linux and Unix have the concept of *hidden files* that do not show up in the regular output.  You can see your hidden files by adding an option to the ***ls*** command that will tell ***ls*** to also show hidden files.

```text
go.cougs@login1 ~ $ ls -a
.              .bash_logout   .clcbio     .lesshst  .rvm       .viminfo      .zlogin
..             .bash_profile  .curlrc     .profile  .ssh       .Xauthority   .zshrc
.bash_history  .bashrc        .install4j  .psrc     .tempstor  .x-formation
go.cougs@login1 ~ $ 
```

Most of these files contain configuration data for other programs and you may or may not have all of them.  Notice all of the hidden files start with a *period*.

### Creating a new folder

Folders are used to organize your files.  To create a new folder, use the command ***mkdir*** or 'make directory'.  Make a folder called 'tutorial'

```text
go.cougs@login1 ~ $ mkdir tutorial
go.cougs@login1 ~ $ ls
tutorial
go.cougs@login1 ~ $
```

### Enter the folder

You can use the ***cd*** command or 'change directory' to navigate through your folders.  To move into the tutorial folder you just created, type:

```text
go.cougs@login1 ~ $ cd tutorial
go.cougs@login1 ~/tutorial $
```

If you type ***cd*** without a folder name, it will automatically take you back to the top of your home directory.  

You may also want to move back up a directory.  To do this you can use the special file "***..***" (you may have noticed this in the output of ***ls -a*** above).  The two dots represent the *parent* or *containing* folder and can be used like this:

```text
go.cougs@login1 ~/tutorial $ cd ..
go.cougs@login1 ~ $
```

*Before you move on, make sure to change back to the tutorials directory that you created.*

### Creating and editing a file

Although there are several text based editors on our systems, the one that we will focus on will be a simple text editor called ***nano***.  To start nano, 
type the command:

```text
go.cougs@login1 ~/tutorial $ nano
```

You will be greeted by a screen that looks like:

![Nano](https://dl.dropboxusercontent.com/u/108911615/docimages/nano.png)

Type some words into the editor and when you would like to save the file press the ***control (ctrl)*** and the ***x*** keys a the the same time.  

You will be asked if you want to save the buffer (i.e. all of your changes)

```text
Save modified buffer (ANSWERING "No" WILL DESTROY CHANGES) ?                            
 Y Yes
 N No           ^C Cancel
```

If you want to save, press 'Y' otherwise press 'N'.  It will then ask you to type in the filename.  Call it 'hello.txt' and press enter

```text
File Name to Write: hello.txt                                                           
^G Get Help           ^T To Files           M-M Mac Format        M-P Prepend
^C Cancel             M-D DOS Format        M-A Append            M-B Backup File
```

*Note, that on the bottom of the screen, you will see ***^C*** right next to the word 'Cancel'.  When ever you see the ***^*** character, substitute it with the control key.  In otherwords, ***^G*** is ***CNTL + G*** and that key combination will bring up the help pages.*

### Different ways to interact your files

There are many different ways to access the information stored in your files.  The most common are the ***cat***, ***more***, ***less***, ***head*** and ***tail*** commands.  To view the file contents of hello.txt run:

```text
go.cougs@login1 ~/tutorial $ cat hello.txt 
Hello
```

The command ***cat*** stands for *concatenate* and can take as many files as you want.  Use the nano to create another file called *world.txt* and save it.  You can concatenate the output of both files together by running the command:

```text
go.cougs@login1 ~/tutorial $ cat hello.txt world.txt 
Hello
World
```

This command does not actually change your files.  It outputs the contents to the screen.  You can capture this output and put it into a new file by using a method called ***redirection***.  To *redirect* the output to a new file you can use ***>*** of ***>>*** after the command with the name of a new file.  The single ***>*** will overwrite all the contents in the file with the new contents you are redirecting into it, while the double will append the new contents to the end of the file. 

```text
go.cougs@login1 ~/tutorial $ cat hello.txt world.txt > helloworld.txt
go.cougs@login1 ~/tutorial $ cat helloworld.txt 
Hello
World
go.cougs@login1 ~/tutorial $ cat hello.txt world.txt >> helloworld.txt
go.cougs@login1 ~/tutorial $ cat helloworld.txt 
Hello
World
Hello
World
```

For large files, the ***cat*** command will output all of the file contents without stoping.  You can use the ***more*** command to page through the contents of a large file.  The ***less*** command is a paging utility like the ***more*** command, but it also allows you to page backwards.  The ***head*** and ***tail*** command show the first and last few lines of a file.  You can control the number of lines shown by adding a dash and then the number of lines (e.g. ***-10***)

Try them out by downloading a large file with the following command:

```text
go.cougs@login1 ~/tutorial $ wget http://www.textfiles.com/etext/AUTHORS/SHAKESPEARE/shakespeare-comedy-7.txt
```

You can then use the following commands:

```text
go.cougs@login1 ~/tutorial $ more shakespeare-comedy-7.txt
go.cougs@login1 ~/tutorial $ less shakespeare-comedy-7.txt
go.cougs@login1 ~/tutorial $ head -20 shakespeare-comedy-7.txt
go.cougs@login1 ~/tutorial $ tail -20 shakespeare-comedy-7.txt
```

When using ***more*** or ***less*** you can press the ***Q*** key to exit before the end of the file.

### Removing files and directories

Use the ***rm*** command to remove files

```text
go.cougs@login1 ~/tutorial $ ls
hello.txt  helloworld.txt  shakespeare-comedy-7.txt  world.txt
go.cougs@login1 ~/tutorial $ rm helloworld.txt 
go.cougs@login1 ~/tutorial $ ls
hello.txt  shakespeare-comedy-7.txt  world.txt
go.cougs@login1 ~/tutorial $
```

To remove a directory you will use the same command but use the ***-r*** option to recursivly remove all of the files in the directory at the same time.  If you do not specify the ***-r*** when trying to remove a directory the command will fail.

```text
go.cougs@login1 ~/tutorial $ mkdir -p removeme
go.cougs@login1 ~/tutorial $ ls
hello.txt  removeme  shakespeare-comedy-7.txt  world.txt
go.cougs@login1 ~/tutorial $ rm removeme
rm: cannot remove `removeme': Is a directory
go.cougs@login1 ~/tutorial $ rm -r removeme
go.cougs@login1 ~/tutorial $ ls
hello.txt  shakespeare-comedy-7.txt  world.txt
```

### Renaming and moving your files

To rename a file you can use the ***mv*** (move) command or the ***rename*** command.  Move is the simplest form of renaming a file, to test this out type ***mv*** with the original file name and the new file name:

```text
go.cougs@login1 ~/tutorial $ ls
hello.txt  moved  shakespeare-comedy-7.txt  world.txt
go.cougs@login1 ~/tutorial $ mv world.txt World.txt
go.cougs@login1 ~/tutorial $ ls
hello.txt  moved  shakespeare-comedy-7.txt  World.txt

```

The rename command gives you a little more flexibility when it comes to renaming multiple files at the same time.  Let's say that you wanted to take all of your text files in your directory and rename them to have a *.backup* extension before you started creating new ones.  You could use the ***rename*** command to take the .txt extension and turn it into .txt.backup

```text
go.cougs@login1 ~/tutorial $ ls
hello.txt  moved  shakespeare-comedy-7.txt  World.txt
go.cougs@login1 ~/tutorial $ rename .txt .txt.backup *.txt
go.cougs@login1 ~/tutorial $ ls
hello.txt.backup  moved  shakespeare-comedy-7.txt.backup  World.txt.backup
```

*Note the asterisk in \*.txt.  This is called a wildcard and in this context means all files that have the extension 'txt'.  For additional information on wildcards see [this tutorial](http://www.ee.surrey.ac.uk/Teaching/Unix/unix4.html)*

You can also move or rename entire directories along with their contents.

```text
go.cougs@login1 ~/tutorial $ mkdir -p moveme/{1,2,3,4}
go.cougs@login1 ~/tutorial $ ls moveme
1  2  3  4
go.cougs@login1 ~/tutorial $ mv moveme moved
go.cougs@login1 ~/tutorial $ ls moved
1  2  3  4
```
