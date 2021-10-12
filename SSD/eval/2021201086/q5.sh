#!/bin/bash
#remove folder and contents if already exists
rm -rf temp_activity
mkdir temp_activity
cd temp_activity
#create 50 text files
touch temp{1..50}.txt
#rename 1-25 to .md
for i in {1..25}
do
   mv temp$i.txt temp$i.md
done
#append modified to all filenames
for file in *.*
do
    filename=${file%.*}
    extension=${file##*.}
    mv $file ${filename}_modified.$extension
done
#compress all the text files
zip txt_compressed.zip *.txt