# include<iostream>
# include<cstdlib>
# include<ctime>
#include "rlutil.h"
#include <stdlib.h>
#include <conio.h>
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;

void menu2();
int menu(const char*titulo,const char *opciones[],int n);
void leerptos();
void guardasptos(int puntos,string nombre);
void uno();
void dos();
void tres();
void cuatro();
void cinco();
void seis();
void cartelfinal(int modo, int puntos1, string nombre1, int puntos2, string nombre2, int rondas, int gs1, int gs2);
void transicion(int ronda,int puntos1, string nombre1, string nombre2, int modo, int puntos2);
void Juego(string nombre1, int jug, string nombre2, string *nomptmax, int *rondptmax, int *puntsmax );
int Juego2(string nombre2, int ronda, int puntos);
int mayorpuntuacion (int gen, int poker, int full, int esca, int resto);
int FPuntajeResto(int VecDados[]);
int FEscalera(int VecDados[],int fprimera);
int FPoker (int VecDados[],int fprimera);
int FFull(int VecDados[],int fprimera);
int FGenerala(int VecDados[], int fprimera);
void TirarDadosAgain(int PP[], int aaa2, int FDados[] );
void tirarDados(int vecDados[], int otro);
void mostrarDados(int vecDados[], int tam);

int main(){
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);
    system("cls");
    menu2();
    return 0;
}

void Juego(string nombre1, int jug, string nombre2, string *nomptmax, int *rondptmax, int *puntsmax ){
    char rta;
    const int TAM=5;
    int i, dados[TAM], puntos1=0, puntos2=0, vecresp[5], resp, gs1, gs2;

    for(i=1;i<=10;i++){
    cout <<"    TURNO DE: " <<nombre1 <<"        |RONDA ", cout<<i         <<"          |        PUNTOS: " <<puntos1 <<endl;
    cout <<"    -------------------------------------------------------------------------" <<endl;
    cout <<endl;

    int puntostirada2=0,puntostirada1=0;
    bool primera=0;
    cout <<"    PRIMERA TIRADA."<<endl;
    cout <<"    ------------------------------------"<<endl;
    primera=1;
    cout <<endl;
    tirarDados(dados, TAM);
    mostrarDados(dados, TAM);
    cout <<endl;
    puntostirada1=mayorpuntuacion (FGenerala(dados,primera),FPoker(dados,primera),FFull(dados,primera),FEscalera(dados,primera),FPuntajeResto(dados));
    cout <<"    CONTINUAR TIRANDO? (S/N) : ";
    cin >> rta;
    while(rta != 'S' && rta != 'N'){
            cout <<"    Tenes que elegir s o n!" <<endl;
            cout <<"    CONTINUAR TIRANDO? (S/N) : ";
            cin >> rta;
        }

    if(rta=='S'){
    primera=0;
    TirarDadosAgain(vecresp ,resp ,dados);
    system("cls");
    cout <<"    TURNO DE: " <<nombre1 <<"        |RONDA ", cout<<i         <<"          |        PUNTOS: " <<puntos1 <<endl;
    cout <<"    -------------------------------------------------------------------------" <<endl;
    cout <<endl;

    cout <<"    SEGUNDA TIRADA." <<endl;
    cout <<"    ------------------------------------"<<endl;
    cout <<endl;

    mostrarDados(dados, TAM);
    cout <<endl;

    puntostirada1=mayorpuntuacion (FGenerala(dados,primera),FPoker(dados,primera),FFull(dados,primera),FEscalera(dados,primera),FPuntajeResto(dados));

    cout <<"    CONTINUAR TIRANDO? (S/N) : ";
    cin >> rta;
    while(rta != 'S' && rta != 'N'){
            cout <<"Tenes que elegir s o n!" <<endl;
            cout <<"CONTINUAR TIRANDO? (S/N) : ";
            cin >> rta;
        }

    if(rta=='S'){
    TirarDadosAgain(vecresp ,resp ,dados);
    system("cls");

    cout <<"    TURNO DE: " <<nombre1 <<"        |RONDA ", cout<<i         <<"          |        PUNTOS: " <<puntos1 <<endl;
    cout <<"    ------------------------------------------------------------" <<endl;
    cout <<endl;

    cout <<"    TERCERA Y ULTIMA TIRADA."<<endl;
    cout <<"    -----------------------------------"<<endl;
    cout <<endl;
    mostrarDados(dados, TAM);
    cout <<endl;
    puntostirada1=mayorpuntuacion(FGenerala(dados,primera),FPoker(dados,primera),FFull(dados,primera),FEscalera(dados,primera),FPuntajeResto(dados));
    cout <<"    LOGRASTE:" <<puntostirada1 <<" PUNTOS EN ESTE TURNO." <<endl;
    cout <<endl;
    system("pause");
    system("cls");
    }
    }
    puntos1+=puntostirada1;
    system("cls");

    if(puntostirada1==100 && jug==1){
        break;
    }

    if(i==10 && jug==1){
        break;
    }

    else{
    transicion(i, puntos1, nombre1, nombre2, jug, puntos2);
    }

    if(jug==2){
        puntostirada2=Juego2(nombre2, i, puntos2);
        puntos2+=puntostirada2;
        if(puntostirada1==100 && puntostirada2!=100){
            break;
        }
        else if(puntostirada1!=100 && puntostirada2==100){
            break;
        }
        else if(puntostirada1==100 && puntostirada2==100){
            gs1=puntostirada1;
            gs2=puntostirada2;
            break;
        }
        if(i==10){
            break;
        }
        else{
        transicion(i+1, puntos2, nombre2, nombre1, jug, puntos1);
        }
    }
    } //FIN DEL JUEGO

    cartelfinal(jug, puntos1, nombre1, puntos2, nombre2, i, gs1, gs2);
    system("cls");
    if(puntos2 < puntos1){
    if(i < *rondptmax){
        *rondptmax=i;
        *puntsmax=puntos1;
        *nomptmax=nombre1;
        }
    else if(puntos1 > *puntsmax){
        *rondptmax=i;
        *puntsmax=puntos1;
        *nomptmax=nombre1;
    }
    }
    else{
        if(i < *rondptmax){
        *rondptmax=i;
        *puntsmax=puntos2;
        *nomptmax=nombre2;
        }
        else if(puntos2 > *puntsmax){
        *rondptmax=i;
        *puntsmax=puntos2;
        *nomptmax=nombre2;
    }
    }
}

