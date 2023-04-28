#!/bin/bash

#########################################################################
# File: list-diskpools-filtered.sh					#
# Script filter diskpools on the bases of available free space		#
#########################################################################

WORKDIR=$(cd $(dirname $0); pwd)
source ${WORKDIR}/lib.sh

# Print help and exit
function usage()
{
	_info "Usage: $0 <morethan|lessthan> <size in GB|TB>
 		Eg. $0 lessthan 39GB 
	-h|--help         Print this help message
	"
	exit 2
}

# Filter diskpools on the bases of available free space 
function filter_diskpools
{
	filter=${1}
	poolsize=${2}
	poolsizewidth=${#poolsize}

	if [[ "${filter}" != "morethan" && "${filter}" != "lessthan" ]] || [[ ${poolsize: -2} != "TB" && ${poolsize: -2} != "GB" ]] || 
		[[ ${poolsizewidth} -lt 3 ]] || [[ ! ${poolsize:: -2} =~ ^[0-9]+$ ]]	    
	then
		_error "Invalid input, Look at help"
	fi
	
	# Convert TB to GB
	poolsize=$(echo "${poolsize}" | awk '{ if($1 ~ /TB$/) { print $1 * 1024 } else {print $1*1;} }')
	
	# Get existing diskpools size
	disksize=($(zpool list -H -o size))
	exitCode=$?
	[[ $exitCode -ne 0 ]] && _error "Failed: Fetch diskpools size"

	# Get existing diskpools name
	diskname=($(zpool list -H -o name))
	exitCode=$?
	[[ $exitCode -ne 0 ]] && _error "Failed: Fetch diskpools name"

	#_info "$diskname" # remove it
	#_info "$disksize" # remove it

	_more=""
	_less=""
	
	for ((idx=0; idx<${#disksize[@]}; ++idx))
	do
		n=$(echo "${disksize[idx]}" | awk '{ if($1 ~ /T$/) { print $1 * 1024 } else {print $1*1;} }')
		if (( $(echo "$n < $poolsize" | bc -l) ));
		then
			#echo  "${diskname[idx]} ${disksize[idx]} GB" 
			_less+="${diskname[idx]} ${disksize[idx]} GB\n" 
		else
			#echo  "${diskname[idx]} ${disksize[idx]} GB" 
			_more+="${diskname[idx]} ${disksize[idx]} GB\n" 
		fi
	done
	
	if [ $filter == "lessthan" ]
	then
		_info "${_less}"
	elif [ $filter == "morethan" ]
	then
		_info "${_more}"
	fi
}

####################################
# Main function script starts here #
####################################
function main()
{
	# Expect two args (<morethan|lessthan> <size in GB|TB>)	
	[[ "$#" -ne 2 ]] && usage
	filter_diskpools $1 $2
}

main $@
# End: list-diskpools-filtered.sh
