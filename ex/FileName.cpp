#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

class Human{
	string name;
	string last_name;
	int age;
	bool gender;
	bool married = false;

public:
	static int persons;
	
	bool passport = false;

	Human(){
		name = " ";
		last_name = " ";
		age = 0;
		persons++;
	}
	Human(string name) {
		this->name = name;
		persons++;
	}
	Human(string name, string last_name) : Human(name) {
		this->last_name = last_name;
	}
	Human(string name, string last_name, int age) : Human(name, last_name) {
		this->age = age;
	}
	
	Human(string name, string last_name, int age, bool passport) : Human(name, last_name, age) {
		if (age >= 18) 
		{
			passport = true;
		}
		else 
		{
			passport = false;
		}
	}
	Human(string name, string last_name, int age, bool passport, bool gender) : Human(name, last_name, age, passport) {
		this->gender = gender;
	}

	string GetName() { return name; }
	string GetLastName() { return last_name; }
	int GetAge() { return age; }
	bool GetPassport() { return passport; }
	bool GetGender() { return gender; }
	bool GetMarried() { return married; }

	void SetName(string name) { this->name = name; }
	void SetLastName(string last_name) { this->last_name = last_name; }
	void SetAge(int age) { this->age = age; }
	void SetMarried(bool tr) { married = true; }

	void Copy(Human* obj) {
		this->age = obj->GetAge();
		this->last_name = obj->GetLastName();
		this->name = obj->name;
	}
	void Move(Human* obj) {
		this->age = obj->GetAge();
		this->last_name = obj->GetLastName();
		this->name = obj->name;

		delete[] this;
	}
	void Birthday() {
		this->age += 1;
	}

	void Passport() {
		passport = true;
	}
};

int Human::persons = 0;

ostream& operator<< (ostream& os, Human obj) {
	cout << "Name: " << obj.GetName() << endl;
	cout << "Last Name: " << obj.GetLastName() << endl;
	cout << "Age: " << obj.GetAge() << endl;

	if (obj.GetPassport() == false) {
		cout << "Passport: Not passport" << endl;
	}
	else {
		cout << "Passport: Passport" << endl;
	}
	
	if (obj.GetGender() == false) {
		cout << "Gender: Man" << endl;
	}
	else {
		cout << "Gender: Women" << endl;
	}
	
	if (obj.GetMarried() == false) {
		cout << "Marriege: Not married" << endl;
	}
	else {
		cout << "Marriege: Married" << endl;
	}

	return os;
}

istream& operator>>(istream& is, Human obj) {
	string name;
	cout << "Enter name: ";
	cin >> name;
	obj.SetName(name);

	string last_name;
	cout << "Enter last name: ";
	cin >> last_name;
	obj.SetLastName(last_name);

	int age;
	cout << "Enter age: ";
	cin >> age;
	obj.SetAge(age);

	bool marr;
	cout << "Enter your marry(1 - married; 2 - not married): ";
	cin >> marr;
	obj.SetMarried(marr);

	return is;
}

void PassportHuman(Human* human) {
	if (human->GetAge() >= 18) {
		human->passport = true;
		cout << endl << "....." << human->GetName() <<  " got a passport....." << endl;
	} 
	else {
		human->passport = false;
		cout << endl << "....." << human->GetName() << " too young....." << endl;
	}
}

void Mariage(Human* m, Human* wm) {
	if (m->GetGender() != wm->GetGender()) {
		if (m->GetMarried() != true && wm->GetMarried() != true) {
			m->SetMarried(true);
			wm->SetMarried(true);

			cout << "......" << m->GetName() << " married on " << wm->GetName() << "......" << endl;
		}
		else {
			cout << ".......some of them are already married........" << endl;
		}
	}
	else {
		cout << ".......same-gender marriage prohibited!........" << endl;
	}
}

int RandomAge() {
	return 14 + rand() % 5;
}

int main() {
	srand(time(0));

	vector<Human*> family;

	Human* ivan = new Human("Ivan", "Mlanarskiy", RandomAge(), false, false);
	Human* kostya = new Human("Kostya", "Kysnecov", RandomAge(), false, false);
	Human* nadia = new Human("Nadia", "Robosh", RandomAge(), false, true);

	family.push_back(ivan);
	family.push_back(kostya);
	family.push_back(nadia);

	for (int i = 0; i < Human::persons; i++) {
		cout << *family[i] << endl;
	}

	sort(family.begin(), family.end(), [](Human* obj1, Human* obj2) {
		return obj1->GetAge() < obj2->GetAge();
	});

	nadia->Birthday();
	PassportHuman(nadia);
	Mariage(kostya, nadia);

	for (int i = 0; i < Human::persons; i++) {
		cout << *family[i] << endl;
	}

}