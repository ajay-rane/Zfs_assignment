
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

static int a = 25;
class Zpool
{
	private:
		map<int, string> poolmap_;
	 	vector<string> diskslist_;
        	map<string, map<int, string> > diskmap_;
         	map<int, string> freedisklist_;
	
		map<int,string> zpool_list();
		map<int, string> free_disk_list();
	 	vector<string> disks_list();
         	map<string, map<int, string> >  Get_list_of_disks_of_pools();

	public:
		Zpool()
		{
			poolmap_ = zpool_list();
			diskslist_ = disks_list();
			diskmap_ = Get_list_of_disks_of_pools();
			freedisklist_ = free_disk_list();
		}

		bool  Create_disk_pool();
		bool List_disk_pools();
		bool Add_disks_to_pools();
		bool Remove_disk_from_the_specified_disk_pool();
		bool Get_list_of_disks_in_the_specified_disk_pool();
		bool Destroy_pool();
};

