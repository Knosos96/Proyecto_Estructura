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
	string desc_in;
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
       int dato;        
       struct nodo *next;
};
typedef struct nodo *ListaEn;

/////////////////////////////////////////////////////////////////////////

void insertarInicio(ListaEn &lista, int valor){
     ListaEn lista1;
     lista1 = new(struct nodo);
     lista1->dato = valor;
     lista1->next = lista;
     lista  = lista1;
}

void insertarFinal(ListaEn &lista, int valor){
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
 
    cout<<"\n\t Opcion : "; cin>> _op;
 
    if(op==1)
        band = -1;
    else
        band = 0;
 
    return band;
}

void insertarElemento(ListaEn &lista, int valor, int pos){
  
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

void buscarElemento(ListaEn lista, int valor){
    
    ListaEn q = lista;
    int i = 1, busc = 0;
 
    while(q!=NULL)
    {
        if(q->dato==valor)
        {
            cout<<endl<<" Encontrada en posicion "<< i <<endl;
            busc = 1;
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


/////////////////////////////////////////////////////////////////////////////
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

Insumo* crearInsumo(int codIn, string nombIn, string descIn, string imagIn, float precioIn){
    Insumo* i= (Insumo*)malloc(sizeof(Insumo));
    i->cod_in = codIn;
    i->nom_in = nombIn;
    i->desc_in = descIn;
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
        cout<<"\nDescripcion: "<<t->desc_in;
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
Insumo * buscar(NodoArbol * a , string s){
    if (a == NULL){
        cout<<"es nulo\n";
        return NULL;
    }
    else if (s.compare(a->info->nom_in) == 0)   
        return a->info; 
    else if (s.compare(a->info->nom_in) > 0)   
        return(buscar(a->der, s));   
    else 
        return(buscar(a->izq, s));
}
//METODO INSERTAR
NodoArbol* insertarInsumo(NodoArbol* nodo, Insumo* t){
    if (nodo == NULL)  {
        nodo = (NodoArbol*)malloc(sizeof(NodoArbol));   
        nodo->info = t;   
        nodo->izq = NULL;   
        nodo->der = NULL;   
    }
    else if (t->nom_in.compare(nodo->info->nom_in) < 0)   
        nodo->izq = insertarInsumo(nodo->izq, t);   
    else if(t->nom_in.compare(nodo->info->nom_in) > 0)   
        nodo->der = insertarInsumo(nodo->der, t); 
 return nodo;
}
//METODO RETIRAR
NodoArbol* retirarInsumo(NodoArbol* r, Insumo* v){
    NodoArbol *t, *f;   
    if (r == NULL)   
        return NULL;   
    else if (v->nom_in.compare(r->info->nom_in) < 0)   
        r->izq = retirarInsumo(r->izq, v);   
    else if (v->nom_in.compare(r->info->nom_in) > 0)   
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


////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////
void LeerArchivo(){

   ifstream archivo("Libro2.csv");
   string linea;
   char delimitador=',';
   getline(archivo,linea);
   while(getline(archivo,linea)){
    stringstream stream(linea); // Convertir la cadena a un stream
        string idProducto, codigoBarras, descripcion, precioCompra,     precioVenta, existencia, stock;
     
        // Extraer todos los valores de esa fila
        getline(stream, idProducto, delimitador);
        getline(stream, codigoBarras, delimitador);
        getline(stream, descripcion, delimitador);
        getline(stream, precioCompra, delimitador);
        getline(stream, precioVenta, delimitador);
        getline(stream, existencia, delimitador);
        getline(stream, stock, delimitador);
        // Imprimir
        cout << "==================" << endl;
        cout << "Id: " << idProducto << endl;
        cout << "Codigo de barras: " << codigoBarras << endl;
        cout << "Descripcion: " << descripcion << endl;
        cout << "Precio de compra: " << precioCompra << endl;
        cout << "Precio de venta: " << precioVenta << endl;
        cout << "Existencia: " << existencia << endl;
        cout << "Stock: " << stock << endl;
	
     
   }
   
  
}
void AgregarClientetxt(int cod, string nom, string ape, string dni, string num){
    
    ofstream archivo;
    archivo.open("Clientes.txt", ios::app);
    if (archivo.good()) {
	    
	    archivo << "Informacion del Cliente:" <<  endl;
	    archivo << "*\tCodigo: " << cod << endl;
	    archivo << "*\tNombre: " << nom << endl;
	    archivo << "*\tApellido: " << ape << endl;
	    archivo << "*\tDNI: " << dni << endl;
	    archivo << "*\tTelefono: " << num << endl;
	    archivo << "\n" << endl;
	    archivo.close();
        
	}
	else{
	     cout << "\n Error al querer agregar un cliente \n";
	     
	}

}

/////////////////////////////////////////////////////////////
int main()
{
	 cout<<"Hello World";
    LeerArchivo();

    return 0;
}
