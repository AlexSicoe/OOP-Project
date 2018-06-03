#include <iostream>
#include <fstream>
#include <vector>
//#include <list>
#include <string>
#include <map>
#include <ctime>




using namespace std;

enum TypeOfExpenditure {
	Food = 0,
	Clothing = 1,
	PC = 2,
	ConsumerProduct = 3,
	Car = 4,
	Rent = 5,
	House = 6,
	Land = 7,
	Medicine = 8,
	Service = 9,
	Other = 10
};

ostream& operator<< (ostream& out, const TypeOfExpenditure value)
{
	static map<TypeOfExpenditure, string> strings;
	if (strings.size() == 0) {
		#define INSERT_ELEMENT(p) strings[p] = #p
				INSERT_ELEMENT(Food);
				INSERT_ELEMENT(Clothing);
				INSERT_ELEMENT(PC);
				INSERT_ELEMENT(ConsumerProduct);
				INSERT_ELEMENT(Car);
				INSERT_ELEMENT(Rent);
				INSERT_ELEMENT(House);
				INSERT_ELEMENT(Land);
				INSERT_ELEMENT(Medicine);
				INSERT_ELEMENT(Service);
				INSERT_ELEMENT(Other);
		#undef INSERT_ELEMENT
	}

	return out << strings[value];
}

class Expenditure
{
private:
	//const int expId;
	//static int ID_COUNTER;
	char* expName;
	float cost;
	struct tm* date;
	TypeOfExpenditure type;
	bool paid;
	

public:
	Expenditure(char* ExpName, float ExpCost, struct tm* ExpDate, TypeOfExpenditure ExpType, bool Paid) //:expId(ID_COUNTER++)
	{
		
		expName = new char [strlen(ExpName) + 1];
		strcpy(expName, ExpName);
		
		if (ExpCost >= 0) {
			cost = ExpCost;
		}
		else { throw exception("The cost must be positive!"); }

		#pragma region expDate
				date = new struct tm[sizeof(ExpDate)];
				date->tm_hour = ExpDate->tm_hour;
				date->tm_isdst = ExpDate->tm_isdst;
				date->tm_mday = ExpDate->tm_mday;
				date->tm_min = ExpDate->tm_min;
				date->tm_mon = ExpDate->tm_mon;
				date->tm_sec = ExpDate->tm_sec;
				date->tm_wday = ExpDate->tm_wday;
				date->tm_yday = ExpDate->tm_yday;
				date->tm_year = ExpDate->tm_year;
		#pragma endregion

		type = ExpType;
		paid = Paid; //true if paid	
	}

	
	~Expenditure()
	{
		delete [] expName;
		delete [] date;
	}

	
	Expenditure(const Expenditure& existing) // :expId(ID_COUNTER++)
	{		
		expName = new char[strlen(existing.expName) + 1];
		strcpy(expName, existing.expName);
		cost = existing.cost;

		#pragma region expDate
				date = new struct tm[sizeof(existing.date)];
				date->tm_hour = existing.date->tm_hour;
				date->tm_isdst = existing.date->tm_isdst;
				date->tm_mday = existing.date->tm_mday;
				date->tm_min = existing.date->tm_min;
				date->tm_mon = existing.date->tm_mon;
				date->tm_sec = existing.date->tm_sec;
				date->tm_wday = existing.date->tm_wday;
				date->tm_yday = existing.date->tm_yday;
				date->tm_year = existing.date->tm_year;
		#pragma endregion

		type = existing.type;
		paid = existing.paid;
	}
	

	char* displayPaid()
	{
		if (this->paid == true)
			return "Yes";
		else
			return "No";
	}

	void displayExpenditure()
	{
		cout << "///Expenditure///"
			//<< endl << "  ID: " << this->id
			<< endl << "Name: " << this->expName
			<< endl << "Type: " << this->type
			<< endl << "Cost: $" << this->cost
			<< endl << "Date: " << asctime(this->date)
			<< "Paid: " << displayPaid()
			<< endl << endl;
	}
	
	void writeToFile(ofstream& file) {
		if (file.is_open()) {
			file.write(this->expName, sizeof(Expenditure::expName));
			file.write((char*)&this->cost, sizeof(this->cost));
			file.write((char*)&this->date, sizeof(this->date));
			file.write((char*)&this->type, sizeof(this->type));
			file.write((char*)&this->paid, sizeof(this->paid));
		}
		else 
			throw exception();
	}

