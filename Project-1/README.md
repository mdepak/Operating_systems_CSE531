Project Description:
--------------------

Part 1: // this part is not to be submitted

This is a self-study project. Run all the programs (threads, locking, semaphores, monitors) from the p-threads tutorial (to be) discussed in class. The files are available in zip format: Link -> here

1.       Run each program. Make sure you understand the output and how it works

2.       Make changes to the program and observe what happens. Be creative; do not be afraid of breaking it. It can be a valuable learning experience.

Details of running

The programs have to be compiled with p-threads library. Use gcc and not an IDE. Each program is self-contained and needs one compile, no makefile needed.

The compile command is:

            gcc –lpthread filename.c   // note the –lpthread option is not needed in some versions of Linux

The programs work with Linux, If you have a machine (or virtual machine) that has Linux installed, you have nothing to do other than download, unzip and go.

Part 2: // to be submitted

 

Write a program that does the following.

1.       The main (parent) thread initializes an array of 3 integers to zero.

2.       The parent creates 3 children. Child i adds 1 to array[i], where i = 0, 1, 2.

3.       The parent waits for the children to finish adding, and then prints the values in the array.

4.       The children wait for the parent to finish printing and then repeats (adds 1 to an an element of the array)

5.       Continues forever

 

Use pthreads and semaphores provided by the programs in part 1. Create the file using the examples provided and put the code in proj-1.c. You can include any of the .h files provided.

 

Extra: Do not submit – Write the program such that instead of 3 there can be any number of children up to 100 and the array holds 100 integers. The actual number is passed to the program at runtime (command line argument) and. If the number is n, n children works on n elements of the array.