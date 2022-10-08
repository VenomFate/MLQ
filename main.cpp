#include<iostream>
#include<vector>
#include <string> 
using namespace std;

class Proceso{

    private:
    string nombre;
    int rafaga; 
    int prioridad;
    float llegada,TT,WT,tiempoActual;

    public:
    Proceso(){
        this->nombre = "N/A";
        this->rafaga = 0;
        this->prioridad = 0;
        this->llegada = 0;
        this->TT = 0;
        this->WT = 0;
        this->tiempoActual = 0;
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
    void setTT(float TT){
        this->TT = TT;
    }
    float getTT(){ 
        return this->TT;
    }
    void setWT(float WT){
        this->WT = WT;
    }
    float getWT(){ 
        return this->WT;
    }
    void setTiempoActual(float tiempoActual){
        this->tiempoActual = tiempoActual;
    }
    float getTiempoActual(){ 
        return this->tiempoActual;
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
            cout<<"Rafaga remanente:"<<Cola[i].getRafaga()<<endl;
            cout<<"Tiempo De llegada:"<<Cola[i].getLlegada()<<endl;
            cout<<"WT:"<<Cola[i].getWT()<<endl;
            cout<<"TT:"<<Cola[i].getTT()<<endl;
            cout<<"TiempoActual:"<<Cola[i].getTiempoActual()<<endl;
        }
}

float menorTiempo(vector<Proceso> Cola){
    float menor=Cola[0].getLlegada();
    for(int i=0;i<Cola.size();i++){
        if(Cola[i].getLlegada() < menor)
        menor = Cola[i].getLlegada();
    }
    return menor;
}

void RoundRobin1(vector<Proceso> Cola){
    int q1=3;
    float tiempoSistema=0;
    float TiempoActual = menorTiempo(Cola);
    float inicio = menorTiempo(Cola);
    vector<Proceso> Registro;
    while(!Cola.empty()){
        for(int i=0 ; i < Cola.size();i++){
                
            if(Cola[i].getLlegada() < TiempoActual){                                                           //si el proceso ya esta dentro del sistema entonces

                if(Cola[i].getRafaga() <= q1){
                    Cola[i].setWT(tiempoSistema);
                    tiempoSistema = tiempoSistema + Cola[i].getRafaga();                                                // si la rafaga es mas pequeña que el quantum se suma solo la rafaga remanente y se trabaja con el siguente proceso con un quantum nuevo
                    Cola[i].setRafaga(0);
                    Cola[i].setTT(tiempoSistema);
                    Cola[i].setTiempoActual(tiempoSistema+inicio);
                    Registro.push_back(Cola[i]);

                }
                else{
                    Cola[i].setWT(tiempoSistema);
                    tiempoSistema = tiempoSistema + q1;
                    Cola[i].setRafaga(Cola[i].getRafaga()-q1);
                    Cola[i].setTT(tiempoSistema);
                    Cola[i].setTiempoActual(tiempoSistema+inicio);
                    Registro.push_back(Cola[i]);
                }
                    

                if(Cola[i].getRafaga() <= 0) {                                                                 //Elimina elementos del queue en caso de que su rafaga sea menor a 0
                    cout<<"Tiempo de ejecucion completado: "<<Cola[i].getNombre()<<endl;
                    
                    Cola.erase(Cola.begin()+i);
                    
                }
            }
        }
        TiempoActual++;
    }
    MostrarVector(Registro);

}



int main(){
    float tiempoSistema = 0;                    //tiempo a sumar para la ejecucion del sistema
    vector<Proceso> RR1,RR2,FCFS,Cola;         
    Proceso procesoAux;  
    int q1=3,q2=8;
    Cola = CrearProcesos(10);
    float tiempoRR1 = 0;
    RoundRobin1(Cola);
   
    return 0;
}
