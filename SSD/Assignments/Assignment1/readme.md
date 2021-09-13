# SSD ASSIGNMENT 1
```bash
.
├── q1.sh
├── q2.sh
├── q3.sh
├── q4.sh
├── q5.sh
└── readme.md
```
## Question 1
### File name : q1.sh
#### Strategy :
1. Use `du` command to extract size of each directory in Bytes
2. Use `sort` command to sort each line according to the Bytes in reverse 
3. Use `numfmt`to convert the bytes to nearest human readable form in /K/M/G
4. Cleaning the output and applying tab delimiter
##### Assumptions :
1. Directory names doesn't contain spaces
2. Output format is in K/M/G as mentioned

#### I/O Format :
```bash
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q1$ ./q1.sh
dummy1  153M
dummy4  80M
dummy2340       13M
dummy3  1.4M
dummy5  4.1K
```
## Question 2
### File name : q2.sh
#### Strategy :
1. Using the `grep` command to find words ending with "ing" and using the options `w` for word `o` for displaying only matched words and `i` for ignoring case
2. Translating the output to lower case using `tr`
#### Assumptions :
1. In output.txt all words are printed in lower-case
#### I/O Format :
```bash
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q2$ cat input.txt
fighting cleaning store food
fox wolf cow shining xeal.
exhume right sdsing asdas
sadmask ing exter xings FEELING.
Dragon rider SEEMInG shy
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q2$ ./q2.sh input.txt output.txt
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q2$ cat output.txt
fighting
cleaning
shining
sdsing
ing
feeling
seeming
```
## Question 3
### File name : q3.sh
#### Utility Functions :
`sort_char`:

__Sorts the input string lexicographically__

#### Strategy :
1. Taking the input and sorting the characters using `sort_char` and storing in a variable.
2.  Using `compgen -c` to generate the list of bash commands and storing the unique commands in sorted order in a file called `temp`.
3. To reduce computation time I am removing all the commands from the list that are not of equal length to the input string using `awk` and storing it in a new file called `temp2` and deleting the old file.
4. Reading the filtered command list one command at a time from `temp2` and sorting its characters as well using the `sort_char` function.
5. Then there is an equality check and if they match I am adding the command in the output array `out` and setting a marker called `flag`.
6. Removing the temporary file `temp`
and printing the appropriate output.

#### Assumptions :

#### I/O Format :
```bash
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q3$ ./q3.sh act

YES     cat     tac
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q3$  ./q3.sh ubuntu-core-launcher
YES     ubuntu-core-launcher
```
## Question 4
> __Assumptions__ : Roman Numbers are in capital
### File name : q4.sh
#### Utility Functions :
##### `rom_to_int`:
__Converts Roman Number to Integer__

It extracts each substraction notation and replaces it with its corresponding lower unit roman numerals using the replace functionality of `sed` command recursively.
Then it removes a newline before doing a count using `tr` and `wc` commands.
##### `int_to_rom`:
__Converts Integer to Roman__

We run a loop for

Strategy:
1. If number 
## Question 5
> __Assumption__ : 