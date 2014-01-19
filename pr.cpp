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

int main(int argc, char* argv[]) {
	fstream base_file, match_file;
	string base = "", tmp;
	vector<string> to_match, to_base;

	base_file.open(argv[1], ios_base::in);
	match_file.open(argv[2], ios_base::in);

	if(*argv[3] == '0'){
		while(!base_file.eof()){
			getline(base_file, tmp);
			base.append(tmp);
		}
		while(!match_file.eof()){
			getline(match_file, tmp);
			to_match.pb(tmp);
		}
		cout<<base.size()<<endl;
		#pragma omp parallel for
		for(int i = 0; i < to_match.size(); i++){
			cout<<countStringInBase(to_match[i], base)<<'\n';
		}
	} else if(*argv[3] == '1') {
		while(!match_file.eof()){
			getline(match_file, tmp);
			to_match.pb(tmp);
		}
		while(!base_file.eof()){
			getline(base_file, tmp);
			to_base.pb(tmp);
		}
		// #pragma omp parallel for
		for(int j = 0; j < to_base.size(); j++){
			#pragma omp parallel for
			for(int i = 0; i < to_match.size(); i++){
				cout<<countStringInBase(to_match[i], to_base[j])<<'\n';
			}
		}
	} else {
		cout<<"Wrong parameters"<<'\n';
	}
	return 0;
}
