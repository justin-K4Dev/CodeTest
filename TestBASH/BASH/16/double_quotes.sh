#!/bin/bash
 
# Declare bash string variable
BASH_VAR="Bash Script"

# echo variable BASH_VAR
echo $BASH_VAR

# meta characters and its special meaning in bash is 
# suppressed when using double quotes except "$", "\" and "`"

echo "It's $BASH_VAR  and \"$BASH_VAR\" using backticks: `date`"