#! /bin/bash
echo -n Enter file path:
read file_path
if [ `ls -la $file_path 2> temp.txt | wc -l` -eq 0 ];then 
echo $file_path has passwords are enabled!
else
	echo $file_path is accessible!
	if [ `echo $file_path | grep / | wc -l ` -ne 0 ];then
		parent=`dirname $file_path`
		filename=`basename $file_path`
		temp=(`ls -la $parent | grep $filename`)	
	else
		temp=(`ls -la | grep $file_path`)
	fi
	if [ `echo ${temp[0]} | grep w | wc -l` -ne 0 ];then
		echo You have permissions to edit $file_path!
		else
			echo You do not have the permissions to edit $file_path!	
	fi
	
fi
rm temp.txt