	char* getExpName()
	{
		return this->expName;
	}
	TypeOfExpenditure getType()
	{
		return this->type;
	}
	float getCost()
	{
		return this->cost;
	}
	struct tm* getDate()
	{
		return this->date;
	}
	bool getPaid()
	{
		return this->paid;
	}
	/*int getId(){
		return this->id;
	}*/

	void setExpName(char* newExpName)
	{
		if (this->expName != NULL)
		{
			delete [] expName;//
		}

		this->expName = new char[strlen(newExpName) + 1];
		strcpy(this->expName, newExpName);
	}
	void setType(TypeOfExpenditure newType)
	{
		type = newType;
	}
	void setCost(float newCost)
	{
		if (newCost >= 0)
			cost = newCost;
		else
			throw exception("Cost must be positive");
	}
	void setDate(struct tm* newDate)
	{
		if (date != NULL) {
		delete[]date;
		}

		date = new struct tm[sizeof(newDate)]; //vezi si in celelalte parti daca n-ai facut shallow copy
		date->tm_hour = newDate->tm_hour;
		date->tm_isdst = newDate->tm_isdst;
		date->tm_mday = newDate->tm_mday;
		date->tm_min = newDate->tm_min;
		date->tm_mon = newDate->tm_mon;
		date->tm_sec = newDate->tm_sec;
		date->tm_wday = newDate->tm_wday;
		date->tm_yday = newDate->tm_yday;
		date->tm_year = newDate->tm_year;
	}
	void setPaid(bool newPaid)
	{
		this->paid = newPaid;
	}
	void setPaidString(char* newPaid)
	{
		if (_strcmpi(newPaid, "YES") == 0 || _strcmpi(newPaid, "Y") == 0 || strcmp(newPaid, "1") == 0) {
			this->paid = true;
		}
		else {
			if (_strcmpi(newPaid, "NO") == 0 || _strcmpi(newPaid, "N") == 0 || strcmp(newPaid, "0") == 0) {
				this->paid = false;
			}
			else
				throw exception("Exception: Type either Yes or No");
		}
	}

	/*
	int setId()
	{
		return ID_COUNTER++;
		//TODO: id corect cand incarc fisier
	} 
	*/




	//friend ostream& operator<< (ostream& out, Expenditure exp);
	//friend istream& operator>> (istream& console, Expenditure &exp);

	Expenditure operator++ (int) {
		Expenditure copie = *this;
		this->cost++;
		return copie;
	}

	void operator! () {
		if (this->paid == true)
			this->paid = false;
		else
			this->paid = true;
	}

};

//int Expenditure::ID_COUNTER = 1;

ostream &operator<< (ostream &out, Expenditure exp)
{
	out << "///Expenditure///"
		<< endl << "Name: " << exp.getExpName()
		<< endl << "Type: " << exp.getType()
		<< endl << "Cost: $" << exp.getCost()
		<< endl << "Date: " << asctime(exp.getDate())
		<< "Paid: " << exp.displayPaid()
		<< endl << endl;

	return out;
}

istream &operator>> (istream &console, Expenditure &exp)
{
	cout << "Inserting a new expenditure..." << endl;
	cout << "Expenditure Name: ";
	char buffer[100];
	console >> buffer;
	exp.setExpName(buffer);
	
	cout << endl;
	for (int i = 0; i <= 10; i++)
	{
		cout << i + 1 << ". " << (TypeOfExpenditure)i << endl;
	}
	cout << endl << "Choose a type: ";
	int type;
	console >> type;
	exp.setType((TypeOfExpenditure) (type - 1));

	cout << "Cost: $";
	float cost;
	console >> cost;
	exp.setCost(cost);

	//setting todays date
	struct tm* data;
	time_t rawtime;
	time(&rawtime);
	data = localtime(&rawtime);
	exp.setDate(data);

	cout << "Have you paid this expenditure? 1 = Yes, 0 = No" << endl;
	char paid[5];
	console >> paid;
	exp.setPaidString(paid);

	return console;
}
	


class BankAccount
{
private:
	float cash;
	float debit;
	float credit;
	float creditRate;
	float savings;
	float savingsRate;

public:
	BankAccount(float Cash, float Debit, float Credit, float CreditRate, float Savings, float SavingsRate)
	{
		cash = Cash;
		debit = Debit;
		credit = Credit;
		creditRate = CreditRate;
		savings = Savings;
		savingsRate = SavingsRate;
	}

	~BankAccount()
	{

	}

