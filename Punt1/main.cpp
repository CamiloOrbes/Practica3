#include <iostream>
#include <fstream>
#include <exception>
using namespace std;

int getnum(char* array, int a){
    int contad = 0;
    for(int i=0;i<a;i++){
        if(array[i]-48==0){
            contad++;
        }
}
    return contad;
}

void Metodo1(ifstream* lectura,ofstream* escritura){
    cout<<"Ha escogido el metodo de codificacion numero 1"<<endl;
    int tambloque;
    cout<<"Ingrese el tamaño del bloque"<<endl;
    cin>>tambloque;

    lectura->seekg(0,ios::end);
    int fin = lectura->tellg() - 1;

    lectura->seekg(0,ios::beg);

    char bloqueanterior[100],bloqueactual[100],bloqueconvertido[100];

    int banbloq1=0;
    int indice=0;

    while(!lectura->eof()){
        lectura->read(bloqueactual,tambloque);
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
        if(lectura->eof() && indice<fin){
            escritura->write(bloqueconvertido,tambloque-indice);
        }
        else{
            escritura->write(bloqueconvertido,tambloque);
        }
        for(int i=0;i<tambloque;i++){
            bloqueanterior[i]=bloqueactual[i];
       }
        banbloq1++;
        indice=indice+tambloque;
    }
}
void Metodo2(ifstream* lectura,ofstream* escritura){
    cout<<"Ha escogido el metodo de codificacion numero 2"<<endl;
    int tambloque;
    cout<<"Ingrese el tamaño del bloque"<<endl;
    cin>>tambloque;

    lectura->seekg(0, ios::end);
    int final = (lectura->tellg())-1 ;

    lectura->seekg(0, ios::beg);

    char bloqueAnterior[100],bloqueActual[100],bloqueConvertido[100];

    int banbloq1=0;
    int indice=0;
    while(!lectura->eof()){


        while(!lectura->eof()){
            lectura->read(bloqueActual,tambloque);

            if(indice>=final){
                break;
            }

            if(lectura->eof() && indice<final){
                bloqueConvertido[0]=bloqueActual[final-indice-1];
                for(int i=1;i<final-indice;i++){
                  bloqueConvertido[i]=bloqueActual[i-1];
                }
                escritura->write(bloqueConvertido,final-indice);
            }
            else {
                bloqueConvertido[0]=bloqueActual[tambloque-1];
                for(int i=1;i<tambloque;i++){
                  bloqueConvertido[i]=bloqueActual[i-1];
                }
                escritura->write(bloqueConvertido,tambloque);
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
    string archivoacodificar, archivocodificado;
    cout<<"Ingrese el nombre del archivo a codificar: "<<endl;
    cin>>archivoacodificar;

    ifstream lectura;
    lectura.open(archivoacodificar, ios::binary);
    if(lectura.fail()){
        cout<<"Error al abrir el archivo lectura\n"<<endl;
        return -1;
    }

    cout<<"Ingrese el nombre del archivo codificado: "<<endl;
    cin>>archivocodificado;

    ofstream escritura;
    escritura.open(archivocodificado);
    if(escritura.fail()){
        cout<<"Error al abrir el archivo escritura\n"<<endl;
        return -1;
    }

    int opcion;
    cout<<"Ingrese el numero del metodo que desea realizar: "<<endl;
    cin>>opcion;

    switch (opcion) {
    case 1:
        Metodo1(&lectura,&escritura);
        break;
    case 2:
        Metodo2(&lectura,&escritura);
        break;
    default:
        cout<<"Opcion incorrecta: "<<endl;
        return -1;
    }

    lectura.close();
    escritura.close();

}