void TirarDadosAgain(int PP[], int resp, int FDados[] ){
        int i;
        cout <<endl;
        cout <<"    CUANTOS DADOS VOLVES A TIRAR? : ";
        cin >> resp;
        while (cin.fail()){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout <<endl;
        cout << "    OPCION INCORRECTA.\n";
        cout << "    CUANTOS DADOS VOLVES A TIRAR?: ";
        cin >> resp;
        }
        for(i=0;i<=(resp-1);i++){
            cout <<endl;
            cout <<"    CUAL?";
            cin >>PP[i];
            while (cin.fail()){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout <<endl;
            cout << "OPCION INCORRECTA.\n";
            cout << "CUAL?: ";
            cin >> PP[i];
            }
    }
        srand(time(NULL));
        for(i=0;i<resp;i++){
        FDados[(PP[i]-1)]=(rand()%6)+1;
        }
}
void tirarDados(int vecDados[], int tam){
    int i, correccion=0;
    if(correccion==0){
    srand(time(NULL));
    for(i=0;i<tam;i++){
       vecDados[i]=(rand()%6)+1;
     }
    }
    else{
        for(i=0;i<tam;i++){
        cout<<"Ingresar un dado: ";
        cin >>vecDados[i];
        }
    }
    }
void mostrarDados(int vecDados[], int   tam){

    int i;
    for(i=0;i<tam;i++){
        if(vecDados[i]==1){
           uno();
        }
        if(vecDados[i]==2){
            dos();
        }
        if(vecDados[i]==3){
            tres();
        }
        if(vecDados[i]==4){
            cuatro();
        }
        if(vecDados[i]==5){
            cinco();
        }
        if(vecDados[i]==6){
            seis();
        }
    }
    cout<<endl;
 }