	BankAccount(BankAccount &acc)
	{
		cash = acc.cash;
		debit = acc.debit;
		credit = acc.credit;
		creditRate = acc.creditRate;
		savings = acc.savings;
		savingsRate = acc.savingsRate;
	}

	void displayAccount()
	{
		cout << "///Account///"
			<< endl << "Cash: $" << cash
			<< endl << "Debit: $" << debit
			<< endl << "Credit: $" << credit
			<< "	Rate: " << creditRate*100 << "% per month"
			<< endl << "Savings: $" << savings
			<< "	Rate: " << savingsRate*100 << "% per month"
			<< endl << endl;
	}


	void modifyAccount(){
		cout << "Modifying bank account...";
		cout << endl << "Cash: $";
		float buffer;
		cin >> buffer;
		this->setCash(buffer);

		cout << "Debit: $";
		cin >> buffer;
		this->setDebit(buffer);

		cout << "Credit: $";
		cin >> buffer;
		this->setCredit(buffer);

		cout << "Credit Rate (between 0 and 1): ";
		cin >> buffer;
		this->setCreditRate(buffer);

		cout << "Savings: $";
		cin >> buffer;
		this->setSavings(buffer);

		cout << "Savings Rate (between 0 and 1): ";
		cin >> buffer;
		this->setSavingsRate(buffer);

		cout << endl;
	}


	///////////
	void PayCash(Expenditure exp) //TO DO: fara valori negative //costul cheltuielii
	{
		try
		{
			if (cash - exp.getCost() < 0)
				throw exception("Can't buy, too little cash");
			else
				cash = cash - exp.getCost();
		}
		catch (exception e)
		{
			//ToDo: PayDebit() / Credit
		}
	}

	void writeToFile(ofstream &file)
	{
		if (file.is_open()) {
			file.write((char*)&this->cash, sizeof(float));
			file.write((char*)&this->debit, sizeof(float));
			file.write((char*)&this->credit, sizeof(float));
			file.write((char*)&this->creditRate, sizeof(float));
			file.write((char*)&this->savings, sizeof(float));
			file.write((char*)&this->savingsRate, sizeof(float));
		}
		else
			throw exception();
	}

	void generateReport(char* reportName) {
		cout << endl << "Generating bank account report..." << endl << endl;
		ofstream report;
		report.open(reportName, ios::out | ios::trunc);
		if (report.is_open()) {
			//report << "///Account///\n";
			report << *this;
		}
		report.close();
	}

	///////////
	void setCash(float Cash)
	{
		if (Cash >= 0)
			cash = Cash; 
		else
			throw exception("Cash must be bigger or equal to 0");
	}
	void setDebit(float Debit)
	{
		if (Debit >= 0)
			debit = Debit;
		else
			throw exception("Debit must be bigger or equal to 0");
	}
	void setCredit(float Credit)
	{
		if (Credit >= 0)
			credit = Credit;
		else
			throw exception("Credit must be bigger or equal to 0");
	}
	void setCreditRate(float CreditRate)
	{
		if (CreditRate >= 0 && CreditRate <= 1)
			creditRate = CreditRate; 
		else
			throw exception("Credit Rate must be between 0 and 1");
	}
	void setSavings(float Savings)
	{
		if (Savings >= 0)
			savings = Savings; 
		else
			throw exception("Savings must be bigger or equal to 0");
	}
	void setSavingsRate(float SavingsRate)
	{
		if (SavingsRate >= 0 && SavingsRate <= 1)
			savingsRate = SavingsRate;
		else	
			throw exception("Savings Rate must be between 0 and 1");
	}

	float getCash()
	{
		return cash;
	}
	float getDebit()
	{
		return debit;
	}
	float getCredit()
	{
		return credit;
	}
	float getCreditRate()
	{
		return creditRate;
	}
	float getSavings()
	{
		return savings;
	}
	float getSavingsRate()
	{
		return savingsRate;
	}
	
	BankAccount operator++ () {
		this->cash += 10000;
		
		return *this;
	}

	bool operator == (BankAccount acc) {
		if (this->cash + this->debit + this->savings == acc.cash + acc.debit + acc.savings)
		{
			return true;
		}
		else 
			return false;
	}

	friend ostream& operator<< (ostream& out, BankAccount acc);
};

