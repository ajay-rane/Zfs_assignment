#!/bin/bash

#########################################################################
# File: list-diskpools-free-space.sh					#
# Script lists free space of the diskpools				#
#########################################################################

WORKDIR=$(cd $(dirname $0); pwd)
source ${WORKDIR}/lib.sh

# Print help and exit
function usage()
{
	_info "Usage: $0
	-h|--help         Print this help message
	"	
	exit 2;
}

# Lists free space of the diskpools
function list_diskpools_free_space
{
	# Get existing diskpool with their free space and total size
	#diskpools=$(zpool list | awk 'NR>1 {print $1 "  " $4; sum += $4} END { print "Total "  sum "G" }')
	diskpools=$(zpool list | awk 'NR>1 {print $1 "  " $4}')		
	exitCode=$?
	if [[ $exitCode -ne 0 ]]; 
	then 
		_error "Failed: Fetch diskpools"
	else 
		_info "Diskpools fetched so far:\n${diskpools}"
	fi

	# Get existing diskpools size
	disksize=($(zpool list -H -o size))
	exitCode=$?
	[[ $exitCode -ne 0 ]] && _error "Failed: Fetch diskpools size"
	
	sum=0
	for ((idx=0; idx<${#disksize[@]}; ++idx))
	do
		# Convert TB to GB
		n=$(echo "${disksize[idx]}" | awk '{ if($1 ~ /T$/) { print $1 * 1024 } else {print $1*1;} }')
		sum=`expr ${sum} + ${n}`
	done

	if [ ${sum} -gt 1023 ]
	then
		sum=$(echo " scale=2; ${sum}/1024" | bc -l)
		_info "Total ${sum} TB"
	else
		_info "Total ${sum} GB"
	fi
}

####################################
# Main function script starts here #
####################################
function main()
{
	# Not expecting any argument
	[[ "$#" -ge 1 ]] && usage
	list_diskpools_free_space
}

main $@
# End: list-diskpools-free-space.sh
