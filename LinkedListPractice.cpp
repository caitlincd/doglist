//this program makes a list of dogs: name, breed, age
//it is organized by age from youngest to oldest

#include <iostream>
#include <string>

using namespace std;

//the struct represents each dog that can be put in the list
struct dog {
	string name;
	string breed;
	int age;
	dog * next;
};

//this class creates a list of dogs
class DogList {
private:
	dog * head;
public:
	DogList();
	void addDog(string name_, string breed_, int age_);
	void delDog(string &name, string &breed, int &age);
	void printList();
	void printBreed(string breed_);
	void printAge(int age_);
	~DogList();
};

DogList::DogList() {
	head = 0;
}

//add a dog, assigning the name, breed, and age of the dog
//it will be added behind younger dogs and in front of the other dogs with that same age if there are any
void DogList::addDog(string name_, string breed_, int age_) {
	if (head == 0) { //if list is empty, assign the head with parameters
		dog * newDog = new dog();
		newDog->name = name_;
		newDog->breed = breed_;
		newDog->age = age_;
		head = newDog;
	}
	else {
		dog * cu = head; //save head
		while (cu->next != 0) {
			if (cu->age < age_)
				cu = cu->next;
			else
				break;
		}

		dog * newDog = new dog; //create the new dog to be added in
		newDog->name = name_;
		newDog->breed = breed_;
		newDog->age = age_;
		newDog->next = cu->next; //make this new dog point to the dog that will be after it in the list
		cu->next = newDog; //make cu point to the new dog instead of the dog that is now after new dog


	}
}

//only the first instance of a dog with the exact name, breed, and age entered will be deleted
void DogList::delDog(string &name_, string &breed_, int &age_) {
	dog * cu = head;
	if (cu != 0) {
		//need to iterate through list and find correct dog
		while (cu->next != 0) {
			if (cu->next->name != name_ || (cu->next)->breed != breed_ || (cu->next)->age != age_)
				cu = cu->next;
			else
				break;
		}
		//if that dog is found
		if (cu->next != 0) {
			dog * temp = cu->next;
			cu->next = temp->next;
			delete temp;
		}
		else
			cout << "\nThis is not a dog in the list\n";	
	}
	else
		cout << "\nThis list is empty\n";
}

//prints the full list of dogs
void DogList::printList() {
	dog * cu = head;
	if (cu != 0) {
		while (cu != 0) {
			cout << "Name: " << cu->name << ", Breed: " << cu->breed << ", Age: " << cu->age << endl;
			cu = cu->next;
		}
	}
	else
		cout << "\nThis list is empty\n";
}

//prints only the dogs of the specified breed
void DogList::printBreed(string breed_) {
	dog * cu = head;
	if (cu == 0)
		cout << "\nThis list is empty\n";
	else {
		while (cu->breed != breed_ && cu != 0)
			cu = cu->next;
		if (cu->breed != breed_)
			cout << "\nThis breed is not in the list\n";
		else {
			cout << "Breed: " << breed_ << endl;
			while (cu->next != 0 && cu->breed == breed_) {
				cout << "Name: " << cu->name << ", Age: " << cu->age << endl;
				cu = cu->next;
			}
		}
	}
}

//prints only the dogs of the specified age
void DogList::printAge(int age_) {
	dog * cu = head;
	if (cu == 0) {
		cout << "\nThis list is empty\n";
	}
	else {
		while (cu->age != age_ && cu->next != 0)
			cu = cu->next;
		if (cu->age != age_)
			cout << "\nThis age is not in the list\n";
		else {
			cout << "Age: " << age_ << endl;
			while (cu != 0) {
				if (cu->age == age_) {
					cout << "Name: " << cu->name << ", Breed: " << cu->breed << endl;
					cu = cu->next;
				}
			}
		}
	}
}

DogList::~DogList()
{
	delete head;
}
		

int main()
{
	DogList myDogs;
	
	myDogs.addDog("Jack", "Westie", 7);
	myDogs.addDog("Pepper", "Black Lab", 13);
	myDogs.addDog("Rosie", "Mix", 5);
	myDogs.addDog("Charlie", "Mix", 6);
	myDogs.addDog("Toby", "Chocolate Lab", 13);

	cout << "\nFull list:\n";
	myDogs.printList();
	
	cout << "\nPrint age 13:\n";
	myDogs.printAge(13);

	cout << "\nPrint breed 'Mix':\n";
	myDogs.printBreed("Mix");
	
	string name = "Toby";
	string breed = "Chocolate Lab";
	int age = 13;
	cout << "\nTesting delete a dog:\n";
	cout << "Deleting Toby..................\n";
	myDogs.delDog(name, breed, age);
	myDogs.printList();

	return 0;
}
