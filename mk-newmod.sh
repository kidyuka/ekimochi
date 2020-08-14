#!/usr/bin/bash

if [ "$1" = "" ]; then
    echo "mk-newmod.sh <NEW-Module-Name> <Module-Directry-Name>"
    exit 1
fi 

if [ "$2" = "" ]; then
    DIR_NAME=$1
else
    DIR_NAME=$2
fi

NEW_MOD_NAME=$1

if [ -e ${DIR_NAME} ]; then
    echo "${DIR_NAME} はすでに存在している"
    exit 1
fi

mkdir -p ${DIR_NAME}
mkdir -p ${DIR_NAME}/include
perl ./Template/genfile.pl ./Template/Template.cpp.tmp ${DIR_NAME}/${NEW_MOD_NAME}.cpp -NAME ${NEW_MOD_NAME}
perl ./Template/genfile.pl ./Template/Template.cfg.tmp ${DIR_NAME}/${NEW_MOD_NAME}.cfg -NAME ${NEW_MOD_NAME}
perl ./Template/genfile.pl ./Template/Template.h.tmp   ${DIR_NAME}/include/${NEW_MOD_NAME}.h -NAME ${NEW_MOD_NAME}

