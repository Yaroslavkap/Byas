#include<iostream>
#include<fstream>
#include<math.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;


class Email {

public:
	Email();
	~Email();

	string datatxt = "";
	string spam_or_ham_ = "";

	
};

class Vacabloary {
public:
	string word = "";
	double  number = 0; // amount number of this word
	double spam_num = 0; //number in spam
	double ham_num = 0; // number in hum

	long double probability = 0;
	long double probability_spam = 0;
	long double probability_ham = 0;
};

Email::Email() {
	spam_or_ham_ = "0";
	datatxt = "";
}

Email::~Email() {}

//Functions




vector<Vacabloary> Str_to_Vacabl(string all, string spam, string ham, const int WORDS_SET_SIZE)
{
    vector<Vacabloary> vac(WORDS_SET_SIZE);
    vector<string> vect(WORDS_SET_SIZE);
    
    stringstream ss(all);
    stringstream ss1(spam);
    stringstream ss2(ham);

    string word; // for storing each word
    int i = 0;
    while (ss >> word)
    {
        std::vector<std::string>::iterator it = find(vect.begin(), vect.end(), word);
        if (it == vect.end()) {
            Vacabloary v;
            v.word = word;
            vac[i].word = word;
            vect[i] = word;
            vac[i].number = 1;
            i++;
        }
        else {
            vac[it - vect.begin()].number = vac[it - vect.begin()].number + 1;
        }
    }

    //spam
    while (ss1 >> word)
    {
        std::vector<std::string>::iterator it = find(vect.begin(), vect.end(), word);
        if (it != vect.end()) {
            vac[it - vect.begin()].spam_num = vac[it - vect.begin()].spam_num + 1;
        }

    }

    //ham
    while (ss2 >> word)
    {
        std::vector<std::string>::iterator it = find(vect.begin(), vect.end(), word);
        if (it != vect.end()) {
            vac[it - vect.begin()].ham_num = vac[it - vect.begin()].ham_num + 1;
        }

    }

    //probabilities
    double count_all = 0;
    double count_spam = 0;
    double count_ham = 0;

    long double prob = 0;
    long double prob_spam = 0;
    long double prob_ham = 0;

    for (int a = 0; a < vac.size(); a++) {
        count_all += vac[a].number;
        count_spam += vac[a].spam_num;
        count_ham += vac[a].ham_num;
    }

    //cout << "counts" << count_all << " " << count_spam << " " << count_ham << endl;

    for (int a = 0; a < vac.size(); a++) {
        vac[a].probability = (vac[a].number / count_all);
        vac[a].probability_spam = (vac[a].spam_num / count_spam);
        vac[a].probability_ham = (vac[a].ham_num / count_ham);
    }



    return vac;
}


vector<string> Str_Vector(string str, const int WORDS_SET_SIZE)
{
    vector<string> vect(WORDS_SET_SIZE);
    stringstream ss(str);

    string word; // for storing each word

    int i = 0;
    while (ss >> word)
    {
        std::vector<std::string>::iterator it = find(vect.begin(), vect.end(), word);
        if (it == vect.end()) {
            
            vect[i] = word;
            i++;
        }

    }
    return vect;
}

int Str_number(string str) {
    stringstream ss(str);
    string word;
    int number = 0;
    vector<string> vect;

    while (ss >> word)
    {
        std::vector<std::string>::iterator it = find(vect.begin(), vect.end(), word);
        if (it == vect.end()) {

            vect.push_back(word);
            number++;
        }

    }
    return number;

}


vector<double> Mail_Vector(string str, vector<string> vacabl, const int WORDS_SET_SIZE) {
    vector<double> numbers(WORDS_SET_SIZE);
    stringstream ss(str);
    string word; // for storing each word
    int i = 0;
    while (ss >> word)
    {
        std::vector<std::string>::iterator it = find(vacabl.begin(), vacabl.end(), word);
        if (it != vacabl.end()) {
            numbers[it - vacabl.begin()] = numbers[it - vacabl.begin()] + 1;
        }

    }


    return numbers;
}


string toLower(string str) {
    //int l = str.length();
    //char a = '.';
    //char b = ",";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '.' || str[i] == ',') {
            str[i] = ' ';
        }
        str[i] = tolower(str[i]);
    }
    return str;
}

//Main

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int train, tests;
    cin >> train >> tests;
    //cout << train << tests << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const int mail_num = train + 1;


    //Train//
    vector<Email> Emails(mail_num);
    for (int i = 0; i < train; i++) {

        string s_h;
        getline(cin, s_h);
        Emails[i].spam_or_ham_ = s_h;
        string mail_data;
        getline(cin, mail_data);
        Emails[i].datatxt = mail_data;

    }
    
    // all spam
    string all_spam_txt;
    for (int i = 0; i < train; i++) {
        if (Emails[i].spam_or_ham_ == "0") {
            string data = all_spam_txt;
            all_spam_txt = data + " " + Emails[i].datatxt;
        }
    }
    all_spam_txt = toLower(all_spam_txt);
    // all ham
    string all_ham_txt;
    for (int i = 0; i < train; i++) {
        if (Emails[i].spam_or_ham_ == "1") {
            string data = all_ham_txt;
            all_ham_txt = data + " " + Emails[i].datatxt;
        }
    }
    all_ham_txt = toLower(all_ham_txt);

    //all data
    string all_txt = all_ham_txt + all_spam_txt;

    const int WORDS_SET_SIZE = Str_number(all_txt);

    //>
    //< Make vacabloaries
    vector<Vacabloary> vacab_all(WORDS_SET_SIZE);
    vacab_all = Str_to_Vacabl(all_txt, all_spam_txt, all_ham_txt, WORDS_SET_SIZE);
    //>

    //<Tests

    vector<string> vacabl(WORDS_SET_SIZE);
    vacabl = Str_Vector(all_txt, WORDS_SET_SIZE);

    for (int i = 0; i < tests; i++) {
        string mail;
        getline(cin, mail);
        vector<double> mail_nums(WORDS_SET_SIZE);
        mail_nums = Mail_Vector(mail, vacabl, WORDS_SET_SIZE);

        long double prob_spam = 0;
        long double prob_ham = 0;
        long double prob_spam_all = 0.5;
        for (int i = 0; i < WORDS_SET_SIZE; i++) {
            //cout << "probability_spam" << vacab_all[i].probability_spam << "  mail_nums[i]" << mail_nums[i] << "  vacab_all[i].probability" << vacab_all[i].probability << endl;
            if (vacab_all[i].probability != 0 || mail_nums[i] != 0) {
                prob_spam += 0.5 * (vacab_all[i].probability_spam) * (mail_nums[i]) / (vacab_all[i].probability);
                prob_ham += 0.5 * (vacab_all[i].probability_ham) * (mail_nums[i]) / (vacab_all[i].probability);
            }
        }
        if (prob_ham > prob_spam) {
            cout << "1" << endl;
        }
        else {
            cout << "0" << endl;
        }
    }
    //>
    return 0;
}