int mayorpuntuacion (int gen, int poker, int full, int esca, int resto){
    int mayorpunt;
    if(gen>poker && gen>full && gen>esca){
     mayorpunt=gen;
     return mayorpunt;
    }
    else if(poker>full && poker>esca){
    mayorpunt=poker;
    return mayorpunt;
    }
    else if(full>esca){
    mayorpunt=full;
    return mayorpunt;
    }
    else if(esca>resto){
    mayorpunt=esca;
    return mayorpunt;
    }
    else{
    mayorpunt=resto;
      return mayorpunt;
    }
}

int FFull(int VecDados[],int fprimera){
    int i, uno=0,dos=0,tres=0,cuatro=0,cinco=0,seis=0,f=0, puntos=0;
    for(int i=0;i<5;i++){
    if(VecDados[i]==1)uno++;
    else if(VecDados[i]==2)dos++;
    else if(VecDados[i]==3)tres++;
    else if(VecDados[i]==4)cuatro++;
    else if(VecDados[i]==5)cinco++;
    else if(VecDados[i]==6)seis++;
    }
    if((uno==3 || dos==3 || tres==3 || cuatro==3 ||cinco==3 || seis==3) && (uno==2 || dos==2 || tres==2 || cuatro==2 ||cinco==2 || seis==2)){
        if (fprimera==1){
            puntos=60;
        }
        else{
            puntos=30;
        }
    }

    return puntos;
}
int FGenerala(int VecDados[], int fprimera){
    int iguales=0, puntos=0;
    for(int j=0;j<5;j++){
    if(VecDados[1]==VecDados[j]){
            iguales++;
        }
    }
    if(iguales==5){
        if(fprimera==1){
            puntos=100;
        }
        else{
            puntos=50;

        }
    }
return puntos;
}
int FPoker(int VecDados[],int fprimera){
    int i, uno=0,dos=0,tres=0,cuatro=0,cinco=0,seis=0, puntos=0;
    for(int i=0;i<5;i++){
    if(VecDados[i]==1)uno++;
    else if(VecDados[i]==2)dos++;
    else if(VecDados[i]==3)tres++;
    else if(VecDados[i]==4)cuatro++;
    else if(VecDados[i]==5)cinco++;
    else if(VecDados[i]==6)seis++;
    }
    if(uno==4 || dos==4 || tres==4 || cuatro==4 ||cinco==4 || seis==4){
        if (fprimera==1){
            puntos=80;
        }
        else{
            puntos=40;
        }
    }
    return puntos;
}
int FEscalera(int VecDados[],int fprimera){
    int mayor=0,esca=0, puntos=0;
    for(int x=0;x<6;x++){
        if(VecDados[x]==6){
            mayor++;
        }
    }
    if(mayor>=1){
        for(int j=2;j<=6;j++){
        for(int i=0;i<6;i++){
        if(VecDados[i]==j){
            esca++;
            break;
        }
    }
    }
    }
    else{
        for(int j=1;j<=5;j++){
        for(int i=0;i<6;i++){
        if(VecDados[i]==j){
            esca++;
            break;
        }
        }
        }
    }
    if(esca==5){
        if(fprimera==1){
            puntos=50;
        }
        else{
            puntos=25;
        }
    }
    return puntos;
}
int FPuntajeResto(int VecDados[]){
    int uno=0,dos=0,tres=0,cuatro=0,cinco=0,seis=0, puntos=0;
     for(int i=0;i<5;i++){
        if(VecDados[i]==1)uno++;
        else if(VecDados[i]==2)dos+=VecDados[i];
        else if(VecDados[i]==3)tres+=VecDados[i];
        else if(VecDados[i]==4)cuatro+=VecDados[i];
        else if(VecDados[i]==5)cinco+=VecDados[i];
        else if(VecDados[i]==6)seis+=VecDados[i];
}
    if(seis>cinco && seis>cuatro && seis>tres && seis>dos && seis>uno ){
        puntos=seis;
    }
    else if(cinco>cuatro && cinco>tres && cinco>dos && cinco>uno){
        puntos=cinco;
    }
    else if(cuatro>tres && cuatro>dos && cuatro>uno){
        puntos=cuatro;
    }
    else if(tres>dos && tres>uno){
        puntos=tres;
    }
    else if(dos>uno){
        puntos=dos;
    }
    else{
        puntos=uno;
    }
    return puntos;
    }


