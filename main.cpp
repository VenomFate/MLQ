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
    ~Proceso(){}

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
        procesoAux.setLlegada(rand()%10 * 0.1 + (rand()%10)+20);
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
    cout<<"Aqui";
    float tiempoSistema=0;
    
    float TiempoActual = menorTiempo(Cola);
    float inicio = menorTiempo(Cola);
    vector<Proceso> Registro;
    int contador=0;
    while(!Cola.empty()){
        for(int i=0 ; i < Cola.size();i++){
                
            if(Cola[i].getLlegada() <= TiempoActual){                                                           //si el proceso ya esta dentro del sistema entonces
                
                if(Cola[i].getRafaga() <= q){
                    
                    Cola[i].setWT(TiempoActual-inicio);
                    TiempoActual = TiempoActual + Cola[i].getRafaga();                                             // si la rafaga es mas pequeña que el quantum se suma solo la rafaga remanente y se trabaja con el siguente proceso con un quantum nuevo
                    Cola[i].setRafaga(0);
                    Cola[i].setTT(TiempoActual-inicio);
                    Cola[i].setTiempoActual(TiempoActual);
                    Registro.push_back(Cola[i]);
                    
                }
                else{
                    
                    Cola[i].setWT(TiempoActual- inicio);
                    TiempoActual = TiempoActual + q;
                    Cola[i].setRafaga(Cola[i].getRafaga() - q);
                    Cola[i].setTT(TiempoActual- inicio);
                    Cola[i].setTiempoActual(TiempoActual);
                    Registro.push_back(Cola[i]);
                    
                }
                    

                if(Cola[i].getRafaga() <= 0) {                                                                 //Elimina elementos del queue en caso de que su rafaga sea menor a 0
                    
                    Cola.erase(Cola.begin()+i);
                    
                }
                
            }
         
        
        }
        
        //contador++;
        //TiempoActual = TiempoActual + 0.1;       
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
                
                
                    Cola[i].setWT(TiempoActual-inicio);
                    TiempoActual = TiempoActual + Cola[i].getRafaga();                                             // si la rafaga es mas pequeña que el quantum se suma solo la rafaga remanente y se trabaja con el siguente proceso con un quantum nuevo
                    Cola[i].setRafaga(0);
                    Cola[i].setTT(TiempoActual-inicio);
                    Cola[i].setTiempoActual(TiempoActual);
                    Registro.push_back(Cola[i]);
                
                if(Cola[i].getRafaga() <= 0) {                                                                 //Elimina elementos del queue en caso de que su rafaga sea menor a 0

                    Cola.erase(Cola.begin()+i);
                    
                }
            }
        }    
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
void CrearProcesoManual (vector<Proceso> *Cola ,string nombre,int rafaga, int prioridad,float llegada){
        Proceso procesoAux;
        procesoAux.setNombre("Job " + nombre);
        procesoAux.setRafaga(rafaga);
        procesoAux.setRafagaInicial(rafaga);
        procesoAux.setPrioridad(prioridad);
        procesoAux.setLlegada(llegada);
        Cola->push_back(procesoAux);

}

int main(){


    
    vector<Proceso> Cola,RR1,RR2,FCFS;         
    
    int q1=3,q2=8;
    int opcion=0;
    //Cola = CrearProcesos(10);                       //Crea n Procesos de manera aleatoria
    //AsignadorDeCola(Cola,&RR1,&RR2,&FCFS);
    Cola.clear();
    int n;

    string nombre;
    int rafaga = 0;
    int prioridad = 0;
    float llegada = 0;

f1:
    cout << "-.-.-.-Menu-.-.-.-" << endl << "1) Agregar Proceso Manualmente" << endl << "2) Crear n Procesos aleatorios" << endl << "3) Ejecutar MLQ" << endl << "4)Mostrar Queue Actual" << endl<< "5)eliminar Queue" << endl<< "6)Salir"<< endl;
    cout << "Escriba por consola la opcion requerida:";
    cin >> opcion;
    cout << endl;
    switch(opcion){
        case 1:
            
            cout<<"Ingrese el nombre del proceso:";
            cin>>nombre; cout<<endl;
            cout<<"Ingrese la rafaga inicial del proceso:";
            cin>>rafaga;
            cout<<"Ingrese la prioridad del proceso:";
            cin>>prioridad;
            cout<<"Ingrese el tiempo de llegada del proceso(flotante):";
            cin>>llegada;
            CrearProcesoManual(&Cola,nombre,rafaga,prioridad,llegada);
            system("PAUSE");
            system("cls");
            goto f1;
        break;

        case 2:
            cout << "Ingrese la cantiada de procesos a ingresar:";
            cin >> n;
            Cola.clear();
            Cola = CrearProcesos(n);
            cout << endl << "Se borro la cola anterior y se crearon " << n <<" Procesos y se ingresaron en Queue"<< endl;
            system("PAUSE");
            system("cls");
            goto f1;
        break;

        case 3:
            AsignadorDeCola(Cola,&RR1,&RR2,&FCFS);
            if(!RR1.empty()){
                cout<<"-.-.-.-.-RoundRobin Q=3-.-.-.-.-"<<endl;
                RoundRobin(RR1,q1);
                RR1.clear();
            }
            else{
                cout<<"-.-.-.-.-RoundRobin Q=3 VACIO-.-.-.-.-"<<endl;
            }

            if(!RR2.empty()){
                cout<<"-.-.-.-.-RoundRobin Q=8-.-.-.-.-"<<endl;
                RoundRobin(RR2,q2);
                RR2.clear();
            }
            else{
                cout<<"-.-.-.-.-RoundRobin Q=8 VACIO-.-.-.-.-"<<endl;
            }
            if(!FCFS.empty()){
                cout<<"-.-.-.-.-FCFS Apropiativo-.-.-.-.-"<<endl;
                fcfs(FCFS);
                FCFS.clear();
            }
            else{
                cout<<"-.-.-.-.-FCFS Apropiativo VACIO-.-.-.-.-"<<endl;
            }
            


            system("PAUSE");
            system("cls");
            goto f1;
        break;

        case 4:
            MostrarVector(Cola);
            system("PAUSE");
            system("cls");
            goto f1;
        break;

        case 5:
            Cola.clear();
            cout<<"Se Limpio el Queue"<<endl;
            goto f1;
        break;

        case 6:

        break;
        default:
            cout<<endl<<"Ingrese una opcion valida"<<endl;
            system("PAUSE");
            system("cls");
            goto f1;
        break;

    }
    
    

   
    return 0;
}
