---
layout: default
title: Writing Shell Scripts
---

# Writing Shell Scripts

Many things that you want to do on the HPC systems will require alot of commands run in a specific order.  Formating your data, submitting jobs to the cluster, and parsing job results are just a few things that could take alot of time if you were to do this by hand.  More than likely you will need to do this more than once, which means you may be stuck typing at your keyboard instead of coming up with the next scientific breakthrough.  That's where shell scripting comes in.

## Your first shell script

To create your first shell script open up your text editor and type:

```sh
#!/bin/bash
echo "Hello world!"
```

The first line may seem a little strange but it's purpose is simple.  The first two characters ```#!```, often called the *shebang*, *shabang*, or *pound-bang*, is an interperter directive that lets the program loader know what it should use to interperet the text that will follow.  In otherwords, the ```#!/bin/bash``` means, *'Please use the program /bin/bash to process all the commands that will follow.'*

The second line contains the ```echo``` command, which does exactly what it's name implies:  It takes some text and outputs it to the terminal.

Save the file as ```hello.sh``` and exit the editor.  Before you can 'run' your script, you will need to do one more thing.  If you were to try to run it right now, you would see the following:

```text
go.cougs@login1 ~ $ ./hello.sh
-bash: ./hello.sh: Permission denied
```

In order to run a script, you will need to let the operating system know that it is the kind of file that can be run.  To do this, you will use the ```chmod``` or *change mode* program with the ```+x``` or *add execute permissions* to set the appropriate permissions.

```text
go.cougs@login1 ~ $ chmod +x hello.sh
```

Once you have set the execute permissions on the file you will be able to run it:

```text
go.cougs@login1 ~ $ ./hello.sh 
Hello world!
```

Congratulations!  You have just created your first shell script.  Now let's actually make one that does something other than say hello.  

## Your next shell script

To give us some files to work with, download some files containing the text of several plays by Shakespeare.

```text
go.cougs@login1 ~/tutorial $ wget http://www.textfiles.com/etext/AUTHORS/SHAKESPEARE/shakespeare-comedy-7.txt
go.cougs@login1 ~/tutorial $ wget http://www.textfiles.com/etext/AUTHORS/SHAKESPEARE/shakespeare-hamlet-25.txt
go.cougs@login1 ~/tutorial $ wget http://www.textfiles.com/etext/AUTHORS/SHAKESPEARE/shakespeare-romeo-48.txt
go.cougs@login1 ~/tutorial $ wget http://www.textfiles.com/etext/AUTHORS/SHAKESPEARE/shakespeare-taming-2.txt
go.cougs@login1 ~/tutorial $ wget http://www.textfiles.com/etext/AUTHORS/SHAKESPEARE/shakespeare-tragedy-58.txt
```

We will be creating a shell script that will provide us some statistics on the files including the number of characters, words, and lines.  To do this, you will learn about environment variables, arguments, and several new commands to mine information from files.

### The first pass

Our first pass at this problem will be to pass the file along to a command called ```wc``` which will count up the information we need.  It will be simple but it's always good to start out simple and stay simple as long as you can.  Create a file called ```stats.sh``` and put the following commands in it:

```sh
#!/bin/bash
wc shakespeare-comedy-7.txt
```

Use the ```chmod``` command to give the file execute permissions and run it:

```text
go.cougs@login1 ~/tutorial $ ./stats.sh 
 2851 16252 89439 shakespeare-comedy-7.txt
```

The ```wc``` command has given us the number of lines (2851), the number of words (16252) and the number of characters (89439) in the file.  This has given us what we wanted, but it is not very friendly.  Without reading the manual, it would be hard to tell what the values are, so let try to make it a little more clear.  To do this we need to explain two new concepts.  Pipes and variables  

### Adding variables and pipes

Pipes are similar to the *redirection* concept that you learned in the previous section, but instead of redirecting the output to a file we send the output of one command to the input of another by connecting them with the ```|``` character.  To see this in action, type the following command:

```text
go.cougs@login1 ~/tutorial $ echo "This goes to the next command" | wc
      1       6      30
```