int menu(const char*titulo,const char *opciones[],int n){
    system("color 1f");
    int opcion_seleccionada = 1;
    int tecla;
    bool repite=true;
    do{
        system("cls");

        gotoxy(5,3+opcion_seleccionada);cout<<"==>";

        //imprime titulo
        gotoxy(25,3);cout<<titulo;
        //imprime opciones
        for(int i=0;i<n;i++){
        gotoxy(10,4+i);cout<<i+1<<")"<<opciones[i];
        }
        do{
            tecla = getch();
        }
        while(tecla!=TECLA_ARRIBA&&tecla!=TECLA_ABAJO&&tecla!=ENTER);

        switch(tecla)
        {
        case TECLA_ARRIBA:
            opcion_seleccionada--;
            if(opcion_seleccionada==0){
                opcion_seleccionada=n;
            }
            break;
        case TECLA_ABAJO:
            opcion_seleccionada++;
            if(opcion_seleccionada==n+1){
                opcion_seleccionada=1;
            }
            break;
        case ENTER:
            repite=false;
            break;
        }
        }
    while(repite);

    return opcion_seleccionada;
}

void menu2() {
const char *titulo="GENERALA";
const char *opciones[]={"1 Jugador","2 Jugadores","Puntuacion mas alta","Salir"};
int n=4;
bool repite=true;
int opcion;
char palabra[]="nadie";
string nomptmax=palabra;
int rondptmax=0, puntsmax=0;

do{
   system("cls");
   opcion=menu(titulo,opciones,n);

   switch(opcion)
   {
    case 1:{
    int puntaje;
    string nombre, nombre2;
    system("cls");
    cout <<"    BIENVENIDO AL MODO DE UN JUGADOR! "<<endl;
    cout <<endl;
    cout <<"    NOMBRE DEL JUGADOR: ";
    cin >>nombre;
    system("cls");
    Juego(nombre, opcion, nombre2, &nomptmax, &rondptmax, &puntsmax );
    system ("cls");
    }
        break;
    case 2:{
    int puntaje;
    string nombre, nombre2;
    system("cls");
    cout <<"    BIENVENIDO AL MODO DE 2 JUGADORES! "<<endl;
    cout <<endl;
    cout <<"    NOMBRE DEL JUGADOR UNO: ";
    cin >>nombre;
    cout <<endl;
    cout <<"    NOMBRE DEL JUGADOR DOS: ";
    cin >>nombre2;
    system("cls");
    Juego(nombre, opcion, nombre2, &nomptmax, &rondptmax, &puntsmax );
    system ("cls");
    }
        break;
    case 3:
        system("cls");
        cout <<nomptmax <<" gano en " <<rondptmax <<" rondas con " <<puntsmax <<" puntos.";
        rlutil::anykey();
        break;
    case 4:repite=false;
        break;
   }
   }
while(repite);

}

