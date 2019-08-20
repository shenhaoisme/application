#! /bin/bash
NUMBER=( 8 8 5 6 )

echo ${NUMBER[1]}

for i in ${NUMBER[@]}
do
	echo ${i}
       	#key sim ${i}
done
#bash是linux 内置的shell，dash是bash的阉割版，d->debian
#本身 /bin/sh 连接到 bash, 因为普通使用 dash 就够用了, 所以标准也建议
#把sh重定向到dash，现在ubuntu deian 都指向dash

#知道背景故事后，上面的代码在 bash 下可以运行，但在dash是不可以的
#sh 执行会失败，source 成功

#为此，总结 dash bash 语法区别
#
