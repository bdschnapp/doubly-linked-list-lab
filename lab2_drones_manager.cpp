#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	int temp = size;
	for(int i = 0; i < temp; i++){
		this->remove_back();
	}
	delete first;
	delete last;
}


/*droneID(newDroneID), range(newRange), 
yearBought(newYearBought), droneType(newDroneType),
manufacturer(newManufacturer), description(newDescription), 
batteryType(newBatteryType)*/ 

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	if (lhs.droneID==rhs.droneID && lhs.range==rhs.range && lhs.yearBought==rhs.yearBought && lhs.droneType==rhs.droneType
	 && lhs.manufacturer==rhs.manufacturer && lhs.description==rhs.description && lhs.batteryType==rhs.batteryType){
		return true;
	}
	return false;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if (size != 0)
		return false;
	return true;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (!first)
		return DronesManager::DroneRecord(0);
	if(index >= size)
		return *last;
	DroneRecord* end = first;
	for(int i = 0; i < index; i++)
		end = end->next;
	return *end;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if(size == 0){
		return 0;
	}
	unsigned int count = 0;
	DroneRecord* val = first;
	while (val){
		if (*val == value){
			return count;
		}
		val = val->next;
		count ++;
	}
	return size;
}

void DronesManager::print() const {
	DroneRecord* temp = first;
	while(temp){
		std::cout<<temp->droneID<<std::endl;
		temp = temp->next;
	}
	return;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if(index > size)
		return false;
	if(index == 0){
		insert_front(value);
		return true;
	}
	if(index == size){
		insert_back(value);
		return true;
	}
	
	DroneRecord* new_value = new DroneRecord(value);
	DroneRecord* temp = first;
	for(int i = 0; i < index; i++){
		temp = temp->next;
	}
	new_value->next = temp;
	new_value->prev = temp->prev;
	temp->prev->next = new_value;
	temp->prev = new_value;
	size++;
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	if(!first){
		last = first = new DroneRecord(value);
		size++;
		return true;
	}
	DroneRecord* new_value = new DroneRecord(value);
	new_value->next = first;
	first->prev = new_value;
	first = new_value;
	size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	if(!first){
		first = last = new DroneRecord(value);
		size++;
		return true;
	}
	DroneRecord* new_value = new DroneRecord(value);
	new_value->prev = last;
	last->next = new_value;
	last = new_value;
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	if(index > size - 1 || size == 0)
		return false;
	if(size - 1 == index)
		remove_back();
	if(size == 1)
		remove_front();
	else{
		DroneRecord *trash = new DroneRecord(*first);
		for(int i = 0; i  < index; i++){
			trash = trash->next;
		}
		trash->prev->next = trash->next;
		trash->next->prev = trash->prev;
		size--;
		delete trash;
		return true;
	}
	
}

bool DronesManager::remove_front() {
	if(size == 0)
		return false;
	if(size == 1){
		delete first;
		first = NULL;
		last = NULL;
	}
	else {
		first = first->next;
		delete first->prev;
		first->prev = NULL;
	}
	size--;
	return true;
}

bool DronesManager::remove_back() {
	if (size == 0)
		return false;
	if(size == 1){
		delete first;
		first = NULL;
		last = NULL;
	}
	else{
		last = last->prev;
		delete last->next;
		last->next = NULL;
	}
	size--;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value){
	if(index > size - 1)
		return false;
	DroneRecord *trash = first;
	for(int i = 0; i < index; i++){
		trash = trash->next;
	}
	trash->droneID = value.droneID;
	return true;
}

bool DronesManager::reverse_list() {
	if(size == 0)
		return true;
	DronesManager other;
	for (int i = size; i > 0; i--){
		other.insert_back(this->select(i));
		this->remove_back();
	}
	this->first = other.first;
	this->last = other.last;
	other.first = NULL;
	other.last = NULL;
	size = other.size;
	other.size = 0;
	return true;
}

