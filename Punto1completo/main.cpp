#include <iostream>
#include <fstream>
#include <exception>

using namespace std;
void Creador(int t,char* array,ofstream* escritura){

    char letra = array[0];
    char letrenbloq [8]={};
    char nuevo[8]={};


    for(int i=0;i<=7;i++){
        int d;
        d = letra%2;

        letra = letra/2;
        if(d==0){
            letrenbloq[i]=48;
        }
        else if(d==1){

            letrenbloq[i]=49;
        }

    }

    for(int i=7;i>=0;i--){
        nuevo[i]=letrenbloq[7-i];
        cout<<nuevo[i];
    }
    escritura->write(nuevo,t);

}

void Convierte(ifstream* lectura,ofstream* escritura){

    int tambloqu=8;


    lectura->seekg(0,ios::end);
    int fino = lectura->tellg() - 1;

    lectura->seekg(0,ios::beg);
    char bloqueActua[100]={};
    int indicel=0;
    while(!lectura->eof()){

        lectura->read(bloqueActua,1);
        if(indicel>fino){
            break;
        }
        else{
            Creador(tambloqu,bloqueActua,escritura);
        }
    indicel=indicel+1;

    }

}
int getnum(char* array, int a){
    int contad = 0;
    for(int i=0;i<a;i++){
        if(array[i]-48==0){
            contad++;
        }
}
    return contad;
}

void Metodo1(ifstream* lecturaf,ofstream* escrituraf){
    cout<<"Ha escogido el metodo de codificacion numero 1"<<endl;
    int tambloque;
    cout<<"Ingrese el tamaño del bloque"<<endl;
    cin>>tambloque;

    lecturaf->seekg(0,ios::end);
    int fin = lecturaf->tellg() - 1;

    lecturaf->seekg(0,ios::beg);

    char bloqueanterior[100],bloqueactual[100],bloqueconvertido[100];

    int banbloq1=0;
    int indice=0;

    while(!lecturaf->eof()){
        lecturaf->read(bloqueactual,tambloque);
        for(int i=0;i<tambloque;i++){
            bloqueconvertido[i]=bloqueactual[i];
        }
        if(indice>=fin){
            break;
        }
        if(banbloq1==0){
            for(int i=0;i<tambloque;i++){
                if(bloqueactual[i]-48==0){
                    bloqueconvertido[i]=49;
                }
                else if(bloqueactual[i]-48==1){
                    cout<<"entro"<<endl;
                    bloqueconvertido[i]=48;
                }
            }
            banbloq1++;
        }

        else{
            int numeceros = getnum(bloqueanterior,tambloque);

            if((tambloque-numeceros)== numeceros){
                cout<<"MISMO NUMERO"<<endl;                                    //mismo numero de 0s y 1s
                for(int i=0;i<tambloque;i++){
                    if(bloqueactual[i]-48==0){
                        bloqueconvertido[i]=49;
                    }
                    else if(bloqueactual[i]-48==1){
                        bloqueconvertido[i]=48;
                    }
                }
            }
            else if(tambloque-numeceros>numeceros){
                cout<<"Mas unos"<<endl;
                for(int i=2;i<tambloque;i+=3){
                    if(bloqueactual[i]-48==0){
                        bloqueconvertido[i]=49;
                    }
                    else if(bloqueactual[i]-48==1){
                        bloqueconvertido[i]=48;
                    }
                }
            }
            else{

                 for(int i=1;i<tambloque;i+=2){
                    if(bloqueactual[i]-48==0){
                        bloqueconvertido[i]=49;
                            }
                    else if(bloqueactual[i]-48==1){
                        bloqueconvertido[i]=48;
                    }
                }

            }
        }
        if(lecturaf->eof() && indice<fin){
            escrituraf->write(bloqueconvertido,tambloque-indice);
        }
        else{
            escrituraf->write(bloqueconvertido,tambloque);
        }
        for(int i=0;i<tambloque;i++){
            bloqueanterior[i]=bloqueactual[i];
       }
        banbloq1++;
        indice=indice+tambloque;
    }
}
void Metodo2(ifstream* lecturaf,ofstream* escrituraf){
    cout<<"Ha escogido el metodo de codificacion numero 2"<<endl;
    int tambloque;
    cout<<"Ingrese el tamaño del bloque"<<endl;
    cin>>tambloque;

    lecturaf->seekg(0, ios::end);
    int final = (lecturaf->tellg())-1 ;

    lecturaf->seekg(0, ios::beg);

    char bloqueAnterior[100],bloqueActual[100],bloqueConvertido[100];

    int banbloq1=0;
    int indice=0;
    while(!lecturaf->eof()){


        while(!lecturaf->eof()){
            lecturaf->read(bloqueActual,tambloque);

            if(indice>=final){
                break;
            }

            if(lecturaf->eof() && indice<final){
                bloqueConvertido[0]=bloqueActual[final-indice-1];
                for(int i=1;i<final-indice;i++){
                  bloqueConvertido[i]=bloqueActual[i-1];
                }
                escrituraf->write(bloqueConvertido,final-indice);
            }
            else {
                bloqueConvertido[0]=bloqueActual[tambloque-1];
                for(int i=1;i<tambloque;i++){
                  bloqueConvertido[i]=bloqueActual[i-1];
                }
                escrituraf->write(bloqueConvertido,tambloque);
            }

            cout << "Actual: " << bloqueActual << endl;
            cout << "Convertido: " << bloqueConvertido << endl;

            for(int i=0;i<tambloque;i++){
                bloqueAnterior[i] = bloqueActual[i];
            }

            banbloq1++;
            indice = indice + tambloque;
        }
    }

    }



