#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <omp.h>
#include <vector>

#define pb push_back

using namespace std;

int countStringInBase(string str, string base) {
	int count=0;
	if (base.length() < str.length() || str.length() == 0)
		return 0;
	for (int i=0; i<= base.length() - str.length();i++) {
		bool ok=true;
		for (int j=0; j<str.length(); j++) {
			if (base[i+j] != str[j]) {
				ok=false;
				break;
			}
		}
		count+=ok;
	}
	return count;
}

int main() {
	fstream base_file, match_file;
	string base, tmp;
	vector<string> to_match;
	base_file.open("base.txt", ios_base::in);
	match_file.open("strings.txt", ios_base::in);
	getline(base_file, base);
	while(!match_file.eof()){
		getline(match_file, tmp);
		to_match.pb(tmp);
	}
	cout<<base.size()<<endl;
	for(int i = 0; i < to_match.size(); i++){
		cout<<countStringInBase(to_match[i], base)<<'\n';
	}
	return 0;
}
