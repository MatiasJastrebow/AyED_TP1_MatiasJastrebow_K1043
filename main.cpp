#include <iostream>
#include <fstream>

using namespace std;

const int dclien {8};//numero de clientes
const int dprod {5};//numero de productos

void ordasc (float vdist [], int dprod, int vpos[])
{
    int pmin;
    for (int pos = 0; pos < dprod - 1; pos++){
        pmin = pos;
        for (int i = pos + 1; i < dprod; i++) {
            if (vdist[pmin] > vdist[i]) {
                pmin = i;
            }
        }
            if (pmin != pos) {
                swap (vdist[pos], vdist[pmin]);
                swap (vpos[pos], vpos[pmin]);
            }
    }
}

int main()
{

    string vnombres [dclien] {};//vector con los nombres de los clientes
    string vtipoprod [dprod] {};//vector con los tipos de productos
    float mpeso [dclien][dprod] {};//matriz de pesos por prodcuto, por clientes
    float mdist [dclien] [dprod]{};//matriz de distancia por producto, por cliente
    float vdist [dprod] {};//vector de distancias del cliente con mayor cantidad
    int vpos [dprod] {};//vector de posiciones de tipo de productos
    int ventregas [dprod] {};//vector de entregas por producto

    int entclie {};//numero de entregas del cliente con mayor cantidad (punto 2)
    int pmayor {};//posicion del mayor

    ifstream datos;
    datos.open("Datos.txt");
    if (!datos) {
        cout << "Error al abrir el archivo de datos" << endl;
        return 1;
    }
    int clien, prod;
    float peso, dist;
    while (datos >> clien >> prod >> peso >> dist) {
            mpeso [clien] [prod] += peso;
            mdist [clien] [prod] += dist;
            ventregas [prod]++;
    }
    datos.close();

    ifstream nombres;
    nombres.open("Nombres.txt");
    if (!nombres) {
        cout << "Error al abrir el archivo de nombres" << endl;
        return 1;
    }
    string pal;
    for (int i = 0; i < (dclien + dprod); ++i) {
            nombres >> pal;
            if (i < dclien) {
            vnombres [i] = pal;
            }
            else {
                vtipoprod [i - dclien] = pal;
                vpos [i - dclien] = (i - dclien);
            }

    }
    nombres.close();

    //Punto 1
    cout << "Listado de productos por cliente, que superan los 13000Kg:" << endl;
    for (int i = 0; i < dclien; ++i){
        cout << vnombres [i] << ": ";
        int auxe {};
        for (int j = 0; j < dprod; ++j) {
            if (mpeso [i] [j] > 13000){
                cout << vtipoprod[j] << ", ";
                auxe++;
            }
            if (auxe > entclie){
                entclie = auxe;
                pmayor = i;
            }
        }
        cout << endl;
    }
    cout << endl;

    //Punto 2
    for (int i = 0; i < dprod; ++i){
        vdist [i] = mdist [pmayor] [i];
        vpos [i] = i;
    }
    ordasc(vdist, dprod, vpos);
    cout << "Lista ascendente de kilometros recorridos, por producto del cliente " << vnombres[pmayor] << ":" << endl;
    for (int i = 0; i < dprod; ++i){
        cout << vtipoprod[vpos[i]] << "-" << vdist[i] << " Km" << endl;
    }
    cout << endl;

    //punto 3
    cout << "Cantidad de entregas de " << vtipoprod[vpos[dprod-1]] << ": ";
    cout <<  ventregas[vpos[dprod-1]] << endl;
    return 0;
}