int Juego2(string nombre2, int ronda, int puntos){
    char rta;
    const int TAM=5;
    int i, dados[TAM], puntos2=0, vecresp[5], resp;

        cout <<"    TURNO DE: " <<nombre2 <<"        |RONDA ", cout<<ronda         <<"          |        PUNTOS: " <<puntos <<endl;
        cout <<"    -------------------------------------------------------------------------" <<endl;
        cout <<endl;

    int puntostirada2=0;
    bool primera=0;
    cout <<"    PRIMERA TIRADA."<<endl;
    cout <<"    -----------------------------------"<<endl;
    primera=1;
    cout <<endl;
    tirarDados(dados, TAM);
    mostrarDados(dados, TAM);
    cout <<endl;
    puntostirada2=mayorpuntuacion (FGenerala(dados,primera),FPoker(dados,primera),FFull(dados,primera),FEscalera(dados,primera),FPuntajeResto(dados));
    cout <<"    CONTINUAR TIRANDO? (S/N) : ";
    cin >> rta;
    while(rta != 'S' && rta != 'N'){
            cout <<"Tenes que elegir s o n!" <<endl;
            cout <<"CONTINUAR TIRANDO? (S/N) : ";
            cin >> rta;
        }


    if(rta=='S'){
    primera=0;
    TirarDadosAgain(vecresp ,resp ,dados);
    system("cls");
    cout <<"    TURNO DE: " <<nombre2 <<"        |RONDA ", cout<<ronda         <<"          |        PUNTOS: " <<puntos <<endl;
    cout <<"-------------------------------------------------------------------------" <<endl;
    cout <<endl;
    cout <<"    SEGUNDA TIRADA." <<endl;
    cout <<"    -----------------------------------"<<endl;
    cout <<endl;

    mostrarDados(dados, TAM);
    cout <<endl;
    puntostirada2=mayorpuntuacion (FGenerala(dados,primera),FPoker(dados,primera),FFull(dados,primera),FEscalera(dados,primera),FPuntajeResto(dados));

    cout <<"    CONTINUAR TIRANDO? (S/N) : ";
    cin >> rta;
    while(rta != 'S' && rta != 'N'){
            cout <<"Tenes que elegir s o n!" <<endl;
            cout <<"CONTINUAR TIRANDO? (S/N) : ";
            cin >> rta;
        }

    if(rta=='S'){
    TirarDadosAgain(vecresp ,resp ,dados);
    system("cls");

    cout <<"    TURNO DE: " <<nombre2 <<"        |RONDA ", cout<<ronda         <<"          |        PUNTOS: " <<puntos <<endl;
    cout <<"    -------------------------------------------------------------------------" <<endl;
    cout <<endl;
    cout <<"    TERCERA Y ULTIMA TIRADA."<<endl;
    cout <<"    -----------------------------------"<<endl;
    cout <<endl;
    mostrarDados(dados, TAM);
    cout <<endl;
    puntostirada2=mayorpuntuacion (FGenerala(dados,primera),FPoker(dados,primera),FFull(dados,primera),FEscalera(dados,primera),FPuntajeResto(dados));
    cout <<"    LOGRASTE:" <<puntostirada2 <<" PUNTOS EN ESTE TURNO." <<endl;
    cout <<endl;
    system("pause");
    system("cls");
    }
    }
    puntos2+=puntostirada2;
    system("cls");


    return puntos2;
    }

void transicion(int ronda,int puntos1, string nombre1, string nombre2, int modo, int puntos2){
        system("cls");
        if(modo==1){
        for(int i=80;i<=117;i++){
        gotoxy(i,4);
        cout <<"_";
        }
        for(int i=5;i<=13;i++){
            gotoxy(80,i);
            cout <<"|";
        }
        for(int i=5;i<=13;i++){
            gotoxy(117,i);
            cout<<"|";
        }
        for(int i=81;i<=116;i++){
            gotoxy(i,13);
            cout <<"_";
        }
        gotoxy(95,7);
        cout <<"RONDA: " <<ronda;
        gotoxy(92,10);
        cout<<"PUNTOS DE " <<nombre1 <<": " <<puntos1;
    }
    else{
        for(int i=80;i<=117;i++){
        gotoxy(i,4);
        cout <<"_";
        }
        for(int i=5;i<=13;i++){
            gotoxy(80,i);
            cout <<"|";
        }
        for(int i=5;i<=13;i++){
            gotoxy(117,i);
            cout<<"|";
        }
        for(int i=81;i<=116;i++){
            gotoxy(i,13);
            cout <<"_";
        }
        gotoxy(95,7);
        cout <<"RONDA: " <<ronda;
        gotoxy(90,6);
        cout <<"PROXIMO TURNO DE: " <<nombre2;
        gotoxy(92,10);
        cout<<"PUNTOS DE " <<nombre1 <<": " <<puntos1;
        gotoxy(92,11);
        cout<<"PUNTOS DE " <<nombre2 <<": " <<puntos2;
    }
        rlutil::anykey();
        system("cls");
    }

