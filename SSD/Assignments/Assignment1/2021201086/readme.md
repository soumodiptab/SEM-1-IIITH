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
##### `sort_char`:

__Sorts the input string lexicographically__
It takes the input string and puts all the characters in different lines using `grep` and then uses `sort` to sort the characters and then removes all the newlines using `tr` to recombine the sorted string and return back

#### Strategy :
1. Taking the input and sorting the characters using `sort_char` and storing in a variable.
2.  Using `compgen -c` to generate the list of bash commands and storing the unique commands in sorted order in a file called `temp`.
3. To reduce computation time I am removing all the commands from the list that are not of equal length to the input string using `awk` and storing it in a new file called `temp2` and deleting the old file.
4. Reading the filtered command list one command at a time from `temp2` and sorting its characters as well using the `sort_char` function.
5. Then there is an equality check and if they match I am adding the command in the output array `out` and setting a marker called `flag`.
6. Removing the temporary file `temp2`
and printing the appropriate output.

#### Assumptions :
1. It is allowed to create temporary files during script execution and delete them.
> __Note__ : There is a newline character after the output so that the shell prompt comes to the nextline.
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

We run a loop for each Roman Numeral's decimal value from highest to lowest and check it that numeral value is able to divide the number and if it does then add that numeral to our output and extract the remainder and continue looping until number is zero.
#### Strategy:
1. If number of arguments is 1 then convert integer to roman using `int_to_rom` function.
2. For 2 arguments check if both are roman numbers using search and replace i.e. if the roman number contains I,V,X,L,C,D,M then it becomes empty string and then use function `rom_to_int` to convert to corresponding integer and then perform the sum operation.
3. Similarly if both are integers then first add them up and then use `int_to_rom` function to convert to roman numeral.
>__NOTE__: 
> * If one of the input is invalid it prints nothing.
> * If the number of arguments are invalid then also it prints nothing.
> * If single argument given and it is roman print nothing.
#### I/O Format :
```bash
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q4$ ./q4.sh 123
CXXIII
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q4$ ./q4.sh VIII IX
17
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q4$ ./q4.sh 12 29
XLI
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q4$ ./q4.sh VII 29
```
## Question 5
### File name : q5.sh
#### Strategy :
1. Create a directory called `temp_activity` using `mkdir` command. If directory already exists then remove it using `rm` and remove all of its contents recursively.
2. Change the `pwd` to `temp_activity`
3. Create 50 text files using `touch` command.
4. Run a loop from 1 to 25 and rename each file from `.txt` to `.md` using `mv` command.
5. For all files with an extension extract filename and extension
and append "_modified" to the filename and rename using `mv` command.
6. zip all the `.txt` files using zip command.
>__NOTE__ : During zip output is generated related to what files are being zipped. 
#### I/O Format :
```bash
soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q5$ ./q5.sh
  adding: temp26_modified.txt (stored 0%)
  adding: temp27_modified.txt (stored 0%)
  adding: temp28_modified.txt (stored 0%)
  adding: temp29_modified.txt (stored 0%)
  adding: temp30_modified.txt (stored 0%)
  adding: temp31_modified.txt (stored 0%)
  adding: temp32_modified.txt (stored 0%)
  adding: temp33_modified.txt (stored 0%)
  adding: temp34_modified.txt (stored 0%)
  adding: temp35_modified.txt (stored 0%)
  adding: temp36_modified.txt (stored 0%)
  adding: temp37_modified.txt (stored 0%)
  adding: temp38_modified.txt (stored 0%)
  adding: temp39_modified.txt (stored 0%)
  adding: temp40_modified.txt (stored 0%)
  adding: temp41_modified.txt (stored 0%)
  adding: temp42_modified.txt (stored 0%)
  adding: temp43_modified.txt (stored 0%)
  adding: temp44_modified.txt (stored 0%)
  adding: temp45_modified.txt (stored 0%)
  adding: temp46_modified.txt (stored 0%)
  adding: temp47_modified.txt (stored 0%)
  adding: temp48_modified.txt (stored 0%)
  adding: temp49_modified.txt (stored 0%)
  adding: temp50_modified.txt (stored 0%)
```