int main()
{

    int a;
    cout<<"Si su archivo de texto son binarios ingrese 1, sino ingrese 2: "<<endl;
    cin>>a;
    if(a==2){

        string archivoaconvertir, archivoacodificar;
        cout<<"Ingrese el nombre del archivo a converitr a Ascii "<<endl;
        cin>>archivoaconvertir;

        ifstream lectura;
        lectura.open(archivoaconvertir, ios::binary);
        if(lectura.fail()){
            cout<<"Error al abrir el archivo lectura\n"<<endl;
            return -1;
        }

        cout<<"Ingrese el nombre del archivo de salida: "<<endl;
        cin>>archivoacodificar;

        ofstream escritura;
        escritura.open(archivoacodificar);
        if(escritura.fail()){
            cout<<"Error al abrir el archivo escritura\n"<<endl;
            return -1;
        }

        int opcion;
        cout<<"Ingrese el numero del metodo que desea realizar: "<<endl;
        cin>>opcion;

        switch (opcion) {
        case 1:
            Convierte(&lectura,&escritura);
            break;

        default:
            cout<<"Opcion incorrecta: "<<endl;
            return -1;
        }

        lectura.close();
        escritura.close();

        string  archivocodificado;
        cout<<"El nombre del archivo a codificar es: "<<archivoacodificar<<endl;


        ifstream lecturaf;
        lecturaf.open(archivoacodificar, ios::binary);
        if(lecturaf.fail()){
            cout<<"Error al abrir el archivo lectura\n"<<endl;
            return -1;
        }

        cout<<"Ingrese el nombre del archivo codificado: "<<endl;
        cin>>archivocodificado;

        ofstream escrituraf;
        escrituraf.open(archivocodificado);
        if(escrituraf.fail()){
            cout<<"Error al abrir el archivo escritura\n"<<endl;
            return -1;
        }

        int opcion2;
        cout<<"Ingrese el numero del metodo que desea realizar: "<<endl;
        cin>>opcion2;

        switch (opcion2) {
        case 1:
            Metodo1(&lecturaf,&escrituraf);
            break;
        case 2:
            Metodo2(&lecturaf,&escrituraf);
            break;
        default:
            cout<<"Opcion incorrecta: "<<endl;
            return -1;
        }

        lecturaf.close();
        escrituraf.close();
    }
    else if(a==1){
        string archivoacodificar, archivocodificado;
        cout<<"Ingrese el nombre del archivo a codificar: "<<endl;
        cin>>archivoacodificar;

        ifstream lecturaf;
        lecturaf.open(archivoacodificar, ios::binary);
        if(lecturaf.fail()){
            cout<<"Error al abrir el archivo lectura\n"<<endl;
            return -1;
        }

        cout<<"Ingrese el nombre del archivo codificado: "<<endl;
        cin>>archivocodificado;

        ofstream escrituraf;
        escrituraf.open(archivocodificado);
        if(escrituraf.fail()){
            cout<<"Error al abrir el archivo escritura\n"<<endl;
            return -1;
        }

        int opcion;
        cout<<"Ingrese el numero del metodo que desea realizar: "<<endl;
        cin>>opcion;

        switch (opcion) {
        case 1:
            Metodo1(&lecturaf,&escrituraf);
            break;
        case 2:
            Metodo2(&lecturaf,&escrituraf);
            break;
        default:
            cout<<"Opcion incorrecta: "<<endl;
            return -1;
        }

        lecturaf.close();
        escrituraf.close();
    }
}



