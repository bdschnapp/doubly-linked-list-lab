//Benjamin Schnapp 20748503
//chris starcevic 20776278

#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0);
		ASSERT_TRUE(manager.empty() == true);
		ASSERT_TRUE(manager.first == NULL);
		ASSERT_TRUE(manager.last == NULL);
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1);
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last);
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last);
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL);
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL);
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100));	
		return true;
	    
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager manager1;
		DronesManager::DroneRecord record1(5);
		for (int i = 1; i < 11; i++){
			manager1.insert_front(DronesManager::DroneRecord(i));
		}
		ASSERT_TRUE(manager1.select(5) == record1)
		ASSERT_FALSE(manager1.select(3) == record1)
		record1.droneID = 12;
		return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_front(DronesManager::DroneRecord(100));
		manager1.remove_front();
		manager2.remove_back();
		
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 0);
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 0);
		cout << 6 << endl;
		ASSERT_TRUE(manager1.empty() == manager2.empty());
		ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL);
		cout << 6 << endl;
	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager manager1;
		
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		
		ASSERT_TRUE(manager1.replace(0,(DronesManager::DroneRecord(300))));
		ASSERT_TRUE(manager1.replace(1,(DronesManager::DroneRecord(400))));
		ASSERT_TRUE(manager1.first->next->droneID == 400);
		ASSERT_TRUE(manager1.reverse_list());
	    return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		
		ASSERT_TRUE(manager1.get_size() == 2);
		ASSERT_TRUE((manager1.first != NULL) && (manager1.last !=NULL));
		ASSERT_TRUE((manager1.first->next == manager1.last) && (manager1.last->prev == manager1.first));
		ASSERT_TRUE((manager1.first->droneID == 200) && (manager1.last->droneID == 100));
		return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert(DronesManager::DroneRecord(300), 1);
		manager1.insert(DronesManager::DroneRecord(400), 2);
		
		ASSERT_TRUE(manager1.get_size() == 4);
		ASSERT_TRUE(manager1.first->droneID == 100);
		ASSERT_TRUE(manager1.select(2).droneID == 400);
	    return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.remove_back();
		
		ASSERT_FALSE(manager1.remove_front());
		ASSERT_FALSE(manager1.remove_back());
		ASSERT_FALSE(manager1.remove(3));
		
		manager1.insert_back(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(200));
		manager1.remove_back();
		
		ASSERT_TRUE(manager1.first == manager1.last && manager1.first->droneID == 100)
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager :: DroneRecord(300));
		manager1.insert(DronesManager :: DroneRecord(200), 2);
		
		ASSERT_FALSE(manager1.insert(DronesManager :: DroneRecord(200), 9));
		ASSERT_FALSE(manager1.remove(32));
		
		ASSERT_TRUE(manager1.insert_back(DronesManager :: DroneRecord(400)));
		ASSERT_TRUE(manager1.insert(DronesManager :: DroneRecord(500), 3));
		
		ASSERT_TRUE(manager1.remove(2));
		ASSERT_TRUE(manager1.remove_back());
		ASSERT_TRUE(manager1.remove_front());
		ASSERT_FALSE(manager1.empty());
		return true;
	}     
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
		DronesManager manager1;
		for(int i = 0; i < 20; i++){
			if(i%2 == 0){
				ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(i)));
			}
			else{
				ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(i)));
			}
		}
		manager1.print();
		cout << "Done with List1" << endl;
		ASSERT_TRUE(manager1.reverse_list());
		manager1.print();
		for(int i = 0; i < 20; i++){
			if(i%2 == 0){
				ASSERT_TRUE(manager1.remove_front());
			}
			else{
				ASSERT_TRUE(manager1.remove_back());
			}
		}
		ASSERT_TRUE(manager1.empty());
		return true;
	} 
};

#endif
