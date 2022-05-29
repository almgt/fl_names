#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
using namespace std;

class Person {
public:
    Person(const string& fn, const string& ln, int year) {
        year_of_birth = year;
        ChangeFirstName(year, fn);
        ChangeLastName(year, ln);
    }
    void ChangeFirstName(int year, const string& first_name) {
        if (year >= year_of_birth) {
            fn[year] = first_name; // добавить факт изменения имени на first_name в год year
            range_year1.push_back(year);
            sort(range_year1.begin(), range_year1.end());
        }
    }
    void ChangeLastName(int year, const string& last_name) {
        if (year >= year_of_birth) {
            ln[year] = last_name; // добавить факт изменения фамилии на last_name в год year
            range_year2.push_back(year);
            sort(range_year2.begin(), range_year2.end());
        }
    }
    string GetFullName(int year) const {
        string full;
        string f_name;
        string l_name;
        if (year < year_of_birth) { return "No person"; }
            if ((year < range_year1[0]) && (year < range_year2[0])) { // если в год еще не было запросов по смене ни имени, ни фамилии
                full = "Incognito";
                return full;
            }
            if (year < range_year1[0]) {
                f_name = "with unknown first name";
            }
            else for (const auto& item : fn) {
                if (item.first <= year) {
                    f_name.clear();
                    f_name += item.second;
                    continue;
                }
            }
            if (year < range_year2[0]) {
                l_name = "with unknown last name";
            }
            else for (const auto& item : ln) {
                if (item.first <= year) {
                    l_name.clear();
                    l_name += item.second;
                    continue;
                }
            }
            if (year < range_year1[0]) {
                full = l_name + " " + f_name;
            }
            else full = f_name + " " + l_name;
        return full;
    }  // получить имя и фамилию по состоянию на конец года year

    string GetFullNameWithHistory(int year) const {
        string full;
        string f_name;
        string l_name;
        vector<string> history_fname;
        vector<string> history_lname;
        string string_history_fname;
        string string_history_lname;
        if (year < year_of_birth) { return "No person"; }
            if ((year < range_year1[0]) && (year < range_year2[0])) { // если в год еще не было запросов по смене ни имени, ни фамилии
                full = "Incognito";
                return full;
            }
            if (year < range_year1[0]) {
                f_name = "with unknown first name";
            }
            else for (const auto& item : fn) {
                if (item.first <= year) {
                    f_name.clear();
                    f_name += item.second;
                    if (history_fname.empty()) { history_fname.push_back(f_name); }
                    if (f_name != history_fname.back()) { history_fname.push_back(f_name); }
                    continue;
                }
            } if (!history_fname.empty()) { history_fname.erase(history_fname.end() - 1); }
            reverse(history_fname.begin(), history_fname.end());
            for (const string& s : history_fname) {
                string_history_fname += s;
                string_history_fname += ", ";

            } if (!string_history_fname.empty()) { string_history_fname.resize(string_history_fname.size() - 2); }
            if (year < range_year2[0]) {
                l_name = "with unknown last name";
            }
            else for (const auto& item : ln) {
                if (item.first <= year) {
                    l_name.clear();
                    l_name += item.second;
                    if (history_lname.empty()) { history_lname.push_back(l_name); }
                    if (l_name != history_lname.back()) { history_lname.push_back(l_name); }
                    continue;
                }
            } if (!history_lname.empty()) { history_lname.erase(history_lname.end() - 1); }
            reverse(history_lname.begin(), history_lname.end());
            for (const string& s : history_lname) {
                string_history_lname += s;
                string_history_lname += ", ";
            } if (!string_history_lname.empty()) { string_history_lname.resize(string_history_lname.size() - 2); }
            if (f_name == "with unknown first name") {
                if (!history_lname.empty()) {
                    full = l_name += " (" + string_history_lname + ") " += f_name;
                }
                else full = l_name + " " + f_name;
            }
            else if ((history_fname.empty()) && (history_lname.empty())) { full = f_name + " " + l_name; }
            else if (history_fname.empty()) { full = f_name + " " + l_name + " (" + string_history_lname + ")"; }
            else if (history_lname.empty()) { full = f_name + " (" + string_history_fname + ") " + l_name; }
            else full = f_name + " (" + string_history_fname + ") " + l_name + " (" + string_history_lname + ")";
        return full; // получить все имена и фамилии по состоянию на конец года year
    }
private:
    int year_of_birth;
    map<int, string> fn;
    map<int, string> ln;
    vector<unsigned long long> range_year1{(size_t)-1};
    vector<unsigned long long> range_year2{(size_t)-1};// 2 вектора для записи и сортировки номеров года, в которые были запросы
    // приватные поля
};

int main() {
    Person person;
    
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

        /*person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeFirstName(1990, "Polina");
        person.ChangeLastName(1990, "Volkova-Sergeeva");
        cout << person.GetFullNameWithHistory(1990) << endl;

        person.ChangeFirstName(1966, "Pauline");
        cout << person.GetFullNameWithHistory(1966) << endl;

        person.ChangeLastName(1960, "Sergeeva");
        for (int year : {1960, 1967}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeLastName(1961, "Ivanova");
        cout << person.GetFullNameWithHistory(1967) << endl;*/

    /*Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }*/
    
    return 0;
}
