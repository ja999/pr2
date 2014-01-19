#include <iostream>
#include <time.h>
#include <stdio.h>
#include <omp.h>

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
	cout<<countStringInBase("t","")<<endl;
	printf("kurwa...\n");
	return 0;
}
