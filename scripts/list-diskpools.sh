#!/bin/bash

#########################################################################
# File: list-diskpools.sh						#
# Script lists pools from the diskpools					#			                
#########################################################################

WORKDIR=$(cd $(dirname $0); pwd)
source ${WORKDIR}/lib.sh

# Print help and exit
function usage()
{
	 _info "Usage: $0
	-h|--help    Print this help message
	"
	exit 2;
}

# Lists pools from the diskpools
function list_diskpools
{
	# Get existing diskpools
	diskpools=$(zpool list -H -o name)
	exitCode=$?
	if [[ $exitCode -ne 0 ]]; 
	then 
		_error "Failed: Fetch diskpools"
	else 
		_info "Diskpools fetched so far:\n${diskpools}"
	fi
}

####################################
# Main function script starts here #
####################################
function main()
{
	# Not expecting any argument	
	[[ "$#" -ge 1 ]] && usage
	list_diskpools
}

main $@
# End: list-diskpools.sh
