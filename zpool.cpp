
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include "zpool.h"

using namespace std;
	
map<int,string> Zpool::zpool_list()
{
       	int iCount = -1;
       	FILE * pipe = NULL;
       	char buffer[128];
       	map<int, string> poolmap;


       	//pipe = popen("echo Ajay@123 | sudo -S  zpool list\n", "r");
       	pipe = popen("sudo zpool list\n", "r");
       	if (!pipe)
       	{
               	cout << "popen error" << endl;
               	return poolmap;
       	}
       	fgets(buffer, 128, pipe);
	poolmap_.clear();
       	while(fgets(buffer, 128, pipe) != NULL)
       	{
               	iCount++;
               	*(strchr(buffer, ' ')) = '\0';
       		poolmap[iCount] = buffer;
       	       // cout << iCount << ":  " << poolmap_[iCount] << endl;
       	}
	
	return poolmap;
}
	

map<int, string> Zpool::free_disk_list()
{
	int iCount = -1;
	bool found = false;
        map<int, string> freedisklist;
	auto itr = diskslist_.begin();
	auto itr1 = diskmap_.begin();
	map<int, string>::iterator itr2;
	while(itr != diskslist_.end())
	{
		found = false;
		itr1 = diskmap_.begin();
		while(itr1 != diskmap_.end())
		{
			itr2 = (itr1->second).begin();
			while(itr2 != (itr1->second).end())
			{
				if(itr2->second ==  *itr )
				{
					found = true;
					break;
				}
				itr2++;
			}
			if(found == true)
			{
				break;
			}
			itr1++;
		}
			
		if(found == false)
		{
			freedisklist[++iCount] = *itr;
			//cout << iCount << ":  "<< *itr << endl;
		}
		itr++;
	}
	return freedisklist;
}


vector<string> Zpool::disks_list()
{
        int iCount = -1;
	char buffer[128];
       	FILE * pipe = NULL;
       	vector<string> disklist;
	//pipe = popen("echo Ajay@123 | sudo -S  fdisk -l \n", "r");
	pipe = popen("sudo fdisk -l \n", "r");

	if (!pipe)
       	{
               	cout << "Error: pipe" << endl;
       		return disklist;
       	}


       	while(fgets(buffer, 128, pipe) != NULL)
       	{
               	if(!strncmp(buffer, "Device", 6))
               	{
                       	iCount = -1;
       			fgets(buffer, 128, pipe);
       			fgets(buffer, 128, pipe);
                       	while (fgets(buffer, 128, pipe) != NULL && buffer[0] != '\n')
                       	{
                               	iCount++;
                               	*(strchr(buffer, ' ')) = '\0';
                               	disklist.push_back(strrchr(buffer, '/') + 1);
                              // 	cout << iCount << ":  " << strrchr(buffer, '/') + 1 << endl;
                       	}
		}
	}
	return disklist;
}	


