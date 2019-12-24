#include <iomanip>
#include <ctime>
#include "workspace.h"

using namespace std;

int main(){
    Workspace wordspace;
    clock_t begin = clock();
    wordspace.run();
    clock_t end = clock();
    cout<<static_cast<double>(end - begin) / CLOCKS_PER_SEC * 1000<<"ms"<<endl;
    system("pause");
}