void cartelfinal(int modo, int puntos1, string nombre1, int puntos2, string nombre2, int rondas, int gs1, int gs2){
    if(modo==1){
    for(int i=81;i<=129;i++){
        gotoxy(i,4);
        cout <<"_";
        }
        for(int i=5;i<=13;i++){
            gotoxy(80,i);
            cout <<"|";
        }
        for(int i=5;i<=13;i++){
            gotoxy(130,i);
            cout<<"|";
        }
        for(int i=81;i<=129;i++){
            gotoxy(i,13);
            cout <<"_";
        }
    gotoxy(94,7);
    cout <<"FELICIDADES " <<nombre1 <<" !";
    gotoxy(92,10);
    cout<<"LOGRASTE " <<puntos1 <<" PUNTOS EN " <<rondas <<" RONDAS";
}
    else{
        for(int i=81;i<=129;i++){
        gotoxy(i,4);
        cout <<"_";
        }
        for(int i=5;i<=13;i++){
            gotoxy(80,i);
            cout <<"|";
        }
        for(int i=5;i<=13;i++){
            gotoxy(130,i);
            cout<<"|";
        }
        for(int i=81;i<=129;i++){
            gotoxy(i,13);
            cout <<"_";
        }
        if(puntos1>puntos2){
        gotoxy(95,7);
        cout <<"FELICIDADES ";
        gotoxy(107,7);
        cout <<nombre1 <<", GANASTE !!";
        gotoxy(95,9);
        cout <<"LOGRASTE " <<puntos1 <<" PUNTOS EN "<<rondas <<" RONDAS";
        }
        else if(puntos2>puntos1){
        gotoxy(95,7);
        cout <<"FELICIDADES ";
        gotoxy(107,7);
        cout <<nombre2 <<", GANASTE !!";
        gotoxy(95,9);
        cout <<"LOGRASTE " <<puntos2 <<" PUNTOS EN "<<rondas <<" RONDAS";
        }
        else if(gs1==100 && gs2==100){
            gotoxy(103,7);
            cout<<"EMPATE !";
            gotoxy(95,8);
            cout <<nombre1 <<" Y " <<nombre2 <<" LOGRARON UN EMPATE!";
            gotoxy(84,9);
            cout <<"AMBOS LOGRARON GENERALA SERVIDA EN LA RONDA "<<rondas;
        }
        else{
            gotoxy(103,7);
            cout<<"EMPATE !";
            gotoxy(96,8);
            cout <<nombre1 <<" Y " <<nombre2 <<" LOGRARON UN EMPATE!";
            gotoxy(90,9);
            cout <<"LOGRARON " <<puntos1 <<" PUNTOS EN 10 RONDAS";

        }
}
    rlutil::anykey();
}

void uno(){
    cout<<"     ___________"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |    O    |"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |_________|"<<endl;

}
void dos(){
    cout<<"     ___________"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |  O      |"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |      O  |"<<endl;
    cout<<"     |_________|"<<endl;

}
void tres(){
    cout<<"     ___________"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |  O      |"<<endl;
    cout<<"     |    O    |"<<endl;
    cout<<"     |      O  |"<<endl;
    cout<<"     |_________|"<<endl;

}
void cuatro(){
    cout<<"     ___________"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |_________|"<<endl;
}
void cinco(){
    cout<<"     ___________"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |    O    |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |_________|"<<endl;
}
void seis (){
    cout<<"     ___________"<<endl;
    cout<<"     |         |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |  O   O  |"<<endl;
    cout<<"     |_________|"<<endl;
}
