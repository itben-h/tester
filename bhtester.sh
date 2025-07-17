#!/bin/bash

COLOR_Y='\033[0;33m'
COLOR_END='\033[0m'

NAME=bhtester

# init should only be run directly
if [ "$1" == 'init' ]; then
	(return 0 2>/dev/null)
	if [ $? -eq 0 ]; then
		alias "$NAME=$(pwd)/$NAME.sh"
		echo "$NAME aliased!"
		return 0
	else
		echo "Please run ./$NAME.sh init in 'source' mode"
		exit 1
	fi
fi

CURR_DIR=$(pwd)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=build
cd $SCRIPT_DIR
mkdir -p $BUILD_DIR

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
			printf "${COLOR_Y}Norminette Failure!${COLOR_END}\n"
		fi
	fi
}

if [ -e "$CURR_DIR/libft.h" ]; then
	makefile_check
	norm_check
	cp $CURR_DIR/* ./$BUILD_DIR
else
	echo 'nah'
fi
