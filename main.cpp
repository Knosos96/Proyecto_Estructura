#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

///////////////////////////////////////////////////

/////////////////////////STRUCTS DEL PROGRAMA///////////
struct ventas {
	string cod;
	string nom_cli;
	string nom_pro;
	int cantidad;
	float precioUnit;
	float precioTotal;
	ventas* sig;
};
typedef struct ventas Ventas;

struct nodoArbol3{
    Ventas * sell;
    nodoArbol3 *izq,*der;
};
typedef struct nodoArbol3 NodoArbol3;

struct insumo{
	int cod_in;
	string nom_in;
	string cat_in;
	string imag_in;
	float precio_in;
};
typedef struct insumo Insumo;

//ESTRUCTURA ARBOL INSUMOS
struct  nodoArbol {
    Insumo * info; 
    nodoArbol * izq, * der;
};
typedef struct nodoArbol NodoArbol;

struct Cliente {
	int cod_cl;
	string nom_cl;
	string ape_cl;
	string dni_cl;
	string tel_cl;
};

struct nodoArbol1{
    Cliente *info;
    nodoArbol1 *izq;
    nodoArbol1 *der;
};

struct nodo{
       string dato;        
       struct nodo *next;
};
typedef struct nodo *ListaEn;

/////////////////////////////////////////////////////////////////////////

void insertarInicio(ListaEn &lista, string valor){
     ListaEn lista1;
     lista1 = new(struct nodo);
     lista1->dato = valor;
     lista1->next = lista;
     lista  = lista1;
}

void insertarFinal(ListaEn &lista, string valor){
    ListaEn t, q = new(struct nodo);
 
    q->dato  = valor;
    q->next = NULL;
 
    if(lista==NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while(t->next!=NULL)
        {
            t = t->next;
        }
        t->next = q;
    }

}

int insertarAntesDespues(){
    int op, band;
    cout<<endl;
    cout<<"\t 1. Antes de la posicion           "<<endl;
    cout<<"\t 2. Despues de la posicion         "<<endl;
 
    cout<<"\n\t Opcion : "; cin>> op;
 
    if(op==1)
        band = -1;
    else
        band = 0;
 
    return band;
}

void insertarElemento(ListaEn &lista, string valor, int pos){
  
    ListaEn q, t;
    int i;
    q = new(struct nodo);
    q->dato = valor;
 
    if(pos==1)
    {
        q->next = lista;
        lista = q;
    }
    else
    {
        int x = insertarAntesDespues();
        t = lista;
 
        for(i=1; t!=NULL; i++)
        {
            if(i==pos+x)
            {
                q->next = t->next;
                t->next = q;
                return;
            }
            t = t->next;
        }
    }
    cout<<"   Error...Posicion no encontrada..!"<<endl;
}

string buscarElemento(ListaEn lista, string valor){
    
    ListaEn q = lista;
    int i = 1, busc = 0;
 
    while(q!=NULL)
    {
        if(q->dato==valor)
        {
            cout<<endl<<" Encontrada en posicion "<< i <<endl;
            busc = 1;
            return q->dato;
        }
        q = q->next;
        i++;
    }
 
    if(busc==0)
        cout<<"\n\n Numero no encontrado..!"<< endl;
}

void ImprimirLista(ListaEn lista){

  int i = 0;
 
     while(lista != NULL)
     {
          cout <<' '<< i+1 <<") " << lista->dato << endl;
          lista = lista->next;
          i++;
     }
}

void eliminarElemento(ListaEn &lista, string valor)
{
    ListaEn p, ant;
    p = lista;
 
    if(lista!=NULL)
    {
        while(p!=NULL)
        {
            if(p->dato==valor)
            {
                if(p==lista)
                    lista = lista->next;
                else
                    ant->next = p->next;
 
                delete(p);
                return;
            }
            ant = p;
            p = p->next;
        }
    }
    else
        cout<<" Lista vacia..!";
}