The word count program receives the output of the echo command and tells us that there is one line, six words and thirty characters.  Notice that the file name was not at the end, this is because we didn't actually give it a file.

The next concept is variables.  Variables are temporary containers for your data, you can put whatever you want in them and then retrieve the data later.  In fact, they are used all of the time and even the shell that you are working in right now has variables that you can access.  Type the command ```env``` from the shell.  You should see alot of output that includes these variables (your's will be different):

```text
...
HOSTNAME=login1
TERM=xterm
SHELL=/bin/bash
...
PWD=/home/go.cougs/tutorial
PS1=\[\033[01;32m\]\u@\h\[\033[01;34m\] \w $\[\033[00m\] 
HOME=/home/go.cougs
LOGNAME=go.cougs
```

The shell gives you access to these variables so you can work within the environment and also customize your experience.  You can use ```echo``` to view these variables seperately, or you can use them in other ways to create paths, customize output, or determine what to do.  Notice that when you want to access the information in a variable, you use a ```$``` at the beginning of the name.

```text
go.cougs@login1 ~/tutorial $ echo $HOSTNAME
login1
go.cougs@login1 ~/tutorial $ echo $USER
go.cougs
```

For our script, we will define our own variables to store the information that we get from ```wc``` and then pipe and store the output to another command called cut which cuts a line based on a delimiter.  We can then output the lines, words and characters in a more friendly manner.  Add these changes to your script:

```sh
#!/bin/bash

OUTPUT=`wc shakespeare-comedy-7.txt`

LINES=`echo $OUTPUT | cut -d' ' -f1`
WORDS=`echo $OUTPUT | cut -d' ' -f2`
CHARS=`echo $OUTPUT | cut -d' ' -f3`

echo "Lines: $LINES"
echo "Words: $WORDS"
echo "Characters: $CHARS"
```

If we go through this line by line, we store the output from the ```wc``` command in a variable called ```OUTPUT```.  One thing to notice is the ``` ` ``` or the *backtick* usually found right under the escape key on the keyboard.  When you surround a string with backticks, you are evaluating (executing) the command and getting the output instead of just placing the command string itself in the variable.  Once we get the output of ```wc``` we ```echo``` the output and pipe it to the ```cut``` command using a blank space as the delimiter and assinging the value of the first field to ```LINES```, the second to ```WORDS```, and so on.  Lastly, we print out the values in a format that make it easy for us to see what we are looking at.

When it is run we get the following output:

```text
go.cougs@login1 ~/tutorial $ ./stats.sh 
Lines: 2851
Words: 16252
Characters: 89439
```

That's better, but now we need to do the same thing to our other files.  We could open the text editor and change the file name, but what happens if we have hundreds or thousands of files to look at.  To address this problem lets look at arguments, special variables and conditional statements

### Arguments, conditionals and special variables

You've seen arguments before.  We have used them with ```ls```, ```wget```, ```cut```, and so on.  They are the information that you pass to the command that lets the command know what to do, what file to work on, and where to put it after you are done.  The bash program will automatically grab everything after the command and create special variables that contain information about the arguments and the arguments themselves.  These special variables include:

* ```$#``` - Contains the number of arguments.
* ```$1``` - Contains the first argument.
* ```$2``` - Contains the second argument.  

See the pattern?  The third will be ```$3``` and so on.

When we need to deal with input, it's always a good thing to check to make sure we are getting what we expect, so we will use a conditional statement that includes ```if```, ```then```, and ```else``` to make sure we get the name of the file and let us know what we need to do if we forget to give it.

For the purposed of this tutorial, the condition of an ```if``` statement is surrounded by square brackets (```[ condition ]```).  Conditions can also be surrounded by double square brackets to prevent wildcard expansion and word splitting of variable values, but it is beyond the scope of the tutorial.  

The format of a conditional statement looks like this:

```sh
if [ condition ]
then
    # do this if the condition is met
else
    # do this if the condition is not met
fi
```

Notice the ```fi``` at the end.  That backwords ```if``` is the way bash knows that you are done with the conditional statement.  You can find more information about [conditional statments here](http://www.tldp.org/LDP/Bash-Beginners-Guide/html/chap_07.html)

Let's add in the argument handling so we can specify the file on the command line.  Your script will look like this:

```sh
#!/bin/bash

if [ $# != 1 ]
then
    echo "You need to give me a filename!"
    exit
else
    echo "Getting stats for $1"
fi

OUTPUT=`wc $1`

LINES=`echo $OUTPUT | cut -d' ' -f1`
WORDS=`echo $OUTPUT | cut -d' ' -f2`
CHARS=`echo $OUTPUT | cut -d' ' -f3`

echo "Lines: $LINES"
echo "Words: $WORDS"
echo "Characters: $CHARS"

```

We added the conditional, checking the special variable ```$#``` to see if there is 1 argument that was passed.  If we didn't get the argument we let ourselves know and exit immediately.  If the argument was given, we ```echo``` the filename and then use the ```$1``` in place of the filename for ```wc```.  

If everything works, you will see:

```text
go.cougs@login1 ~/tutorial $ ./stats.sh 
You need to give me a filename!
go.cougs@login1 ~/tutorial $ ./stats.sh shakespeare-comedy-7.txt 
Getting stats for shakespeare-comedy-7.txt
Lines: 2851
Words: 16252
Characters: 89439
go.cougs@login1 ~/tutorial $ ./stats.sh shakespeare-romeo-48.txt 
Getting stats for shakespeare-romeo-48.txt
Lines: 4579
Words: 25919
Characters: 144138
```

Now that we are accepting arguments, let's modify the script to take multiple files and output the stats for each of them by ***looping*** through each of the arguments.

### Loops

To iterate through multiple files that are passed in as arguments, we will use a ```for``` loop and another special variable that contains an array representation of all the arguments.  This special variable is ```$@``` and can be used with ```for``` to step through all the arguments one by one.  

The format of a the loop in this context looks like this:

```sh
for VARIABLE in $ARRAY
do
    # do something to $VARIABLE
done
```

Your final script will look like this:

```sh
#!/bin/bash

if [ $# -lt 1 ]
then
    echo "You need to give me a filename(s)!"
    exit
fi

for FILE in $@
do 
    echo "Getting stats for $FILE"
    OUTPUT=`wc $FILE`

    LINES=`echo $OUTPUT | cut -d' ' -f1`
    WORDS=`echo $OUTPUT | cut -d' ' -f2`
    CHARS=`echo $OUTPUT | cut -d' ' -f3`

    echo "Lines: $LINES"
    echo "Words: $WORDS"
    echo "Characters: $CHARS"
done
```

To process multiple files we start off by adjusting the conditional statement to only fail if we don't have at least one argument, and get rid of the else condition as we want to move the echoing of the filename to the loop.  The section of the script that processed the file is surrounded by the loop and we use the variable ```FILE``` to capture each item that is found in the special array. 

If everything works you will see:

```text
go.cougs@login1 ~/tutorial $ ./stats.sh shakespeare-romeo-48.txt 
Getting stats for shakespeare-romeo-48.txt
Lines: 4579
Words: 25919
Characters: 144138
go.cougs@login1 ~/tutorial $ ./stats.sh shakespeare-comedy-7.txt shakespeare-romeo-48.txt 
Getting stats for shakespeare-comedy-7.txt
Lines: 2851
Words: 16252
Characters: 89439
Getting stats for shakespeare-romeo-48.txt
Lines: 4579
Words: 25919
Characters: 144138
```

It works for a single file and multiple files, but as a bonus we can also use wildcards and bash will expand them to include all of the matching files:

```text
go.cougs@login1 ~/tutorial $ ./stats.sh *.txt 
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

From here, you can start experimenting.  For in depth information on scripting and the concepts that were presented you can find many good online references, including:

* [Beginning Bash](http://www.tldp.org/LDP/Bash-Beginners-Guide/html/index.html)
* [Advanced Bash Scripting](http://www.tldp.org/LDP/abs/html/index.html)
 
