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

$
```

***Note:  When creating this tutorial, my prompt was "$", the commands you will be typing are found to the right of the "$".  Don't type the prompt. Your prompt may vary depending on your system and your system administrator.***

### Viewing the command help pages

At anytime you can view the help pages for the commands that will be used throughout the tutorial to get information about what the command does, options, and even some examples by typing ***man*** (manual) and then the command name.  In otherwords, to find out more information on the ***ls*** command that we will be using next, type:

```text
$ man ls
```

Use the up and down arrows on your keyboard to go forward and backward and use the ***Q*** key to exit the manual

### List the files or folders in your directory

At this point you should have no visible files or folders in your home directory.  You can use the ***ls*** or 'list' command to check:

```text
$ ls
```

As you can see there was nothing returned, but there are some files there.  Linux and Unix have the concept of *hidden files* that do not show up in the regular output.  You can see your hidden files by adding an option to the ***ls*** command that will tell ***ls*** to also show hidden files.

```text
$ ls -a
.              .bash_logout   .clcbio     .lesshst  .rvm       .viminfo      .zlogin
..             .bash_profile  .curlrc     .profile  .ssh       .Xauthority   .zshrc
.bash_history  .bashrc        .install4j  .psrc     .tempstor  .x-formation
```

Most of these files contain configuration data for other programs and you may or may not have all of them.  Notice all of the hidden files start with a *period*.

There are a couple of other files of interest here as well.  Notice the ```.``` and the ```..```?  These represent the current directory and the parent directory.

#### Additional options
There are many options for ls, but some of the options that I have found most useful are the ```-l```, ```-t``` option and the ```-r``` option.  The ```-t``` options tells ```ls``` to sort by decending time and ```-r``` will reverse it.  The ```-l``` option will use a long list format and give you information such as permissions and modification times.  If you have a directory with a large amount of files and you need to see which ones have been accessed recently (and when) just type:

```text
$ ls -altr
```

Your newest files will be listed at the bottom.

### Creating a new folder

Folders are used by Linux to organize files.  To create a new folder, use can use the command ***mkdir*** or 'make directory'.  In Linux Make a folder called 'tutorial' and check to see if it is there.

```text
$ mkdir tutorial
$ ls
tutorial
```

### Enter the folder

You can use the ***cd*** command or 'change directory' to navigate through your folders.  To move into the tutorial folder you just created, type:

```text
$ cd tutorial
```

If you type ***cd*** without a folder name, it will automatically take you back to the top of your home directory.  

You may also want to move back up a directory.  To do this you can use the special file "***..***" (you may have noticed this in the output of ***ls -a*** above).  The two dots represent the *parent* or *containing* folder and can be used like this:

```text
$ cd ..
```
When you type ```ls``` and press enter, you should see the tutorials directory that you created earlier.  Now use ```cd``` to change back to the tutorials directory that you created.

### A smart way to change directories

There are many times that you will run accross cases where you will want to move in and out of several directories.  It can be tough to keep track of the directories that you have entered and left.  The ```pushd``` command can actually keep track of where you have been like breadcrumbs by pushing your current location on to a stack befor it moves to the next directory.  You can then use the ```popd``` to go back to the last location that was pushed.

To test this out make a few more directories:

```text
$ mkdir -p pushtest/{one,two,three,four}/{a,b,c,d}
```

There's a bit of handwaving over this command, but needless to say this is a quick way to recursively create a directory structure that is three levels deep. The number directories will each have an a, b, c, and d directory.

Use ```pushd``` to wind your way through the directories and see what happens.  Then use ```popd``` to return to where you were.  When you pop back out all the way you may see:

```text
$ popd
-bash: popd: directory stack empty
```

### A quick aside - Wildcards in Bash

Wildcards are a power tool in your arsenal when it comes to interacting with the shell.  Commands can use wildcards to specify multiple files without typing the list out or dig out text in a file.  There are several useful ones that you will see in this tutorial and that you will probably use on a daily basis.  They include:

#### * (asterisk)

The asterisk can be used to specify any number or type of character.  It will match everything.  As an example:

```text
*.txt
```

Will match everything with a ***.txt*** extension, no matter what the file name is.

#### \[\] (square brackets)

Square brackets specify a range with an explicit ***or*** relationship.  Meaning you only need one to match.  The following pattern will match dig, dog or dug.  

```text
d[i,o,u]g
```

When you use a comma to seperate characters, it sees them as individual characters, but if you use a dash it will interperet them as a range of characters.  For example if you want to list the files in a directory that begin with a, b or c you could write your ***ls*** statement like this:

```text
ls [a-c]*
```

#### {} (curly brackets)

Curly brackets allow you to group patterns together.  If you wanted to list all of your '.txt' files and your '.log' files you could use the following statement:

```text
ls {*.txt,*.log}
```

### One more quick aside - Ranges

Through this tutorial you'll also see the curly brackets used for ***brace*** or ***sequence*** expansion.  When you have a range of characters or integers connected with ***..*** and surounded by brackets, the shell will expand them into their full range.

For instance:

```text
$ echo {1..9}
1 2 3 4 5 6 7 8 9
$ echo {a..i}
a b c d e f g h i
```

Newer versions of bash will also do zero padding.

```text
$ echo {00..10}
00 01 02 03 04 05 06 07 08 09 10
```

### Get the tutorial files

Before we go any further, there are files that we will be using for this series of tutorials, you can get them by cloning the training repository.  Some of you may not know what this means, but we will explain what this is doing in a later tutorial.  For now, just copy the command and type it into your terminal just the way it appears here.

```text
$ git clone https://github.com/wsuops/hpcc-training.git
```

Once this is done, you should have a folder named ***hpcc-training*** in your tutorials directory.

```text
$ ls
hpcc-training
```

### Different ways to interact your files

The files that we are going to be using are found in the hpcc-training directory so lets change to it.

```text
cd hpcc-training
```

There are many different ways to access the information stored in your files.  The most common are the ***cat***, ***more***, ***less***, ***head*** and ***tail*** commands.  To view the file contents of hello.txt file that is in the directory run the ```cat``` command with the filename as the argument:

```text
$ cat hello.txt
Hello
```

The command ***cat*** stands for *concatenate* and can take as many files as you want.  You can concatenate the output of many files together by running the cat command with all of the files as arguments:

```text
$ cat hello.txt world.txt 
Hello
World
```

This command does not actually change your files.  It outputs the contents to the screen.  You can capture this output and put it into a new file by using a method called ***redirection***.  To *redirect* the output to a new file you can use ***>*** of ***>>*** after the command with the name of a new file.  The single ***>*** will overwrite all the contents in the file with the new contents you are redirecting into it, while the double will append the new contents to the end of the file. 

```text
$ cat hello.txt world.txt > helloworld.txt
$ cat helloworld.txt 
Hello
World
$ cat hello.txt world.txt >> helloworld.txt
$ cat helloworld.txt 
Hello
World
Hello
World
```

For large files, the ***cat*** command will output all of the file contents without stoping.

```text
$ cat testdata/shakespeare-comedy-7.txt
```

You can use the ***more*** command to page through the contents of a large file.  The ***less*** command is a paging utility like the ***more*** command, but it also allows you to page backwards.  The ***head*** and ***tail*** command show the first and last few lines of a file.  You can control the number of lines shown by adding a dash and then the number of lines (e.g. ***-10***)


You can then use the following commands:

```text
$ more testdata/shakespeare-comedy-7.txt
$ less testdata/shakespeare-comedy-7.txt
$ head -20 testdata/shakespeare-comedy-7.txt
$ tail -20 testdata/shakespeare-comedy-7.txt
```

When using ***more*** or ***less*** you can press the ***Q*** key to exit before the end of the file.

### Copying files

Use the ```cp``` command to copy one of our shakespeare files to the current directory:

```text
$ cp testdata/shakespeare-comedy-7.txt .
```
To copy a directory you can use ***-r*** to copy all files recursively.

### Removing files and directories

Use the ***rm*** command to remove files

```text
$ ls
hello.txt  helloworld.txt  shakespeare-comedy-7.txt  world.txt
$ rm helloworld.txt 
$ ls
hello.txt  shakespeare-comedy-7.txt  world.txt
$
```

To remove a directory you will use the same command but use the ***-r*** option to recursivly remove all of the files in the directory at the same time.  If you do not specify the ***-r*** when trying to remove a directory the command will fail.

```text
$ mkdir -p removeme
$ ls
hello.txt  removeme  shakespeare-comedy-7.txt  world.txt
$ rm removeme
rm: cannot remove `removeme': Is a directory
$ rm -r removeme
$ ls
hello.txt  shakespeare-comedy-7.txt  world.txt
```

