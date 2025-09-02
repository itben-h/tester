#!/bin/bash

COLOR_R='\033[0;31m'
COLOR_G='\033[0;32m'
COLOR_Y='\033[0;33m'
COLOR_END='\033[0m'

NAME=bhtester
EXT=.test

if [ "$1" == 'init' ]; then
	RC="$HOME/.bashrc"
	if [ "$SHELL" = "/bin/zsh" ]; then
		RC="$HOME/.zshrc"
	fi
	SCRIPT="$(pwd)/$NAME.sh"
	if ! grep "bhtester=" "$RC" &> /dev/null; then
		printf "\nalias bhtester=$SCRIPT\n" >> "$RC"
	fi
	echo "Alias added for bhtester! Use it in project dirs!"
	exec $SHELL
fi

CURR_DIR=$(pwd)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=build
cd $SCRIPT_DIR
mkdir -p $BUILD_DIR

if [ "$1" == 'clean' ]; then
	make clean
	exit 0
fi

makefile_check () {
	if [ ! -e "$CURR_DIR/Makefile" ]; then
		echo "Makefile missing! Aborting..."
		exit
	fi
}

norm_check () {
	if ! command -v norminette >/dev/null 2>&1; then
		echo "Warning: Norminette not present.."
	else
		if norminette -R CheckForbiddenSourceHeader -R CheckDefine $CURR_DIR | grep 'Error!'; then
			printf "${COLOR_R}Norminette Failure!${COLOR_END}\n"
		else
			printf "${COLOR_G}Norminette Cleared!${COLOR_END}\n"
		fi
	fi
}

if [ -e "$CURR_DIR/libft.h" ]; then
	makefile_check
	norm_check
	cp $CURR_DIR/* $BUILD_DIR &> /dev/null
	make libft
	./libft"${EXT}"
else
	echo "Have you ran 'bhtester.sh init'?"
fi