/////////////////////////////////////////////////////////////////////////////
///////////////////////////clientes//////////////////////////////////////////////////
Cliente* crearCliente(int cod, string nom, string ape, string dni, string tel){
    Cliente* c = (Cliente*)malloc(sizeof(Cliente));
    c->cod_cl=cod;
    c->nom_cl=nom;
    c->ape_cl=ape;
    c->dni_cl=dni;
    c->tel_cl=tel;
    
    return c;
}
nodoArbol1* crearArbol(Cliente *c, nodoArbol1* i, nodoArbol1* d){
    nodoArbol1 * a = (nodoArbol1*)malloc(sizeof(nodoArbol1));
    a->info = c;
    a->izq = i;
    a->der = d;
    
    return a;
}
void mostrarCliente(Cliente* t){
    if (t != NULL){
        cout<<"--------------------------"<<endl;
        cout<<"Codigo: "<<t->cod_cl<<endl;
        cout<<"Nombre: "<<t->nom_cl<<endl;
        cout<<"Apellido: "<<t->ape_cl<<endl;
        cout<<"DNI: "<<t->dni_cl<<endl;
        cout<<"Telefono: "<<t->tel_cl<<endl;
        cout<<"--------------------------";
    }
}
void mostrarArbol(nodoArbol1 *a){
    if (a != NULL){
        mostrarCliente(a->info);
        mostrarArbol(a->izq);
        mostrarArbol(a->der);
    }
}
Cliente* buscarCliente(nodoArbol1 *a, string b){
    if (a == NULL){
        cout<<"No existe el cliente"<<endl;
        return 0;
    }
    else if (b.compare(a->info->nom_cl) == 0)
        return a->info;
    else if (b.compare(a->info->nom_cl) > 0)
        return(buscarCliente(a->der, b));
    else
        return(buscarCliente(a->izq, b));
}
nodoArbol1* eliminarCliente(nodoArbol1* a,Cliente* c){
    nodoArbol1 *t,*f;
    if (a == NULL)
        return NULL;
    else if (c->nom_cl.compare(a->info->nom_cl) < 0)
        a->izq = eliminarCliente(a->izq, c);
    else if (c->nom_cl.compare(a->info->nom_cl) > 0)   
        a->der = eliminarCliente(a->der, c);
    else{
        if (a->izq == NULL && a->der == NULL){
            free(a);  a = NULL;   
        }
        else if (a->izq == NULL){
            t = a; 
            a = a->der;   
            free(t);   
        }
        else if (a->der == NULL) {
            t = a;   
            a = a->izq;   
            free (t);
        }
        else {
            f = a->izq;   
            while (f->der != NULL)   
            {
                f = f->der;   
            }
            a->info = f->info;   
            f->info = c;   
            a->izq = eliminarCliente(a->izq, c);   
        }
        
    }
    return a;
      
}


///////////////////////////////////////////////////////////////////////
///////////////////////////INSUMOS//////////////////////////////////////////////////
Insumo* crearInsumo(int codIn, string nombIn, string catIn, string imagIn, float precioIn){
    Insumo* i= (Insumo*)malloc(sizeof(Insumo));
    i->cod_in = codIn;
    i->nom_in = nombIn;
    i->cat_in = catIn;
    i->imag_in = imagIn;
    i->precio_in = precioIn;
    return i;
}
//IMPRIMIR INSUMOS
void imprimirInsumo(Insumo* t){
    if (t != NULL){
        printf("\n----------------------------------");
        printf("\nCodigo: %i ", t->cod_in); 
        cout<<"\nNombre: "<<t->nom_in;
        cout<<"\nDescripcion: "<<t->cat_in;
        cout<<"\nPresentacion: "<<t->imag_in;
        printf("\nPrecio: %.2f ", t->precio_in);
        printf("\n----------------------------------");
    }
}

NodoArbol* crearArbol(Insumo* t, NodoArbol* i, NodoArbol* d){
    NodoArbol * a = (NodoArbol*)malloc(sizeof(NodoArbol));
    a->info = t;
    a->izq = i;
    a->der = d;
    return a;
}
//IMPRIMIR ARBOL DE INSUMOS
void imprimirArbol(NodoArbol* n){
    if (n != NULL){
        imprimirInsumo(n->info);
        imprimirArbol(n->izq); 
        imprimirArbol(n->der);
    }
}
//METODO BUSCAR
Insumo * buscar(NodoArbol * a , int s){
    if (a == NULL){
        cout<<"es nulo\n";
        return NULL;
    }
    else if (a->info->cod_in > s)   
        return(buscar(a->izq, s)); 
    else if (a->info->cod_in < s)   
        return(buscar(a->der, s));   
    else 
        return a->info;
}
//METODO INSERTAR
NodoArbol* insertarInsumo(NodoArbol* nodo, Insumo* t){
    if (nodo == NULL)  {
        nodo = (NodoArbol*)malloc(sizeof(NodoArbol));   
        nodo->info = t;   
        nodo->izq = NULL;   
        nodo->der = NULL;   
    }
    else if (t->cod_in < nodo->info->cod_in)   
        nodo->izq = insertarInsumo(nodo->izq, t);   
    else if(t->cod_in > nodo->info->cod_in)   
        nodo->der = insertarInsumo(nodo->der, t); 
 return nodo;
}
//METODO RETIRAR
NodoArbol* retirarInsumo(NodoArbol* r, Insumo* v){
    NodoArbol *t, *f;   
    if (r == NULL)   
        return NULL;   
    else if (r->info->cod_in > v->cod_in)   
        r->izq = retirarInsumo(r->izq, v);   
    else if (r->info->cod_in < v->cod_in)   
        r->der = retirarInsumo(r->der, v);   
    else { // encontro el nodo a retirar
        if (r->izq == NULL && r->der == NULL){
            free(r);  r = NULL;   
        }
        else if (r->izq == NULL){
            t = r; 
            r = r->der;   
            free(t);   
        }
        else if (r->der == NULL) {
            t = r;   
            r = r->izq;   
            free (t);
        }
        else {
            f = r->izq;   
            while (f->der != NULL)   
            {
                f = f->der;   
            }
            r->info = f->info;   
            f->info = v;   
            r->izq = retirarInsumo(r->izq, v);   
        }
    }
    return r;
}
void listarInsumos(){
  int opt=0;
  string categoria;
  do{
    cout<<"Ingrese la categoria que desea listar: "; cin>>categoria;
    if()
  }while(opt != 0);
}
void buscarInsumo(){
  
}
void eliminarInsumo(){
  
}

