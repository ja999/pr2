#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <omp.h>
#include <vector>

#define pb push_back

using namespace std;

void test_function(const char* description, void (*func)()) {
  if (first_time) {
    initialize_matrices();
    first_time = false;
  } else {
    initialize_C();
  }
  double start, elapsed;

  fprintf(result_file, "\n%s\n", description);
  printf("\n%s\n", description);
  LARGE_INTEGER freq;
  LARGE_INTEGER timer1, timer2;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&timer1);

  start = (double) clock() / CLK_TCK;
  func();
  elapsed = (double) clock() / CLK_TCK - start;

  QueryPerformanceCounter(&timer2);
  double process_time = double(timer2.QuadPart - timer1.QuadPart) / (freq.QuadPart / 1000.0);

  double resolution = 1.0 / CLK_TCK ;

  fprintf(result_file, "%8.4f msec (clock: %8.4f, res: %6.4f)\n", process_time, elapsed, resolution);
  printf("%8.4f (clock: %8.4f, res: %6.4f)\n", process_time, elapsed, resolution);
}

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
	int hit = 0;
	vector<string> to_match, to_base;
	vector<int> hits;

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
			hits.pb(hit);
		}
		#pragma omp parallel for
		for(int i = 0; i < to_match.size(); i++){
			hits[i] += countStringInBase(to_match[i], base);
		}
		for(int i = 0; i < hits.size(); ++i){
			cout<<to_match[i]<<' '<<hits[i]<<'\n';
		}
	} else if(*argv[3] == '1') {
		while(!match_file.eof()){
			getline(match_file, tmp);
			to_match.pb(tmp);
			hits.pb(hit);
		}
		while(!base_file.eof()){
			getline(base_file, tmp);
			to_base.pb(tmp);
		}
		// #pragma omp parallel for
		for(int j = 0; j < to_base.size(); j++){
			#pragma omp parallel for
			for(int i = 0; i < to_match.size(); i++){
				hits[i] += countStringInBase(to_match[i], to_base[j]);
			}
		}
		for(int i = 0; i < hits.size(); ++i){
			cout<<to_match[i]<<' '<<hits[i]<<'\n';
		}
	} else {
		cout<<"Wrong parameters"<<'\n';
	}
	return 0;
}
