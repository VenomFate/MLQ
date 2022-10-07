#include <iostream>
#include <queue>

using namespace std;

#define MAX 1000

int tlleg[MAX], raf[MAX], prioridad[MAX]; 

void FCFS (int n){
    int a, b, i;
    for(i=0; i<n; i++){
        a = tlleg[i];
        b = a + raf[i];
    }
    
}



int main()
{
    int nproc;
    int i;
    cout << "MLQ" << endl;
    cout << "===" << endl << endl;
    cout << "Ingrese la cantidad de procesos: ";
    cin >> nproc;
    system("clear");
    for (i=0; i<nproc; i++){
        cout << "Proceso " << i+1 << endl;
        cout << "Ingrese el tiempo de llegada: ";
        cin >> tlleg[i];
        cout << "Ingrese rafaga: ";
        cin >> raf[i]; 
        cout << "Ingrese prioridad: ";
        cin >> prioridad[i];
        system("clear");
    }

    '''
    for(i=0; i<nproc; i++){
        cout << "" << tlleg[i] << endl;
        cout << "" << raf[i] << endl;
        cout << "" << prioridad[i] << endl;
    }
    '''

    return 0;
}
