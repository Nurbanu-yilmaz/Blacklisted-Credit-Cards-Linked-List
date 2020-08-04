#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


struct node
{
	int month, year;
	vector<string> cards;
	node* next;

	node(){
		month = 0;
		year = 0;
		next = nullptr;
	}
};

void selectionSort(node* head) 			  
{ 
	node* temp = head; 

	while (temp) { 
		node* min = temp; 
		node* r = temp->next; 

		while (r) { 
			if (min->year > r->year) 
				min = r;
			else if(min->year == r->year && min->month > r->month){
				min = r;
			}

			r = r->next; 
		} 

		vector<string> productname = temp->cards; 
		temp->cards = min->cards; 
		min->cards = productname;

		int month = temp->month; 
		temp->month = min->month; 
		min->month = month;

		int year = temp->year; 
		temp->year = min->year; 
		min->year = year;

		temp = temp->next; 
	} 
}

void selectionSortMonth(node* head) 		{
	

	node* temp = head; 

	while (temp) { 
		node* min = temp; 
		node* r = temp->next; 
 
		while (r) { 
			if (min->month > r->month) 
				min = r; 

			r = r->next; 
		} 

		
		vector<string> productname = temp->cards; 
		temp->cards = min->cards; 
		min->cards = productname;

		int month = temp->month; 
		temp->month = min->month; 
		min->month = month;

		int year = temp->year; 
		temp->year = min->year; 
		min->year = year;

		temp = temp->next; 
	} 
}


node* MonthandYearExists(node*head, int card_month, int card_year){
	node*temp = head;
	while(temp != nullptr){
		if(temp->month == card_month && temp->year == card_year){
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

node* cardNumExists(node*head, string card_num){
	node*temp = head;
	while(temp != nullptr){
		int size = 	temp->cards.size();

		for (int i = 0; i < size; i++)
		{
			if(temp->cards[i] == card_num){
				return temp;
			}
		}

		temp = temp->next;
	}
	return nullptr;
}

void addCard(node *&head,  string card_num, int card_month, int card_year){
	
	if(card_month>0 && card_year>0){
		node* newNode = new node();
		newNode->cards.push_back(card_num);
		newNode->month = card_month;
		newNode->year = card_year;
		newNode->next = nullptr;

		if(head == nullptr){						
			head = newNode;
		}
		else{										
			node* current = head;
			while(current->next != nullptr){
				current = current->next;
			}
			current->next = newNode;
		}
	}




}

void add_card(node*& head, string card_num, int card_month, int card_year){
	
	node* temp = head;
	node* exists = MonthandYearExists(head, card_month, card_year);					

	if(exists){													 
		exists->cards.push_back(card_num);
		cout << "***************" << endl;
		cout << "Node with expiration date " << card_month << " " << card_year << " already exists" << endl;
		cout << "Credit card " << card_num << "added to node " << card_month << " " <<  card_year << endl;
	}
	else{														
		addCard(head, card_num, card_month, card_year);
		cout << "***************" << endl;
		cout << "New node is created with expiration date: " << card_month <<" " <<  card_year << endl; 
		cout << "Credit card " << card_num << "added to node " << card_month << " " <<card_year << endl;
		selectionSort(head);
		
	}
}

bool isNumber(string s) 
{ 
	for (int i = 0; i < s.length(); i++) 
		if (isdigit(s[i]) == false) 
			return false; 

	return true; 
}

void displayAllCards(node * head){
	node * temp = head;

	if(head == nullptr)	{
		cout << "List is Empty" << endl << endl;
		return;
	}
	while(temp != nullptr){
		cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
		int size = 	temp->cards.size();
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << ")  " << temp->cards[i] << endl;
		}
		temp = temp->next;
		cout << "----------------------" << endl << endl;
	}
}

void search(node * head){
	string card_number;

	cout << "Please enter the credit card number: ";
	cin >> card_number;

	while(card_number.length() != 16)
	{
		cout << "Invalid format!" << endl;
		cout << "Please enter the credit card number: ";
		cin >> card_number;
	}

	node * exists = cardNumExists(head, card_number);
	if(exists){
		cout << "There exists a credit card given number "<< card_number << " with expiration date: " << exists->month << " " << exists->year << endl; 
	}
	else{
		cout << "There is no credit card with given credit card number: " << card_number << endl;
	}

}

void deleteNode(node*&head, node*& toBeDeleted){					   
	

	node * ptr = nullptr;
	if (toBeDeleted == head) { 
		head = head->next;
		delete toBeDeleted;
		return;
	} else {  
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
		return;
	}
}


void deleteCard(node * head){
	int month;
	string year;
	cout << "Please enter month and year: ";
	cin >> month >> year;

	while(month > 12 || month < 0 || !isNumber(year)){
		cout << "Invalid Date!" << endl;
		cout << "Please enter month and year: ";
		cin >> month >> year;
	}
	int int_year = stoi(year);

	node * exists  = MonthandYearExists(head, month, int_year);

	if(exists){
		cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
		int size = 	exists->cards.size();
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << ")  " << exists->cards[i] << endl;
		}
		cout << endl << endl;
		deleteNode(head, exists);

	}

	else{
		cout << "There is no node with expiration date " << month << " " << year<< ", nothing deleted!"<< endl;
	}
}

int main()
{    
	string filename;
	ifstream input;
	string line;
	int x=1;
	node * head = nullptr;
	while (x==1)
	{
		string card_num;

		int card_month, card_year;
		cout << "Please enter file name: ";
		cin >> filename;
		input.open(filename);

		if(input.fail())
		{

			cout<< "Cannot find a file named "<< filename << endl;

		}
		if (!input.fail())
		{
			x = 0;

			while(!input.eof())
			{
				getline ( input,line);
				istringstream iss(line);
				iss >> card_num >> card_month >> card_year;
				add_card(head, card_num, card_month, card_year);

			}
		}
	}
	int input_operation;
	cout << "1)Display List" << endl;
	cout << "2)Card Search via Credit Number" << endl;
	cout << "3)Delete Card with respect to Expiration Date" << endl;
	cout << "4)Exit" << endl;	cout << "Please choose option from the menu: ";	cin >> input_operation;	while(input_operation!= 4){		if(input_operation == 1){			displayAllCards(head);		}		if(input_operation == 2){			search(head);		}		if(input_operation == 3){			deleteCard(head);		}		if(input_operation == 4){			break;		}		cout << "1)Display List" << endl;
		cout << "2)Card Search via Credit Number" << endl;
		cout << "3)Delete Card with respect to Expiration Date" << endl;
		cout << "4)Exit" << endl;		cout << "Please choose option from the menu: ";		cin >> input_operation;	}

	return 0;
}