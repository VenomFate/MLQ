#include<iostream>
#include<vector>
#include <string> 
using namespace std;

class Proceso{

    private:
    string nombre;
    int rafaga,rafagaInicial; 
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
        this->rafagaInicial = 0;
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
    void setRafagaInicial(int rafagaInicial){
        this->rafagaInicial = rafagaInicial;
    }
    int getRafagaInicial(){ 
        return this->rafagaInicial;
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
        procesoAux.setRafagaInicial(procesoAux.getRafaga());
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
            cout<<"Rafaga Inicial:"<<Cola[i].getRafagaInicial()<<endl;
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
float mayorTiempo(vector<Proceso> Cola){
    float mayor=0;
    for(int i=0;i<Cola.size();i++){
        if(Cola[i].getLlegada() > mayor)
        mayor = Cola[i].getLlegada();
    }
    return mayor;
}

void RoundRobin(vector<Proceso> Cola, int q){
    float tiempoSistema=0;
    float TiempoActual = menorTiempo(Cola);
    float inicio = menorTiempo(Cola);
    vector<Proceso> Registro;
    int contador=0;
    while(!Cola.empty()){
        for(int i=0 ; i < Cola.size();i++){
                
            if(Cola[i].getLlegada() <= TiempoActual){                                                           //si el proceso ya esta dentro del sistema entonces
                
                if(Cola[i].getRafaga() <= q){
                    Cola[i].setWT(TiempoActual-inicio-0.1*contador);
                    TiempoActual = TiempoActual + Cola[i].getRafaga();                                             // si la rafaga es mas pequeña que el quantum se suma solo la rafaga remanente y se trabaja con el siguente proceso con un quantum nuevo
                    Cola[i].setRafaga(0);
                    Cola[i].setTT(TiempoActual-inicio-0.1*contador);
                    Cola[i].setTiempoActual(TiempoActual-0.1*contador);
                    Registro.push_back(Cola[i]);
                    
                }
                else{
                    Cola[i].setWT(TiempoActual- inicio -0.1*contador);
                    TiempoActual = TiempoActual + q;
                    Cola[i].setRafaga(Cola[i].getRafaga() - q);
                    Cola[i].setTT(TiempoActual- inicio - 0.1*contador);
                    Cola[i].setTiempoActual(TiempoActual-0.1*contador);
                    Registro.push_back(Cola[i]);
                    
                }
                    

                if(Cola[i].getRafaga() <= 0) {                                                                 //Elimina elementos del queue en caso de que su rafaga sea menor a 0
                    cout<<"Tiempo de ejecucion completado: "<<Cola[i].getNombre()<<endl;
                    
                    Cola.erase(Cola.begin()+i);
                    
                }
                
            }
            
             
        
        }
        contador++;
        TiempoActual = TiempoActual + 0.1;       
    }
    MostrarVector(Registro);

}

void fcfs(vector<Proceso> Cola){
    float tiempoSistema=0;
    float TiempoActual = menorTiempo(Cola);
    float inicio = menorTiempo(Cola);
    vector<Proceso> Registro;
    int contador=0;
    while(!Cola.empty()){
        for(int i=0 ; i < Cola.size();i++){
                
            if(Cola[i].getLlegada() <= TiempoActual){                                                           //si el proceso ya esta dentro del sistema entonces
                
                
                    Cola[i].setWT(TiempoActual-inicio-0.1*contador);
                    TiempoActual = TiempoActual + Cola[i].getRafaga();                                             // si la rafaga es mas pequeña que el quantum se suma solo la rafaga remanente y se trabaja con el siguente proceso con un quantum nuevo
                    Cola[i].setRafaga(0);
                    Cola[i].setTT(TiempoActual-inicio-0.1*contador);
                    Cola[i].setTiempoActual(TiempoActual-0.1*contador);
                    Registro.push_back(Cola[i]);
                
                if(Cola[i].getRafaga() <= 0) {                                                                 //Elimina elementos del queue en caso de que su rafaga sea menor a 0
                    cout<<"Tiempo de ejecucion completado: "<<Cola[i].getNombre()<<endl;
                    
                    Cola.erase(Cola.begin()+i);
                    
                }
            }
        }
        contador++;
        TiempoActual = TiempoActual + 0.1;       
    }
    MostrarVector(Registro);

}



void AsignadorDeCola(vector<Proceso> Cola,vector<Proceso> *RR1,vector<Proceso> *RR2,vector<Proceso> *FCFS){     //Toma los procesos de la cola principal y 
    float TiempoSistema = 0;
    float TiempoMaximo = mayorTiempo(Cola);
    while(TiempoSistema <= TiempoMaximo){
        for(int i=0;i<Cola.size();i++){
            if(Cola[i].getLlegada() <= TiempoSistema){
                int prioridad = Cola[i].getPrioridad();
                if(prioridad <= 2){                     //Toma los procesos de maximo prioridad 2
                    RR1->push_back(Cola[i]);
                    Cola.erase(Cola.begin()+i);
                }
                else{
                    if(prioridad <= 5){                //Toma los procesos mayores a 2 pero menores a 5
                        RR2->push_back(Cola[i]);
                        Cola.erase(Cola.begin()+i);
                    }
                    else{                               //Toma los procesos restantes
                       FCFS->push_back(Cola[i]);
                        Cola.erase(Cola.begin()+i);
                    }
                }
            }
        }
        TiempoSistema++;
    }
    
}


int main(){


    
    vector<Proceso> Cola,RR1,RR2,FCFS;         
    
    int q1=3,q2=8;
    Cola = CrearProcesos(10);
    AsignadorDeCola(Cola,&RR1,&RR2,&FCFS);
    cout<<"-.-.-.-.-RoundRobin Q=3-.-.-.-.-"<<endl;
    RoundRobin(RR1,q1);
    cout<<"-.-.-.-.-RoundRobin Q=8-.-.-.-.-"<<endl;
    RoundRobin(RR2,q2);
    cout<<"-.-.-.-.-FCFS Apropiativo-.-.-.-.-"<<endl;
    fcfs(FCFS); 
    

   
    return 0;
}
