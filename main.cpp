#include<iostream>
#include<vector>
#include <string> 
using namespace std;

class Proceso{

    private:
    string nombre;
    int rafaga; 
    int prioridad;

    public:
    Proceso(){
        this->nombre = "N/A";
        this->rafaga = 0;
        this->prioridad = 0;
    }

    void setNombre(string nombre){
        this->nombre = nombre;
    }
    string getNombre(){ 
        return this->nombre;
    }
    void setRafaga(int rafaga){
        this->rafaga = rafaga;
    }
    int getRafaga(){ 
        return this->rafaga;
    }
    void setPrioridad(int prioridad){
        this->prioridad = prioridad;
    }
    int getPrioridad(){ 
        return this->prioridad;
    }

};
vector<Proceso> CrearProcesos(int n){           //Crea n cantidad de procesos con tiempos aleatorios, con nombres genericos
    vector<Proceso> procesos;
    Proceso procesoAux;
    int nombreCont = 0;
    while(n>0){
        
        procesoAux.setNombre("Job " + to_string(nombreCont));
        nombreCont++;
        procesoAux.setRafaga(rand()%10);
        procesoAux.setPrioridad(rand()%10);
        procesos.push_back(procesoAux);
        n--;
    }
    return procesos;
}
void MostrarVector(vector<Proceso> Cola){
        for(int i=0; i <Cola.size();i++){
            cout<<Cola[i].getNombre()<<endl;
        }
}

int main(){
    float tiempoSistema = 0;                    //tiempo a sumar para la ejecucion del sistema
    vector<Proceso> RR1,RR2,FCFS,Cola;               
    int q1=3,q2=8;
    Cola = CrearProcesos(10);
    MostrarVector(Cola);
    
    //while(!Cola.empty())
}

/*
int main(){
    vector<Proceso> a;
    Proceso job1;
    Proceso aux;
    job1.setRafaga(2323);
    a.push_back(job1);
    aux = a[0];
    cout<<")lol:"<<aux.getRafaga();
    return 0;
}
*/