#include<iostream>
#include<vector>
#include <string> 
using namespace std;

class Proceso{

    private:
    string nombre;
    int rafaga; 
    int prioridad;
    float llegada;

    public:
    Proceso(){
        this->nombre = "N/A";
        this->rafaga = 0;
        this->prioridad = 0;
        this->llegada = 0;
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
    void setLlegada(float llegada){
        this->llegada = llegada;
    }
    float getLlegada(){ 
        return this->llegada;
    }

};
vector<Proceso> CrearProcesos(int n){           //Crea n cantidad de procesos con tiempos aleatorios, con nombres genericos
    vector<Proceso> procesos;
    Proceso procesoAux;
    int nombreCont = 0;
    while(n>0){
        
        procesoAux.setNombre("Job " + to_string(nombreCont));
        nombreCont++;
        procesoAux.setRafaga(rand()%10 + rand()%10);
        procesoAux.setPrioridad(rand()%10);
        procesoAux.setLlegada(rand()%10 * 0.1 + (rand()%10)*(rand()%10));
        procesos.push_back(procesoAux);
        n--;
    }
    return procesos;
}
void MostrarVector(vector<Proceso> Cola){
        for(int i=0; i <Cola.size();i++){
            cout<<endl<<Cola[i].getNombre()<<endl;
            cout<<"Prioridad:"<<Cola[i].getPrioridad()<<endl;
            cout<<"Rafaga:"<<Cola[i].getRafaga()<<endl;
            cout<<"Tiempo De llegada:"<<Cola[i].getLlegada()<<endl;
        }
}



int main(){
    float tiempoSistema = 0;                    //tiempo a sumar para la ejecucion del sistema
    vector<Proceso> RR1,RR2,FCFS,Cola;         
    Proceso procesoAux;  
    int q1=3,q2=8;
    Cola = CrearProcesos(10);
    MostrarVector(Cola);
    float tiempoRR1 = 0;

    while(!Cola.empty()){
        //procesoAux = Cola.back();
        
        for(int i=0 ; i < Cola.size();i++){
            
            if(Cola[i].getLlegada() < tiempoSistema){                                                           //si el proceso ya esta dentro del sistema entonces

                if(Cola[i].getRafaga() <= q1){
                    tiempoRR1 = tiempoRR1 + Cola[i].getRafaga();                                                // si la rafaga es mas pequeña que el quantum se suma solo la rafaga remanente y se trabaja con el siguente proceso con un quantum nuevo
                    Cola[i].setRafaga(0);
                    RR1.push_back(Cola[i]);
                }
                else{
                    tiempoRR1 = tiempoRR1 + q1;
                    Cola[i].setRafaga(Cola[i].getRafaga()-q1);
                    RR1.push_back(Cola[i]);
                }
                

                if(Cola[i].getRafaga() <= 0) {                                                                 //Elimina elementos del queue en caso de que su rafaga sea menor a 0
                    cout<<"Tiempo de ejecucion completado: "<<Cola[i].getNombre()<<endl;
                    
                    Cola.erase(Cola.begin()+i);
                    
                }
            }
        }
        tiempoSistema ++;
        
    }
    MostrarVector(RR1);
    cout<<"Cantidad de iteraciones realizadas: "<<tiempoSistema<<endl;
    cout<<"Tiempo Total De ejecucion quantum1/RR1: "<<tiempoRR1;
    
    
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