map<string, map<int, string> >  Zpool::Get_list_of_disks_of_pools()
{
	string cmd;
	int index = 0;
	int index1 = 0;
       	int iCount = -1;
       	char buffer[128];
       	FILE * pipe = NULL;
       	map<int, string> diskmap;
       	map<string, map<int, string> > diskdmap;

	if(poolmap_.size() == 0)
	{
		return diskdmap;
	}
	cmd = 	"sudo zpool status ";
	pipe = popen(cmd.c_str(), "r");

	if (!pipe) 
	{
               	cout << "popen error" << endl;
		return diskdmap;
	}

	while(fgets(buffer, 128, pipe) != NULL)
       	{
		index = string(buffer).find_first_not_of(" \t");
                index1 = string(&buffer[index]).find_first_of(" : \n");
		(&buffer[index])[index1] = '\0';
		auto itr = poolmap_.begin();
	        while(itr != poolmap_.end())
		{
			if(itr->second == &buffer[index])
			{
				break;
			}
			itr++;
		}

		if(itr != poolmap_.end())
		{
			iCount = -1;
			diskmap.clear();
			while (fgets(buffer, 128, pipe) != NULL && buffer[0] != '\n')
	                {
				iCount++;
                               	index = string(buffer).find_first_not_of(" \t");
                               	index1 = string(&buffer[index]).find_first_of(" : \n");
			  	(&buffer[index])[index1] = '\0';
                               		 
				 diskmap[iCount] = &buffer[index];
				 diskdmap[itr->second] = diskmap;
                       	}
	       }
	}

	/*
	for(auto itr1 = diskdmap.begin(); itr1 != diskdmap.end(); itr1++)
	{
		cout << itr1->first << ":"  << endl;
		for(auto itr2 = (itr1->second).begin(); itr2 != (itr1->second).end(); itr2++)
		{
			//cout << itr2->first << itr2->second << endl;
		}
		cout << endl << endl;
	}

	cout << endl;	
*/	pclose(pipe);
 	
	return diskdmap;
}

	
bool  Zpool::Create_disk_pool() 
{
	char consent;
	int option = 0;
	string poolname;
       	char buffer[128];
	string result = "";
 	FILE * pipe = NULL;
	vector<int> options;
	map<int, string> diskmap;


	auto itr_pool = poolmap_.begin();
	while(itr_pool != poolmap_.end())
	{
		cout << itr_pool->first << ": " << itr_pool->second << endl;
		itr_pool++;
	}

	cout << endl ;

 	while(1)
	{
		cout << "Enter the pool name" << endl;
   		cin >> poolname;
		cout << endl;

		if(isalpha(poolname[0]))
   		{
			break;
		}

		cout << "pool name should be start with alphabet" << endl;
	}

	auto itr = poolmap_.begin();
	while(itr != poolmap_.end())
	{
		if(poolname == itr->second)
		{
			cout <<  poolname << " is already present" << endl << endl;;
  			
			while(1)
		        {
       				cout << "Enter the pool name" << endl;
       				cin >> poolname;
				cout << endl;
				
       				if(isalpha(poolname[0]))
       				{
               				break;
       				}
		
       				cout << "pool name should be start with alphabet" << endl << endl;
			}

			itr = poolmap_.begin();
			continue;
		}

		itr++;
	}
 
	
	auto itr1 = freedisklist_.begin();
	while(itr1 != freedisklist_.end())
	{
		cout << itr1->first << ": " << itr1->second << endl;
		itr1++;
	}


	while(1)
	{
		cout << "Enter the option which disk need to be add from 0 to " << freedisklist_.size() - 1 << endl;
		cin >> option;
		cout << endl;
		
		if (!cin)
	  	{
			cin.clear();
		  	while (cin.get() != '\n')
	  		{
	  			continue;
		  	}
		  	cout << "Error Bad input;\n";

			continue;
		}
	
	 	if (option < 0 || option > freedisklist_.size() - 1)
       		{
			cout << "Enter the proper option" << endl;
		  	continue;
	  	}
	
	  	if(find(options.begin(), options.end(), option) != options.end())
 		{
			cout << "you have already select this option" << endl;
		  	continue;
  		}

  		options.push_back(option);
			
  		result = result + freedisklist_[option] + " ";
	
  		cout << "Do you want to add more disks to pool: Y or N" << endl;
 		cin >> consent;

		if(!(consent == 'Y' || consent == 'y'))
 		{
			break;
  		}
	}
    
	string cmd = "sudo zpool create -f " ;
	cmd.append(poolname).append(" ");
	cmd.append(result);
//	cout << cmd.c_str();
	pipe = popen(cmd.c_str(), "r");
	if (!pipe)
        {
                cout << "popen error" << endl;
                return false;
        }


	cout << endl;
	zpool_list();
	Get_list_of_disks_of_pools();
	free_disk_list();

	return true;
}