### Renaming and moving your files

To rename a file you can use the ***mv*** (move) command or the ***rename*** command.  Move is the simplest form of renaming a file, to test this out type ***mv*** with the original file name and the new file name:

```text
$ ls
hello.txt  moved  shakespeare-comedy-7.txt  world.txt
$ mv world.txt World.txt
$ ls
hello.txt  moved  shakespeare-comedy-7.txt  World.txt

```

The rename command gives you a little more flexibility when it comes to renaming multiple files at the same time.  Let's say that you wanted to take all of your text files in your directory and rename them to have a *.backup* extension before you started creating new ones.  You could use the ***rename*** command to take the .txt extension and turn it into .txt.backup

```text
$ mkdir rename
$ pushd rename
~/hpcc-training/rename ~/hpcc-training
$ touch test{1..10}.log
$ ls
test10.log  test2.log  test4.log  test6.log  test8.log
test1.log   test3.log  test5.log  test7.log  test9.log
$ rename .log .log.bak *.log
$ ls
test10.log.bak  test2.log.bak  test4.log.bak  test6.log.bak  test8.log.bak
test1.log.bak   test3.log.bak  test5.log.bak  test7.log.bak  test9.log.bak
$ popd
$ rm -r rename
```

You can also move or rename entire directories along with their contents.

```text
$ mkdir -p moveme/{1,2,3,4}
$ ls moveme
1  2  3  4
$ mv moveme moved
$ ls moved
1  2  3  4
$ rm -r moved
```