istream& operator>> (istream& input, BankAccount& acc)
{
	cout << "Inserting bank account...";
	cout << endl << "Cash: $";
	float buffer;
	input >> buffer;
	acc.setCash(buffer);

	cout << "Debit: $";
	input >> buffer;
	acc.setDebit(buffer);

	cout << "Credit: $";
	input >> buffer;
	acc.setCredit(buffer);

	cout << "Credit Rate (between 0 and 1): ";
	input >> buffer;
	acc.setCreditRate(buffer);

	cout << "Savings: $";
	input >> buffer;
	acc.setSavings(buffer);

	cout << "Savings Rate (between 0 and 1): ";
	input >> buffer;
	acc.setSavingsRate(buffer);
	
	cout << endl;

	return input;
}

ostream& operator<< (ostream& out, BankAccount acc) {
	out << "///Account///"
		<< endl << "Cash: $" << acc.getCash()
		<< endl << "Debit: $" << acc.getDebit()
		<< endl << "Credit: $" << acc.getCredit()
		<< "	Rate: " << acc.getCreditRate() * 100 << "% per month"
		<< endl << "Savings: $" << acc.getSavings()
		<< "	Rate: " << acc.getSavingsRate() * 100 << "% per month"
		<< endl << endl;

	return out;
}

class User
{
private:
	char* username;
	char* password;
	vector<Expenditure> expenditures;
	//Expenditure* expenditures;
	BankAccount* account;

public:
	User(char* Username, char* Password, vector<Expenditure> Expenditures,
		BankAccount* NewAccount)
	{
		username = new char[strlen(Username) + 1];
		strcpy(username, Username);

		password = new char[strlen(Password) + 1];
		strcpy(password, Password);

		expenditures = Expenditures;

		account = NewAccount;
	}


	~User() //////////
	{

	}

	User(User& u)
	{
		//delete[]username;
		username = new char[strlen(u.username) + 1];
		strcpy(username, u.username);

		password = new char[strlen(u.password) + 1];
		strcpy(password, u.password);

		this->account = u.account; ////////
		this->expenditures = u.expenditures; ////////
	}

	void setUsername(char* Username)
	{
		delete[]username;
		username = new char[strlen(Username) + 1];
		strcpy(username, Username);
	}
	void setPassword(char* Password)
	{
		delete[]password;
		password = new char[strlen(Password) + 1];
		strcpy(password, Password);
	}
	void setExpenditure(vector<Expenditure> newExpenditures)
	{
		expenditures = newExpenditures; ////
	}
	void setAccounts(BankAccount* newAccount)
	{
		account = newAccount; ////
	}

	char* getUsername()
	{
		return username;
	}
	char* getPassword()
	{
		return password;
	}
	vector<Expenditure> getExpenditures()
	{
		return expenditures;
	}
	BankAccount* getAccount()
	{
		return account;
	}

	/*
	int getNumberOfExpenditures()
	{
		int noOfElements = sizeof(expenditures) / sizeof(expenditures[0]);
		return noOfElements;
	}
	*/

	void displayAllExpenditures()
	{
		for (int i = 0; i < this->expenditures.size(); i++)
		{
			cout << "#" << i + 1;
			expenditures.at(i).displayExpenditure();
		}
	}

	

	void displayUser()
	{
		cout << endl << "Username: " << this->username << endl;
		cout << "Number of expenditures: " << this->expenditures.size() << endl << endl;
		
	}

	void addExpenditure() {
		
		time_t rawtime;
		time(&rawtime);
		struct tm* acum;
		acum = localtime(&rawtime);
		

		Expenditure myExp ("0", 0, acum, (TypeOfExpenditure)0, false);
		cin >> myExp;

		expenditures.push_back(myExp);
	}

	void deleteExpenditure() {

		cout << "Deleting...";
		expenditures.pop_back();
		/*
		cout << "Delete expenditure with number #";
		unsigned number;
		cin >> number;
		cout << "Deleting #" << number << "... " << endl;

		number--;
		*/

		//expenditures.at(number);
		//iter_swap(expenditures.begin() + number, expenditures.begin() + expenditures.size() - 1);
		//expenditures.pop_back();
		//iter_swap(expenditures.begin() + number, expenditures.end());
		//expenditures.pop_back();
		
		//vector<Expenditure>::iterator it =
		//expenditures.erase(expenditures.begin() + number);
		

		/*
		list <Expenditure> lista;
		for (int i = expenditures.size() - 1; i >= 0; i--)
		{
			lista.push_back(expenditures.at(i));
			expenditures.pop_back();
		}

		lista.erase(lista.begin + number);

		for (int i = 0; i < lista.size(); i++)
		{
			expenditures.push_back(lista.begin + i);
		}
		*/

		
		

		//expenditures.

		//list<Expenditure> lista;



	}

