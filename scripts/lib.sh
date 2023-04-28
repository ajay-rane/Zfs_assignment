#!/bin/bash

#########################################################################
# File: lib.sh        	                                                #
# Library file used for ZFS shell scripts                               #
#########################################################################

# Print error and exit
function _error() 
{
	echo -e "$@ \nExiting..."; 
	exit 2; 
}

# Print info
function _info() 
{ 
	echo -e "\n$@"; 
}

# End: lib.sh 
