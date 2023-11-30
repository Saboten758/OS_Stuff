#! /bin/bash
echo -n Enter the name of the file:
read c
if [ `ls -la | grep $c | wc -l` -eq 0 ]; then
echo No such file exists!
else
	temp=(`ls -la | grep $c`)
	if [ `echo ${temp[0]} | grep d | wc -l` -eq 0 ];then
		echo Not a Directory!
		if [ `echo ${temp[8]} | grep .txt | wc -l` -ne 0 ]; then
			echo Printing Contents of $c.txt:
			cat $c.txt
		else
			echo Not a text file!
		fi
		
	else
		echo Directory!
		ls -l $c
	fi
fi