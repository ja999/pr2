#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
  fstream plik;
  plik.open("base.txt", ios_base::out);
  return 0;
}
