#!/bin/bash
# norminette -R CheckForbiddenSourceHeader CheckDefine

if [ "$1" == 'init' ]; then
	sed -i '/42tester/d' ~/.bashrc
	echo `alias 42tester="$(pwd)/42tester.sh"` >> ~/.bashrc
	echo 'init'
	exit
fi

if [ -e "libft.h" ]; then
	echo 'libft'
else
	echo 'nah'
fi