bool Zpool::List_disk_pools()
{
	if(poolmap_.size() == 0)
	{
		cout << "No pool available" << endl;
		return true;
	}
	auto itr = poolmap_.begin();
       	while(itr != poolmap_.end())
	{
		cout << itr->first << ": " << itr->second << endl;
		itr++;
	}	
	cout << endl;
	return true;
}


bool Zpool::Add_disks_to_pools()
{
	int ret;
	char consent;
	int option = 0;
	int pool_option;
	string result = "";
	vector<int> options;

	if(poolmap_.size() == 0)
        {
                cout << "No pool available" << endl;
                return true;
        }

	cout << endl;
	ret = List_disk_pools();
	if(!ret)
	{
		cout << "List_disk_pools()" << endl;
		return false;
	}

	cout << endl;

       	while(1)
       	{
               	cout << "Enter the  option in which pool you need to add disk" << endl;
		cin >> pool_option;
		if(!cin)
		{
			cin.clear();
			while(cin.get() != '\n');
			cout << "Bad option" << endl;
			continue;
		}

       	        if (pool_option < 0 || pool_option > poolmap_.size() - 1)
               	{
			cout << "Enter the proper option" << endl;
               	      continue;
               	}

		break;
       	}

	auto itr1 = freedisklist_.begin();
        while(itr1 != freedisklist_.end())
        {
		cout << itr1->first << ": " << itr1->second << endl;
		itr1++;
       	}

	while(1)
	{
		cout << "Enter the option which disk need to be add from 0 to " << freedisklist_.size() - 1 << endl;
	  	cin >> option;
		cout << endl;

		if (!cin)
	  	{
			cin.clear();
		  	while (cin.get() != '\n')
		  	{
		  		continue;
		  	}
		  	cout << "Error Bad input;\n";
		  	continue;
	  	}

	  	if (option < 0 || option > freedisklist_.size() - 1)
       	  	{
			cout << "Enter the proper option" << endl;
		  	continue;
	  	}

	  	if(find(options.begin(), options.end(), option) != options.end())
	  	{
			cout << "you have already select this option" << endl;
		  	continue;
	  	}

		options.push_back(option);
			
	  	result = result + freedisklist_[option] + " ";
		
	  	cout << "Do you want to add more disks to pool: Y or N" << endl;
	  	cin >> consent;

	  	if(!(consent == 'Y' || consent == 'y'))
	  	{
			break;
	  	}
	}

	//string cmd = "echo Ajay@123 | sudo -S zpool add " ;
	string cmd = "sudo pool add " ;
	cmd.append(poolmap_[pool_option]).append(" -f ");
	cmd.append(result);
//	cout << cmd.c_str();
   	FILE  *pipe = popen(cmd.c_str(), "r");
	if (!pipe)
        {
                cout << "popen error" << endl;
                return false;
        }

 	cout << endl;
        Get_list_of_disks_of_pools();
        free_disk_list();
	
	return true;
}


