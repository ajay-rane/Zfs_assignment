#!/bin/bash

#########################################################################
# File: list-disks-in-diskpools.sh					#
# Script lists disks from the diskpool					#
#########################################################################

WORKDIR=$(cd $(dirname $0); pwd)
source ${WORKDIR}/lib.sh

# Print help and exit
function usage()
{
	_info "Usage: $0 diskpoolname
	-h|--help         Print this help message
	"
	exit 2;
}

# List disks from the diskpools
function list_disks_in_diskpools
{
	poolname=${1}
	# Get existing diskpools
	diskpools=$(zpool list -H -o name)
	exitCode=$?
	if [[ $exitCode -ne 0 ]];
	then
		_error "Failed: Fetch diskpools"
	fi

	#Check for the given pool name is a part of diskspool or not.
	if [[ "${diskpools}" =~ .*"${poolname}".* ]]; 
	then 
		# Get existing disks list from given pool name
		diskslist=$(zpool list  -v $poolname | awk 'NR > 2 { print $1}')
		exitCode=$?
		if [[ $exitCode -ne 0 ]]; 
		then 
		_error "Failed: Fetch diskpools"
		else
			_info "List of disks in diskpool $poolname is \n${diskslist}"
		fi
	else
		_error "Invalid poolname [${poolname}]"
	fi
}

####################################
# Main function script starts here #
####################################
function main()
{
	# Expect only one arg (diskpool name)
	[[ "$#" -ne 1 ]] && usage
	list_disks_in_diskpools $1
}

main $@
# End: list-disks-in-diskpools.sh
