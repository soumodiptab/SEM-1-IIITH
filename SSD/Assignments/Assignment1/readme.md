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
> __Assumption__ : No Spaces in directory names
#### Strategy :
1. Use `du` command to extract size of each directory in Bytes
2. Use `sort` command to sort each line according to the Bytes in reverse 
3. Use `numfmt`to convert the bytes to nearest human readable form in B/KB/MB/GB
4. Cleaning the output and applying tab delimiter
#### Output :
    soumodiptab@Gigabyte-B450M:~/Desktop/Practice/Assignment1/Q1$ ./q1.sh
    dummy1  153MB
    dummy4  80MB
    dummy2  13MB
    dummy3  1.4MB
    dummy5  4.1KB
## Question 2
### File name : q2.sh

## Question 3
### File name : q3.sh

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

Strategy:
1. If number 
## Question 5
> __Assumption__ : 