bool Zpool::Remove_disk_from_the_specified_disk_pool()
{
	int ret;
 	string cmd;
	int option = 0;
	int pool_option;
	string result = "";

	if(poolmap_.size() == 0)
	{
		cout << "No pool available" << endl;
		return true;
	}

	cout << endl;
        ret = List_disk_pools();
        if(!ret)
        {
        	cout << "List_disk_pools()" << endl;
                return false;
        }
        cout << endl;

        while(1)
        {
        	cout << "Enter the  option from which pool you need to remove the disk 0 to" << poolmap_.size() - 1 << endl;
                cin >> pool_option;
                if(!cin)
                {
                	cin.clear();
                        while(cin.get() != '\n');
                        cout << "Bad option" << endl;
                        continue;
                }

                if (pool_option < 0 || pool_option > poolmap_.size() - 1)
                {
                       cout << "Enter the proper option" << endl;
                       continue;
                }

                break;
         }

	 cout << endl;

	 if(diskmap_[poolmap_[pool_option]].size() <= 1)
	 {
		cout << "you can not remove disk from pool as there is only one disk is present in the pool" << endl << endl;
		return false;
	 }	

	 auto itr = diskmap_[poolmap_[pool_option]].begin();
         while(itr != diskmap_[poolmap_[pool_option]].end())
	 {
		cout << itr->first << ": " << itr->second << endl;
		itr++;
	 }

	 while(1)
         {
         	
 		cout << "Enter option for which you need to be remove the disk from 0 to " << diskmap_[poolmap_[pool_option]].size() - 1  << endl;
               	cin >> option;
		cout << endl;
       		if(!cin)
      		{
            		cin.clear();
               		while(cin.get() != '\n');
               		cout << "Bad option" << endl;
               		continue;
       		}

       		if (option < 0 || option >= (diskmap_[poolmap_[pool_option]].size()))
       		{
       			cout << "Enter the proper option" << endl;
               		continue;
       		}		
			
		break;
	}

		//cmd = "echo Ajay@123 | sudo -S zpool remove  ";
		cmd = "sudo zpool remove  ";
   		cmd.append(poolmap_[pool_option]).append(" ");
 	  	cmd.append(diskmap_[poolmap_[pool_option]][option]);
   //		cout << cmd.c_str();
	   	FILE *pipe = popen(cmd.c_str(), "r");
		if (!pipe)
        	{
                	cout << "popen error" << endl;
                	return false;
        	}
 
		cout << endl;
       		Get_list_of_disks_of_pools();
       		free_disk_list();
	
		return true;
}


bool Zpool::Get_list_of_disks_in_the_specified_disk_pool()
{
	int ret;
       	string cmd;
       	int option = 0;
	int pool_option;
        string result = "";

	if(poolmap_.size() == 0)
	{
		cout << "No pool available" << endl;
		return true;
	}

	cout << endl;
        ret = List_disk_pools();
        if(!ret)
        {

                cout << "List_disk_pools()" << endl;
                return false;
        }


        cout << endl;

        while(1)
        {
                cout << "Enter the  option from which pool you need to list/remove the disks 0 to  " << poolmap_.size() - 1 << endl;
                cin >> pool_option;
                if(!cin)
                {
			cin.clear();
                        while(cin.get() != '\n');
                        cout << "Bad option" << endl;
                        continue;
                }

                if (pool_option < 0 || pool_option > poolmap_.size() - 1)
                {
                        cout << "Enter the proper option" << endl;
                              continue;
                }

                break;
        }

        cout << endl;

        auto itr = diskmap_[poolmap_[pool_option]].begin();
        while(itr != diskmap_[poolmap_[pool_option]].end())
        {
		cout << itr->first << ": " << itr->second << endl;
                itr++;
        }

        cout << endl;

	return true;
}


bool Zpool::Destroy_pool()
{
	int ret;
        string cmd;
        int pool_option;



	if(poolmap_.size() == 0)
	{
		cout << "No pool available" << endl;
		return true;
	}

        ret = List_disk_pools();
        if(!ret)
        {
                cout << "List_disk_pools()" << endl;
                return false;
        }
	
	while(1)
        {
		cout << "Enter the  option which pool you need to destroy 0 to " << (int) poolmap_.size() - 1 << endl;
                cin >> pool_option;
                if(!cin)
                {
                       cin.clear();
                       while(cin.get() != '\n');
                       cout << "Bad option" << endl;
                       continue;
                 }

                 if (pool_option < 0 || pool_option > poolmap_.size() - 1)
                 {
                         cout << "Enter the proper option" << endl;
                         continue;
                 }

                        break;
         }

         //cmd = string(" echo Ajay@123 | sudo -S  zpool destroy ") +  poolmap_[pool_option] ;
         cmd = string("sudo zpool destroy ") +  poolmap_[pool_option] ;
	 FILE *pipe = popen(cmd.c_str(), "r");
 	 if (!pipe)
         {
                cout << "popen error" << endl;
                return false;
         }
	 
	// cout << cmd << endl;

	 cout << endl;
         zpool_list();
         Get_list_of_disks_of_pools();
         free_disk_list();
	 return true;
}



