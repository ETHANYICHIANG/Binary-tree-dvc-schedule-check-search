//Programmer: Ethan Yi Chiang
//Programmer ID: 1538719

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
using namespace std;

#include <cstring>

int termToInt(const string);

int main()
{
	cout << "Programmer: Ethan Chiang\n"
       << "Programmer's ID: 1538719\n"
       << "File: " << __FILE__ << "\n\n";

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if(!fin.good()) throw "I/O error";

  // store class info
  map<string, set<int> > allClass;

  // read the input file
  while(fin.good())
  {
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if(course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    allClass[course].insert(termToInt(term));
  }
  fin.close();

  string uin;
  while(true)
  {
	  cout << "Enter a course name to be search[X/x to exit]: ";
	  getline(cin, uin);
    if(uin == "X" || uin == "x") break;

	  if(!allClass[uin].empty())
	  {
      cout << uin << " was last offered in ";
      if(*allClass[uin].rbegin() % 10 == 3) cout << "Fall ";
      else if(*allClass[uin].rbegin() % 10 == 2) cout << "Summer ";
      else if(*allClass[uin].rbegin() % 10 == 1) cout << "Spring";
      cout << *allClass[uin].rbegin() / 10 << endl;
	  }
	  else
	  	cout << "I didn't find " << uin << endl;
  }
  return 0;
}

int termToInt(const string termAndYear)
{
  string term = termAndYear.substr(0, termAndYear.find(" "));
  size_t pos = termAndYear.find(" ");
  string year = termAndYear.substr(pos);

  if(term == "Spring") return stoi(year) * 10 + 1;
  else if(term == "Summer") return stoi(year) * 10 + 2;
  else if(term == "Fall") return stoi(year) * 10 + 3;
  else return 0;
}