	void displayUserMenu()
	{
		this->displayUser();

		cout << "Menu" << endl;
		cout << "1. See bank account" << endl;
		cout << "2. Modify bank account" << endl;
		cout << "3. See expenditures" << endl;
		cout << "4. Make a new expenditure" << endl; 
		cout << "5. Delete last expenditure" << endl;
		cout << "6. Generate user report" << endl;
		cout << "7. Generate bank account report" << endl;
		cout << "8. Generate report for all expenditures" << endl << endl;

		unsigned choice;
		cin >> choice;

		switch (choice) {
		case 1: this->account->displayAccount();
			break;
		case 2: this->account->modifyAccount();
			break;
		case 3: this->displayAllExpenditures();
			break;
		case 4: this->addExpenditure();
			break; 
		case 5: this->deleteExpenditure();
			break;
		case 6: this->generateReport("UserReport.txt");
			break;
		case 7: this->account->generateReport("BankAccountReport.txt");
			break;
		case 8: this->generateAllExpendituresReport("AllExpendituresReport.txt");
			break;
		}


		displayUserMenu();

	}

	void saveData(char* fileName) {
		ofstream file;
		file.open(fileName, ios::out | ios::trunc | ios::binary);
		if (file.is_open()) {
			file.write(this->username, sizeof(User::username));
			file.write(this->password, sizeof(User::password)); //TODO: nu-i prea safe
			
			this->account->writeToFile(file);
			int size = expenditures.size(); //TODO: check
			file.write((char*)&size, sizeof(size));
			
			for (int i = 0; i < expenditures.size(); i++) {
				this->expenditures[i].writeToFile(file);
			}
			
		}
		file.close();
	}

	void loadData(char* fileName) {
		ifstream inputFile;
		inputFile.open(fileName, ios::in | ios::binary);
		if (inputFile.is_open()) {
			char buffer[50];
			int noOfExpenditures;
			float fBuffer;

			//TODO: check
			inputFile.read(buffer, sizeof(buffer));
			//setUsername(buffer);
			inputFile.read(buffer, sizeof(buffer)); //same
			//setPassword(buffer);

			inputFile.read((char*)&fBuffer, sizeof(float));
			this->account->setCash(fBuffer);
			inputFile.read((char*)&fBuffer, sizeof(float));
			this->account->setDebit(fBuffer);
			inputFile.read((char*)&fBuffer, sizeof(float));
			this->account->setCredit(fBuffer);
			inputFile.read((char*)&fBuffer, sizeof(float));
			this->account->setCreditRate(fBuffer);
			inputFile.read((char*)&fBuffer, sizeof(float));
			this->account->setSavings(fBuffer);
			inputFile.read((char*)&fBuffer, sizeof(float));
			this->account->setSavingsRate(fBuffer);

			/*
			inputFile.read((char*)&buffer, sizeof(buffer));
			fBuffer = atof(buffer);
			this->account->setCash(fBuffer);

			inputFile.read((char*)&buffer, sizeof(buffer));
			fBuffer = atof(buffer);
			this->account->setDebit(fBuffer);

			inputFile.read((char*)&buffer, sizeof(buffer));
			fBuffer = atof(buffer);
			this->account->setCredit(fBuffer);

			inputFile.read((char*)&buffer, sizeof(buffer));
			fBuffer = atof(buffer);
			this->account->setCreditRate(fBuffer);

			inputFile.read((char*)&buffer, sizeof(buffer));
			fBuffer = atof(buffer);
			this->account->setSavings(fBuffer);

			inputFile.read((char*)&buffer, sizeof(buffer));
			fBuffer = atof(buffer);
			this->account->setSavingsRate(fBuffer);
			*/

			inputFile.read((char*)&noOfExpenditures, sizeof(int));
			this->expenditures.clear(); //TODO: check
			for (int i = 0; i < noOfExpenditures; i++)
			{
				struct tm date; //* ?
				TypeOfExpenditure type;
				bool paid;

				inputFile.read(buffer, sizeof(buffer)); //TODO: check //name
				//this->expenditures.at(i).setExpName(buffer);
				inputFile.read((char*)&fBuffer, sizeof(float)); //cost
				//this->expenditures.at(i).setCost(fBuffer);
				inputFile.read((char*)&date, sizeof(date));
				inputFile.read((char*)&type, sizeof(type));
				inputFile.read((char*)&paid, sizeof(paid));

				Expenditure myExp(buffer, fBuffer, &date, type, paid); //& ?
				expenditures.push_back(myExp);
			}
			inputFile.close();
		}
	}


