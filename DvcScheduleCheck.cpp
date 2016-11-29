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

  //key, course
  map<string, set<string> > allKeys;

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
    const string key = term + "-" + section;

    allKeys[key].insert(course);
  }
  fin.close();
  
  // output all dup keys
  map<string, set<string> >::iterator it;
  for(it = allKeys.begin(); it != allKeys.end(); it++)
    if(it->second.size() > 1)
    {
      set<string>::iterator it2;
      cout << "Multiple entrance found for key- " << it->first << ": \n";
      for(it2 = it->second.begin(); it2 != it->second.end(); it2++)
        cout << *it2 << endl;
    }

  return 0;
}