//////////////////////////////////////////////////////////////////
///////////////////////////VENTAS//////////////////////////////////////////////////
Ventas* crearVentas(string cod,string nom_cli,string nom_pro,int cantidad,float precioUnit,float precioTotal){
    
    Ventas* node=(Ventas*)malloc(sizeof(Ventas));
    node->cod=cod;
    node->nom_cli=nom_cli;
    node->nom_pro=nom_pro;
    node->cantidad=cantidad;
    node->precioUnit=precioUnit;
    node->precioTotal=precioTotal;
    return node;
}
/////////////////////////////////
void imprimirVentas(Ventas *venta){
    if(venta!=NULL){
        cout<<"\n"<<"------------------------";
        cout<<"\n"<<"Codigo:"<<venta->cod;
        cout<<"\n"<<"Nombre del Cliente:"<<venta->nom_cli;
        cout<<"\n"<<"Nombre del Producto:"<<venta->nom_pro;
        cout<<"\n"<<"Cantidad:"<<venta->cantidad;
        cout<<"\n"<<"Precio de Unidad:"<<venta->precioUnit;
        cout<<"\n"<<"Precio Total:"<<venta->precioTotal;
    }
    
}
///////////////////////////////////////////////////////////

NodoArbol3 *crearArbol(Ventas* ventas,NodoArbol3 *izq,NodoArbol3 *der){
    
    NodoArbol3 * c = (NodoArbol3*)malloc(sizeof(NodoArbol3));
    c->sell=ventas;
    c->izq=izq;
    c->der=der;
    return c;
}
//////////////////////////////////////////////////////////////
void ImprimirArbol(NodoArbol3 *n){
    if(n!=NULL){
        imprimirVentas(n->sell);
        ImprimirArbol(n->izq);
        ImprimirArbol(n->der);
    }
}
/////////////////////////////////////////////////////////////
Ventas *Buscar(NodoArbol3 *n,string s){
    
    if (n == NULL){
        cout<<"No hay Venta\n";
        return NULL;
    }
    else if(s.compare(n->sell->cod)==0)
        return n->sell;
    else if(s.compare(n->sell->cod)>0)
        return (Buscar(n->der,s));
    else 
        return (Buscar(n->izq,s));
}
/////////////////////////////////////////////////////////////
NodoArbol3 *Insertar(NodoArbol3 * nodo, Ventas* n){
    if(nodo==NULL){
        nodo=(NodoArbol3*)malloc(sizeof(NodoArbol3));
        nodo->sell=n;
        nodo->izq=NULL;
        nodo->der=NULL;
    }
    else if(n->cod.compare(nodo->sell->cod)<0)
        nodo->izq=Insertar(nodo->izq,n);
    else if(n->cod.compare(nodo->sell->cod)>0)
        nodo->der=Insertar(nodo->der,n);
    return nodo;
    
}
//////////////////////////////////////////////////////////////

