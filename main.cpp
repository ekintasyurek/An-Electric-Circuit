/* @Author
Student Name: <Ekin Tasyurek>
Student ID : <150190108>
Date: <09.12.2020> */
#include <iostream>
#include <stdlib.h>
#include <fstream> 

using namespace std;

struct resistor
{
	char group;
	double value;
	int quantity;
	resistor* next;
};

struct grouplessResistor
{
	double value;
	int quantity;
	grouplessResistor* next;
};

struct Circuit
{
	resistor* head;
	void create();
	void add_resistor(char, double);
	int remove_resistor(char, double);
	void delete_resistor(char);
	void circuit_info();
	void clear();

};


void Circuit::create() //creating the circuit(resistor list)
{
	head = NULL;
}


char group;
double value;
int quantity;
resistor* next;

void Circuit::add_resistor(char group, double resistance_value)//adding a resistor to the circuit
{
	if (head == NULL)//if the circuit is empty, we fill the head resistor first
	{
		head = new resistor();
		head->group = group;
		head->value = resistance_value;
		head->quantity = 1;
		head->next = NULL;
	}
	else
	{
		resistor* current = head;
		bool already_exists = false;

		while (current != NULL)
		{
			if (current->group == group && ((current->value)+(resistance_value)!='0'))
			{
				if (current->value == resistance_value)
				{
					current->quantity++;
				}	
				else //if it's a negative value
				{
					remove_resistor(current->group, current->value);
				}
				already_exists = true;
				break;
			}

			current = current->next;
		}


		if (!already_exists)
		{
			resistor* temp1 = new resistor;
			temp1->group = group;
			temp1->value = resistance_value;
			temp1->quantity = 1;

			resistor* temp2 = head;
			resistor** temp3 = &head;
			while (temp2 != NULL && temp2->group < temp1->group)
			{
				temp3 = &temp2->next;
				temp2 = temp2->next;
			}
			*temp3 = temp1;
			temp1->next = temp2;
		}
	}

	
}

int Circuit::remove_resistor(char group, double value)//removing a resistor from the circuit
{
	resistor* current = head;
	while (current != NULL)
	{
		if (current->group == group && ((current->value)+(value)!='0'))
		{
			current->quantity--; 
			if (current->quantity == 0)
			{
				delete_resistor(group);
			}
			break;
		}
		current = current->next;
	}

	return 0;
}

void Circuit::delete_resistor(char)//deleting the resistor node from the circuit
{
	resistor* current = head;
	while (current != NULL)
	{
		if (current->group == group )
		{
			if (current->next == NULL)
			{
				current = NULL;
			}
			else
			{
				current->value = current->next->value;
				current->quantity = current->next->quantity;
				current->group = current->next->group;
				current->next = current->next->next;
			}
			break;
		}

		current = current->next;
	}

}


void Circuit::clear()//deleting all of the nodes of the list
{
    resistor *p;
    while (head){
        p = head;
        head = head->next;
        delete p;
    }
}


void Circuit::circuit_info()//printing resistor info and total resistance of the circuit
{
	grouplessResistor* new_list_head = new grouplessResistor;
	new_list_head->value = head->value; 
	new_list_head->quantity = head->quantity;
	new_list_head->next = NULL; 

	resistor* current = head;
	while(current->next != NULL)
	{
		bool value_already_exists = false;
		grouplessResistor* search_current = new_list_head;
		while (search_current != NULL)
		{
			if (search_current->value == current->next->value)
			{
				search_current->quantity++;
				value_already_exists = true;
				break;
			}

			search_current = search_current->next;
		}

		if (!value_already_exists)
		{
			grouplessResistor* temp1 = new grouplessResistor;
			temp1->value = current->next->value;
			temp1->quantity = current->next->quantity;
			temp1->next = NULL;

			grouplessResistor* temp2 = new_list_head;
			grouplessResistor** temp3 = &new_list_head;
			while (temp2 != NULL && temp2->value < temp1->value)
			{
				temp3 = &temp2->next;
				temp2 = temp2->next;
			}
			*temp3 = temp1;
			temp1->next = temp2;
		}
		
		current = current->next;
	}

	// printing resistor info

	grouplessResistor* search_current = new_list_head;
	while (search_current != NULL)
	{
		if (search_current->quantity < 0)
		{
			std::cout << "NO_RESISTOR" << std::endl;
		}
		search_current = search_current->next;
	}

	
	while (new_list_head != NULL)
	{
		if(new_list_head->quantity > 0)
		{
			std::cout << new_list_head->value << ":" << new_list_head->quantity << std::endl;
		}

		new_list_head = new_list_head->next;
	}


	// Calculating the total resistance and printing it
	double total_resistance = 0;

	resistor* temp = head;
	while (temp != NULL)
	{
		if (temp->quantity > 0)
		{
			total_resistance = total_resistance + (temp->value / temp->quantity);
		}

		temp = temp->next;
	}

	std::cout << "Total resistance=" << total_resistance << " ohm" << std::endl;
}

Circuit circuit;

int main(int argc, char* argv[])
{   
	circuit.create();

    char group;
	double resistance_value;

    std::ifstream infile("input.txt");
	while (infile >> group >> resistance_value)
	{
		if (group == 'A' && resistance_value == 0)
		{
			circuit.circuit_info();
		}
		else
		{
			circuit.add_resistor(group, resistance_value);
		}
	}

	return EXIT_SUCCESS;
}
