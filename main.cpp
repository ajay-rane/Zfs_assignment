
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include "zpool.h"

using namespace std;


int main() 
{
	bool ret;
	int option;
	char consent;
	Zpool obj;

	cout << "1: Create disk pool" << endl;
	cout << "2: List all disk pools" << endl;
	cout << "3: Add disk to the specified disk pool" << endl;
	cout << "4: Get list of disks in the specified disk pool" << endl;
	cout << "5: Remove disk from the specified disk pool" << endl;
	cout << "6: Destroy pool" << endl ;
	cout << "Enter the desired option from 1 to 6" << endl << endl;

	cin >> option;


	while(!cin)
	{
		cout << "Bad option" << endl;
		cin.clear();
		while(cin.get() != '\n');
		cin >> option;
	}

	if(option < 1 || option > 6)
	{
		cout << "Enter the proper option" << endl;
		return 0;
	//	continue;
	}

	switch(option)
	{
		case 1:
			ret = obj.Create_disk_pool();
			if(ret == false)
			{
				cout << "Create_disk_pool() failed" << endl << endl;;
			}
			break;
		
		case 2:
			ret = obj.List_disk_pools();
			if(ret == false)
			{
				cout << "List_disk_pools() failed" << endl << endl;;
			}
			break;

		case 3:	
			ret = obj.Add_disks_to_pools();
			if(ret == false)
			{
				cout << "Add_disks_to_pools() failed" << endl << endl;;
			}
			break;
		
		case 4:
			ret = obj.Get_list_of_disks_in_the_specified_disk_pool();	
			if(ret == false)
			{
				cout << "Get_list_of_disks_in_the_specified_disk_pool() failed" << endl << endl;
			}
			break;

		case 5:
			ret = obj.Remove_disk_from_the_specified_disk_pool();
			if(ret == false)
			{
				cout << "Remove_disk_from_the_specified_disk_pool() failed" << endl << endl;
			}

			break;
		case 6:
                        ret = obj.Destroy_pool();
                        if(ret == false)
                        {
                                 cout << "Destroy_pool() failed()" << endl << endl;
                        }

                                break;
		default:
			exit(0);				
	}

	return 0;
}



