prerequisites:
	ZFS file system should be installed on linux system. if not installed, use the below command,
	   sudo apt install zfsutils-linux
	System should have multiple disks or partitions to test the program.

1) To build the program, use the below commands,
	make clean -s
	make -s

2) To execute the program, use the below command. (At very first time, you will need to enter credentials required to execute the pool commands)
	./Executable_file

	1: Create disk pool
	2: List all disk pools
	3: Add disk to the specified disk pool
	4: Get list of disks in the specified disk pool
	5: Remove disk from the specified disk pool
	6: Destroy pool
	Enter the desired option from 1 to 6

3) From this point, you can proceed according to selected options.	
