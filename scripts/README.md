We are having 4 scripts.

1) list-diskpools.sh 		 :==> This script is for listing all the diskpools. Usage is as below,
			   	       ./list-diskpools-free-space.sh

2) list-disks-in-diskpools.sh   :==> This script is for listing the disks from the given diskpool. For this script only one argument i.e. poolname is required. Usage is as below,
	                              ./list-disks-in-diskpools.sh poolname

3) list-diskpools-free-space.sh :==> This script listing the existing diskpools with available free space and total free space available on all diskpools. Usage is as below,
				      ./list-diskpools-free-space.sh	
				      This script support only for free space size avaible in GB and TB (Not supported for size in KB, MB and PB).

4)list-diskpools-filtered.sh    :==> This script filters diskpools on the basis of available free space of diskpools. This script takes two arguments i.e. <morethan|lessthan> <size in GB|TB>.  Usage is 						as below, 
				      ./list-diskpools-filtered.sh morethan 40GB				      
				      