NodoArbol3 *retirar(NodoArbol3 *nodo, Ventas* v){
    NodoArbol3 *nodo1,*nodo2;
    
    if(nodo==NULL)
        return NULL;
    else if(v->cod.compare(nodo->sell->cod)<0)
        nodo->izq=retirar(nodo->izq,v);
    else if(v->cod.compare(nodo->sell->cod)>0)
        nodo->der=retirar(nodo->der,v);
        
    else{
        if(nodo->izq==NULL && nodo->der==NULL){
            free(nodo);
            nodo=NULL;
        }
        else if(nodo->izq==NULL){
           nodo1=nodo;
           nodo=nodo->der;
           free(nodo1);
        }
        else if(nodo->der==NULL){
            nodo1=nodo;
           nodo=nodo->der;
           free(nodo1);
        }
        else{
            nodo2=nodo->izq;
            while(nodo2->der!=NULL){
                nodo2=nodo2->der;
            }
            nodo->sell=nodo2->sell;
            nodo2->sell=v;
            nodo->izq=retirar(nodo->izq,v);
        }
    }
    return nodo;
}

/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/////////////////////////LEER ARCHIVOS//////////////////////////////
void AlmacenarArchivo(ListaEn &lista,ListaEn &lista1){

  
   ifstream archivo("Insumos.csv");
   ifstream archivo1("Clientes.csv");
   string linea,linea1;
   char delimitador=',';
  
   getline(archivo,linea);
   getline(archivo1,linea1);
  
   while(getline(archivo,linea)){
    stringstream stream(linea); // Convertir la cadena a un stream
        string CODIGO,NOMBRES,CATEGORIAS,IMAGENES,PRECIOS;
     
        // Extraer todos los valores de esa fila
        getline(stream, CODIGO, delimitador);
        getline(stream, NOMBRES, delimitador);
        getline(stream, CATEGORIAS, delimitador);
        getline(stream, IMAGENES, delimitador);
        getline(stream, PRECIOS, delimitador);

        insertarInicio(lista, CODIGO);
        insertarInicio(lista, NOMBRES);
        insertarInicio(lista, CATEGORIAS);
        insertarInicio(lista, IMAGENES);
        insertarInicio(lista,PRECIOS);
     
        // Imprimir
        //cout << "==================================" << endl;
        //cout << " CODIGO: " << CODIGO << endl;
        //cout << " NOMBRE: " << NOMBRES << endl;
        //cout << " CATEGORIA: " << CATEGORIAS << endl;
        //cout << " IMAGEN DE VENTA: " << IMAGENES << endl;
        //cout << " Precio de venta: " << PRECIOS << endl;
   }
  
   while(getline(archivo1,linea1)){
     stringstream stream(linea1); // Convertir la cadena a un stream
        string codigo,nombre,apellido,dni,telefono;
     
        // Extraer todos los valores de esa fila
        getline(stream, codigo, delimitador);
        getline(stream, nombre, delimitador);
        getline(stream, apellido, delimitador);
        getline(stream, dni, delimitador);
        getline(stream, telefono, delimitador);

        insertarInicio(lista1, codigo);
        insertarInicio(lista1, nombre);
        insertarInicio(lista1, apellido);
        insertarInicio(lista1, dni);
        insertarInicio(lista1, telefono);
         // Imprimir
        //cout << "==================" << endl;
        //cout << " CODIGO: " << codigo << endl;
        //cout << " NOMBRE: " << nombre << endl;
        //cout << " CATEGORIA: " << apellido << endl;
        //cout << " IMAGEN DE VENTA: " <<dni << endl;
        //cout << " Precio de venta: " <<telefono  << endl; 
   }  
}

void subMenuInsumos(){
    int opcion=0,opc2=0;
    string num;
    while(opcion!=5){
        
    cout << "----------------------------------" << endl;
		cout << "\t\t\tMENU" << endl;
		cout << "----------------------------------" << endl;
		cout << "||  [1] Listar insumos" << endl;
		cout << "||  [2] Buscar insumos" << endl;
		cout << "||  [3] Eliminar insumos" << endl;
		cout << "||  [4] Volver al menu" << endl;
        cout << "||    Digite una opcion \t"; 
        cin>>opc2;
        switch(opc2){
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
        }
    }
}

////////////////////////////////////////////////////////////////
bool ExisteCliente(ListaEn lista,string codcli){
  buscarElemento(lista, valor)
  if()
}


void Agregar_Venta(){
   string codCli=0;
   string codIns=0;
   bool existCli,existInsu;
  
  cout<<"Digite el codigo del cliente";
  cin>>codCli;
  cout<<"Digite el codigo del insumo";
  cin>>codIns;

  existCli=ExisteCliente(,codCli);
  existInsu=ExisteInsumo(,codIns);
  

  
}
////////////////////////////////FUNCION PRINCIPAL///////////////////////////////////////
int main()
{
	ListaEn Lista=NULL,Lista1=NULL;
  AlmacenarArchivo(Lista,Lista1);

  //ImprimirLista(Lista);
  //ImprimirLista(Lista1);
  subMenuInsumos();
    return 0;
}