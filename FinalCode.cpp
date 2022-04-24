#include<bits/stdc++.h>
using namespace std;


#define RESET "\033[0m"
#define BLACK "\033[30m"			  /* Black */
#define RED "\033[31m"				  /* Red */
#define GREEN "\033[32m"			  /* Green */
#define YELLOW "\033[33m"			  /* Yellow */
#define BLUE "\033[34m"				  /* Blue */
#define MAGENTA "\033[35m"			  /* Magenta */
#define CYAN "\033[36m"				  /* Cyan */
#define WHITE "\033[37m"			  /* White */
#define BOLDBLACK "\033[1m\033[30m"	  /* Bold Black */
#define BOLDRED "\033[1m\033[31m"	  /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"	  /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"	  /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"	  /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"	  /* Bold White */
void clrscr()
{
	cout << "\033[2J\033[1;1H";
}

class Contact
{
private:
	string number;
	string email;
	int frequency;
public:
	string name;
	void setphone(string phoneno){
		regex rp("\\d{10}");
		auto isValidPhoneNumber = regex_match(phoneno, rp);
		if (!(isValidPhoneNumber))
		{
			clrscr();
			cout << RED << "\ninvalid phoneno" << RESET << endl;
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		number=phoneno;
	}
	void setemail(string email){
		regex re("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		auto isValidemail = regex_match(email, re);
		if (!(isValidemail))
		{
			clrscr();
			cout << RED << "\ninvalid email" << RESET << endl;
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		this->email=email;
	}

	string getphoneno(){
		return number;
	}
	string getemail(){
		return email;
	}

	int freq(){
		return frequency;
	}


	Contact(string name, string number, string email)
	{
		this->name = name;
		setphone(number);
		setemail(email);
		frequency = 0;
	}
	void visited()
	{
		frequency++;
	}
};

class TrieNode
{
public:
	unordered_map<char, TrieNode *> child;
	TrieNode *parent;
	bool isLast;
	TrieNode()
	{
		child = unordered_map<char, TrieNode *>();
		for (char i = 'a'; i <= 'z'; i++)
		{
			child[i] = nullptr;
		}
		parent = nullptr;
		isLast = false;
	}
};
class Trie
{
public:
	TrieNode *root;
	Trie()
	{
		root = new TrieNode();
	}
	void insert(string s)
	{
		//O(len of word)
		int len = s.length();
		TrieNode *itr = root;
		for (int i = 0; i < len; i++)
		{
			TrieNode *nextNode = itr->child[s[i]];
			if (nextNode == nullptr)
			{
				nextNode = new TrieNode();
				nextNode->parent = itr;
				itr->child[s[i]] = nextNode;
			}
			itr = nextNode;
			if (i == len - 1)
			{
				itr->isLast = true;
			}
		}
	}
	void deletenodes(TrieNode *curNode, TrieNode *deletetill, stack<char> letters)
	{
		//O(len of word to be deleted)
		TrieNode *prevnode = curNode->parent;
		bool flag = false;
		if (curNode != deletetill)
			flag = true;

		if (curNode == root)
			return;
		delete curNode->parent->child[letters.top()];
		curNode->parent->child[letters.top()] = nullptr;
		curNode = NULL;

		letters.pop();
		if (flag)
			deletenodes(prevnode, deletetill, letters);
	}
	void deletename(string str)
	{
		//O(len) + O(len) = O(len)
		TrieNode *prevNode = root;
		TrieNode *deletetill = root;
		int len = str.length();
		string name;
		stack<char> letters;
		int i;
		for (i = 0; i < len; i++)
		{
			name += (char)str[i];
			char lastChar = name[i];
			letters.push(lastChar);
			bool deletetillflag = false;
			if (prevNode->isLast)
			{
				deletetillflag = true;
			}
			else
			{
				for (char j = 'a'; j <= 'z'; j++)
				{
					if ((prevNode->child[j] != nullptr) && lastChar != j)
					{
						deletetillflag = true;
						break;
					}
				}
			}

			TrieNode *curNode = prevNode->child[lastChar];
			if (deletetillflag)
			{
				deletetill = curNode;
			}
			if (curNode == NULL)
			{
				cout << "\nNo Results Found for " << name
						  << "\n";
				i++;
				break;
			}
			prevNode = curNode;
			if (i == len - 1)
			{
				char j;
				for (j = 'a'; j <= 'z'; j++)
				{
					if (prevNode->child[j] != nullptr)
					{
						prevNode->isLast = false;
						return;
					}
				}
			}
		}
		deletenodes(prevNode, deletetill, letters);
	}

	void displayalphabetically(TrieNode *curNode, string prefix, vector<string> *arrangedcontacts)
	{
		//O(Longestlen)
		if (curNode == nullptr)
		{
			return;
		}
		else
		{
			if (curNode->isLast)
			{
				arrangedcontacts->push_back(prefix);
			}
			for (char i = 'a'; i <= 'z'; i++)
			{
				if (curNode->child[i] != nullptr)
				{
					displayalphabetically(curNode->child[i], prefix + i, arrangedcontacts);
				}
			}
		}
	}

	void displayContactsUtil(TrieNode *curNode, string prefix, vector<string> *contactsWithPrefix)
	{
		//O(n) --> used by getContacts function to displaycontacts relevant to a suggestion query
		if (curNode->isLast)
		{
			contactsWithPrefix->push_back(prefix);
		}
		for (char i = 'a'; i <= 'z'; i++)
		{
			TrieNode *nextNode = curNode->child[i];
			if (nextNode != nullptr)
			{
				displayContactsUtil(nextNode, prefix + i, contactsWithPrefix);
			}
		}
	}
	void getContacts(string str, vector<string> *arrangedcontacts)
	{
		//O(n)
		TrieNode *prevNode = root;

		string prefix = "";
		int len = str.length();

		int i;
		for (i = 0; i < len; i++)
		{
			prefix += (char)str[i];
			char lastChar = prefix[i];
			TrieNode *curNode = prevNode->child[lastChar];
			if (curNode == NULL)
			{
				cout << "\nNo Results Found for " << str
						  << "\n";
				i++;
				break;
			}
			if (i == len - 1)
			{
				cout << "\nSuggestions based on " << prefix
						  << " are \n";
				displayContactsUtil(curNode, prefix, arrangedcontacts);
			}
			prevNode = curNode;
		}
	}
};

class PhoneBookDirectory
{
public:
	unordered_map<string, Contact *> phonebook;
	Trie *trie;
	vector<string> *frequentlyvisited;

	int Partition(vector<string> &v, int start, int end)
	{

		int pivot = end;
		int j = start;
		for (int i = start; i < end; ++i)
		{
			if (phonebook[v[i]]->freq() > phonebook[v[pivot]]->freq())
			{
				swap(v[i], v[j]);
				++j;
			}
		}
		swap(v[j], v[pivot]);
		return j;
	}

	void Quicksort(vector<string> &v, int start, int end)
	{
		//avg case - O(nlogn)

		if (start < end)
		{
			int p = Partition(v, start, end);
			Quicksort(v, start, p - 1);
			Quicksort(v, p + 1, end);
		}
	}

	PhoneBookDirectory()
	{
		phonebook = unordered_map<string, Contact *>();
		trie = new Trie();
		frequentlyvisited = new vector<string>;
	}
	void addContact()
	{
		string name;
		string phoneno;
		string email;
		clrscr();
		cout << BOLDCYAN << "ADD CONTACT" << RESET << endl;
		cout << "name: ";
		cin >> name;
		cout << "number: ";
		cin >> phoneno;
		regex rp("\\d{10}");
		auto isValidPhoneNumber = regex_match(phoneno, rp);
		if (!(isValidPhoneNumber))
		{
			clrscr();
			cout << RED << "\ninvalid phoneno" << RESET << endl;
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		cout << "email: ";
		cin >> email;
		regex re("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		auto isValidemail = regex_match(email, re);
		if (!(isValidemail))
		{
			clrscr();
			cout << RED << "\ninvalid email" << RESET << endl;
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		if (!(phonebook.find(name) == phonebook.end()))
		{
			clrscr();
			cout << RED << "\ncontact with name " << name << " already exists" << RESET << endl;
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}


		Contact *newcont = new Contact(name, phoneno, email);
		phonebook[name] = newcont;
		frequentlyvisited->push_back(name);
		trie->insert(name);
		clrscr();
		cout << GREEN << "\nadded " << name << "'s contact" << RESET << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}

	void selectcontact(vector<string> *arrangedcontacts)
	{
		int index = 0;
		int selector;
		int action = 0;
		int operation;
		for (auto i : *arrangedcontacts)
		{
			cout << ++index << ": " << i << endl;
		}
		cout << "\nselect contact " << RED << "(or press 0 to exit)\n" << RESET ": ";
		cin >> selector;
		if (selector == 0)
			return;
		phonebook[arrangedcontacts->at(selector - 1)]->visited();
		clrscr();
		cout << BOLDCYAN << "VIEWING CONTACT" << RESET << endl;
		cout << "\n"
				  << arrangedcontacts->at(selector - 1) << "\t" << phonebook[arrangedcontacts->at(selector - 1)]->getphoneno() << "\t" << phonebook[arrangedcontacts->at(selector - 1)]->getemail() << "\n"
				  << endl;
		cout << RED << "1. delete\n"
				  << RESET << "2. edit\n3. exit" << endl;
		cin >> action;
		switch (action)
		{
		case 1:
			cout << arrangedcontacts->at(selector - 1);
			cout.flush();
			deletecontact(arrangedcontacts->at(selector - 1));
			break;
		case 2:
			editcontact(arrangedcontacts->at(selector - 1));
			break;

		default:
			return;
		}
	};

	void showfrequent()
	{
		clrscr();
		cout << BOLDCYAN << "FREQUENT CONTACTS" << RESET << endl;
		Quicksort(*frequentlyvisited, 0, frequentlyvisited->size() - 1);
		selectcontact(frequentlyvisited);
	}
	void displaysearchresults(vector<string> arrangedcontacts)
	{
		for (auto i : arrangedcontacts)
		{
			cout << i << "\n";
		}
	}
	void searchAndShowNoForAllCombination()
	{
		vector<string> arrangedcontacts;
		string query = "";
		char c;
		do
		{
			clrscr();
			cout << BOLDCYAN << "SEARCH" << RESET << endl;
			cout << "name: " << query << "|" << GREEN << "press 0 to select contact" << RESET;
			trie->getContacts(query, &arrangedcontacts);
			displaysearchresults(arrangedcontacts);
			cin >> c;
			if (c == '0')
				break;
			query = query + c;
			arrangedcontacts.clear();
		} while (true);
		clrscr();
		selectcontact(&arrangedcontacts);
	}

	void showalphabetically()
	{
		clrscr();
		cout << BOLDCYAN << "ALL CONTACTS" << RESET << endl;
		vector<string> arrangedcontacts;
		if (phonebook.empty())
		{
			cout << RED << "\ndirectory empty\n"
					  << RESET << endl;
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		trie->displayalphabetically(trie->root, "", &arrangedcontacts);
		selectcontact(&arrangedcontacts);
	}

	void deletecontact(string name)
	{
		trie->deletename(name);
		phonebook.erase(name);
		vector<string>::iterator itr;
		for (itr = frequentlyvisited->begin(); itr != frequentlyvisited->end(); itr++)
		{
			if (*itr == name)
			{
				frequentlyvisited->erase(itr);
				break;
			}
		}
		clrscr();
		cout << RED << "\ndeleted " << name << "'s contact" << RESET << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
	void editcontact(string name)
	{
		clrscr();
		char selector;
		cout << BOLDCYAN << "editing " << name << "..." << RESET << endl;
		string newname = name;
		string newnumber;
		string newemail;
		cout << BOLDWHITE << "\nedit name?: " << BOLDGREEN << "y" << RESET << "/" << BOLDRED << "n" << RESET << endl;
		cin >> selector;
		if (selector == 'y')
		{
			cout << BOLDWHITE << "type new name: " << RESET;
			cin >> newname;
			trie->deletename(name);
			trie->insert(newname);
			phonebook[newname] = phonebook[name];
			phonebook.erase(name);
			vector<string>::iterator itr;
			for (itr = frequentlyvisited->begin(); itr != frequentlyvisited->end(); itr++)
			{
				if (*itr == name)
				{
					frequentlyvisited->erase(itr);
					break;
				}
			}
			frequentlyvisited->push_back(newname);
		}
		cout << BOLDWHITE << "\nedit number?: " << BOLDGREEN << "y" << RESET << "/" << BOLDRED << "n" << RESET << endl;
		cin >> selector;
		if (selector == 'y')
		{
			cout << BOLDWHITE << "type new number: " << RESET;
			cin >> newnumber;
			phonebook[newname]->setphone(newnumber);
		}
		cout << BOLDWHITE << "\nedit email?: " << BOLDGREEN << "y" << RESET << "/" << BOLDRED << "n" << RESET << endl;
		cin >> selector;
		if (selector == 'y')
		{
			cout << BOLDWHITE << "type new mail: " << RESET;
			cin >> newemail;
			phonebook[newname]->setemail(newemail);
		}
		clrscr();
		cout << GREEN << "\nupdated " << name << "'s contact" << RESET << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
};

class Account
{
public:
	string username;
	bool checkpass(string pass)
	{
		return pass == password;
	}
	PhoneBookDirectory *getdir()
	{
		return directory;
	}
	Account(string username, string password)
	{
		this->username = username;
		this->password = password;
		directory = new PhoneBookDirectory();
	}

private:
	string password;
	PhoneBookDirectory *directory;
};

void dashboard(Account *account)
{
	PhoneBookDirectory *directory = new PhoneBookDirectory();
	directory = account->getdir();
	bool loggedin = true;
	do
	{
		clrscr();
		cout << BOLDCYAN << "Hi " << account->username << "!" << RESET << endl;
		cout << "\n1. view all contacts\n2. search contact\n3. add contact\n4. show frequent contacts\n5. logout\n";
		int x;
		cin >> x;
		switch (x)
		{
		case 5:
			loggedin = false;
			break;
		case 4:
			directory->showfrequent();
			break;
		case 3:
			directory->addContact();
			break;

		case 2:
			directory->searchAndShowNoForAllCombination();
			break;

		case 1:
			directory->showalphabetically();
			break;

		default:
			break;
		}
	} while (loggedin);
}

void createaccount(unordered_map<string, Account *> &accounts)
{
	clrscr();
	cout << BOLDCYAN << "NEW ACCOUNT" << RESET << endl;
	string username;
	string password;
	cout << BOLDWHITE << "username: " << RESET;
	cin >> username;
	cout << BOLDWHITE << "password: " << RESET;
	cin >> password;
	Account *newaccount = new Account(username, password);
	accounts[username] = newaccount;
	dashboard(newaccount);
}

void login(unordered_map<string, Account *> &accounts)
{
	char ynselector;
	string username;
	string password;
	cout << BOLDCYAN << "CONTACTS APP" << RESET << endl;
	if (accounts.empty())
	{
		cout << "no accounts available\ncreate new account?: " << BOLDGREEN << "y" << RESET << "/" << BOLDRED << "n" << RESET << endl;
		cin >> ynselector;
		if (ynselector == 'y')
		{
			createaccount(accounts);
		}
	}
	else
	{
		int selector;
		cout << BOLDWHITE << "1. login to existing account\n2. create a new account\n3. quit \n"
				  << RESET;
		cin >> selector;
		if (selector == 1)
		{
			clrscr();
			cout << BOLDCYAN << "LOGIN" << RESET << endl;
			cout << BOLDWHITE << "username: " << RESET;
			cin >> username;
			cout << BOLDWHITE << "password: " << RESET;
			cin >> password;
			try
			{
				if (accounts[username]->checkpass(password))
				{
					dashboard(accounts[username]);
				}
				else
				{
					cout << RED << "password incorrect\n"
							  << RESET;
				}
			}
			catch (...)
			{
				cout << RED << "account doesnt exist" << RESET;
			}
		}
		else if (selector == 2)
		{
			createaccount(accounts);
		}
		else
		{
			exit(0);
		}
	}
}

int main()
{
	unordered_map<string, Account *> *accounts = new unordered_map<string, Account *>;
	do
	{
		clrscr();
		login(*accounts);
	} while (true);
}