	void generateReport(char* reportName) {
		cout << endl << "Generating user report..." << endl << endl;
		
		ofstream report;
		report.open(reportName, ios::out | ios::trunc);
		if (report.is_open()) {
			report << *this;
		}
		report.close();
	}

	void generateAllExpendituresReport(char* reportName) {
		cout << endl << "Generating expenditures report..." << endl << endl;

		ofstream report;
		report.open(reportName, ios::out | ios::trunc);
		if (report.is_open()) {
			for (int i = 0; i < this->expenditures.size(); i++)
			{
				report << "#" << i + 1;
				report << expenditures.at(i);
			}

		}
	}

	float getSumOfPaidExpenditures(bool paid)
	{
		float sum = 0;
			for (int i = 0; i < expenditures.size(); i++)
			{
					if (this->expenditures.at(i).getPaid() == paid)
						sum += this->expenditures.at(i).getCost();
			}
			return sum;
	}

	static void loginUser()
	{

	}

	static void registerUser()
	{

	}

	friend ostream& operator << (ostream& out, User user);

};

ostream& operator << (ostream& out, User user)
{
	float expendituresPaid = user.getSumOfPaidExpenditures(true);
	float expendituresNotPaid = user.getSumOfPaidExpenditures(false);
	out << "Username: " << user.getUsername() << endl;
	out << "Number of expenditures: " << user.getExpenditures().size() << endl;
	out << "Sum of paid expenditures : $" << expendituresPaid << endl;
	out << "Sum of payable expenditures: $" << expendituresNotPaid << endl;
	out << "Total sum of expenditures: $" << expendituresPaid + expendituresNotPaid << endl << endl;
	return out;
}

istream& operator >> (istream& input, User& user)
{
	char buffer[50];
	cout << "Username: ";
	input >> buffer;
	user.setUsername(buffer);

	cout << "Password: ";
	input >> buffer;
	user.setPassword(buffer);
	return input;
}

void main()
{
	struct tm* timp1;
	time_t moment1 = 1517436000; //1 feb 2018
	timp1 = localtime(&moment1);
	
	////Testing post++. Increments cost
	//Expenditure expTest1("test", 0, timp1, Food, false);
	//Expenditure expTest2 = expTest1++;
	//cout << "Testing post++. Increments cost" << endl << expTest1 << expTest2;

	////Testing operator! Paid switches value
	//cout << "Testing operator! Paid switches value." << endl << expTest1;
	//!expTest1;
	//cout << expTest1;



	
	Expenditure *exp1Food = new Expenditure((char*)"CheltuialaMancare", 2000, timp1, Food, true);
	//exp1Food->displayExpenditure();

	timp1->tm_hour = 4;
	Expenditure *exp1PC = new Expenditure((char*)"CheltuialaPC", 3000, timp1, PC, true);
	//exp1PC->displayExpenditure();

	timp1->tm_hour = 6;
	timp1->tm_min = 50;
	timp1->tm_sec = 30;
	Expenditure* exp1Clothing = new Expenditure((char*)"CheltuialaImbracaminte", 200, timp1, Clothing, false);

	
	vector<Expenditure> expsUser1;
	expsUser1.push_back(*exp1Food);
	expsUser1.push_back(*exp1PC);
	expsUser1.push_back(*exp1Clothing);
	
	

	BankAccount *acc1 = new BankAccount(5000, 500, 100, 0.20, 1000, 0.10);
	++*acc1; //adds $10.000 in cash
	BankAccount acc2(13500, 1000, 0, 0.10, 2000, 0.10);
	cout << "Testing operator== between bank accounts: ";
	if (*acc1 == acc2) //checks if accounts are equal in cash+debit+savings
		cout << "Equal accounts" << endl;
	else
		cout << "Not equal" << endl;

	//acc1->displayAccount();

	//cin >> *acc1;
	//cout << *acc1;

	User user1("JohnDoe", "1234", expsUser1 , acc1);
	//user1.displayAllExpenditures();
	user1.displayUserMenu();


	user1.saveData("userdata.dat");
	//user1.loadData("userdata.dat"); //TODO: doesn't work


	delete exp1Food;
	delete exp1PC;
	delete acc1;




	system("pause");
}