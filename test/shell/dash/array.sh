#! /bin/sh

#本身 bash style

bash(){
	IFS=""
	var="this is a test|second test| the quick fox"
	IFS="|"  
	#注释掉。不然dash解析会出错
	#test=( $var ) 
	#echo ${test[0]} 
	#echo ${test[1]}
}
#echo "using bash"
#/bin/bash bash


dash(){
	IFS=""
	var="this is a test|second test| the quick fox"
	#oldIFS
	IFS="|"
	set -- $var
	echo $1
	echo $2
}
#echo "using dash"
dash






