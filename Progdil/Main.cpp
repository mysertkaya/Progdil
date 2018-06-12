#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iomanip>
//#include<algorithm>
#include<map>
using namespace std;

int NumberOfLines();
string * Lines(int NumberOfLines);
vector<string> produceListFromALine(string aLine, char split);
bool checkForString(vector<string>::iterator begin, vector<string>::iterator end, string val);
bool checkForChar(string look, char val);
void executeLines(string * Lines);
void removeSpaces();

int main() {
	try {
		//executeLines(Lines(NumberOfLines()));
		vector<string> hey = produceListFromALine("hey man", ' ');
		
		system("PAUSE");
	}
	catch (runtime_error &ex) {
		cout << ex.what() << endl;
		system("PAUSE");
	}
}

int NumberOfLines() {
	int numberOfLines = 0;
	string line;
	ofstream file("C:\\Users\\Yusuf\\Desktop\\Codes.txt");

	if (file.is_open()) {

		while (getline(cin, line)) {
			file << line << '\n';
			numberOfLines++;
		}
		file << "stop";
		file.close();
	} else throw runtime_error(" An error occured while opening file!\n");

	return ++numberOfLines;
}

string * Lines(int numberOfLines) {
	string * lines = new string[numberOfLines];
	string take;
	ifstream file("C:\\Users\\Yusuf\\Desktop\\Codes.txt",ios::beg);

	int i = 0;
	if (file.is_open()) {

		while (getline(file, take)) {
			lines[i] = take;
			i++;
		}

		file.close();
	} else throw runtime_error(" An error occured while opening file!\n");
	

	return lines;
}

vector<string> produceListFromALine(string aLine, char split) {
	vector<string> list;
	vector<char> word;
	for (size_t i = 0; i < aLine.length(); i++)
	{
		if (i == aLine.length() - 1) {
			word.push_back(aLine[i]);
			string temp(word.begin(), word.end());
			list.push_back(temp);
		}
		else if (aLine[i] != split) {
			word.push_back(aLine[i]);
		}
		else {
			string temp(word.begin(), word.end());
			if (!temp.empty()) list.push_back(temp);
			word.clear();
		}
	}
	return list;
}

bool checkForString(vector<string>::iterator begin, vector<string>::iterator end,string val) {
	while (begin != end) {
		if (*begin == val) return true;
		begin++;
	}
	return false;
}

void removeSpaces() {

}

bool checkForChar(string look, char val) {
	size_t take = look.find(val);
	if (take != string::npos) return true;
	return false;
}

void executeLines(string * lines) {
	string reservedKeywords[2] = { "svar", "print" };
	vector<string> listOfWords; int count = 0;
	map<string, int> variableNames;
	for (; *lines != "stop"; lines++)
	{
		count++;
		listOfWords = produceListFromALine(*lines, ' ');

		//Comma checkForString
		string CommaCheck = listOfWords[listOfWords.size() - 1];
		if (CommaCheck[CommaCheck.length() - 1] != ';') throw runtime_error(" An error occured: Expected ';' at the end of the statement " + count);
		//Svar variable definition
		if (checkForString(listOfWords.begin(),listOfWords.end(),"svar") ) {
			if (listOfWords.size() == 2) {
				variableNames.insert(make_pair(listOfWords[listOfWords.size() - 1], NULL));
				continue;
			}
			else
			{
				string error = " An error occured: Wrong definition of a variable in statement " + count;
				throw runtime_error(error);
			}
		}else if(listOfWords[0] == "svar") throw runtime_error(" An error occured: Wrong definition of a variable in statement " + count + '\n');

		//Print a variable
		if(checkForString(listOfWords.begin(),listOfWords.end(),"print")){
			if (listOfWords.size() == 2)
			{
				if (variableNames.find(listOfWords[1]) != variableNames.end())
				{
					if (variableNames[listOfWords[1]] != NULL) cout << variableNames[listOfWords[1]] << endl;
					else cout << "0x" << setw(6) << setfill('3') << rand() % 100000 << endl;
				}
				else throw runtime_error(" An error occured: Variable name couldn't find!");
			}
			else throw runtime_error(" An error occured: Wrong definition of a variable in statement " + count + '\n');
		}
		else if(listOfWords[0] == "print") throw runtime_error(" An error occured: Wrong style print in statement " + count + '\n');

		//Equality things
		for (size_t i = 0; i < listOfWords.size(); i++)
		{
			if (checkForChar(listOfWords[i], '=')) {
				if (listOfWords[i].length() == 1) {

				}
				else if (listOfWords.size() == 2 ){
					vector<string> withEqual = produceListFromALine(listOfWords[i], '=');
					string check = listOfWords[i];
					if (check[check.length() - 1] == '=') {

					}
					else if (check[0] == '=') {

					}else throw runtime_error(" An error occured: Wrong assignment in statement " + count + '\n');
				}
				else{
					vector<string> take = produceListFromALine(listOfWords[i], '=');
					if (take.size() == 2) {

					}
					else throw runtime_error(" An error occured: Wrong assignment in statement " + count + '\n');
				}
			}
		}
	}
}