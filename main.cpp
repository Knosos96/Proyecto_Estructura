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
	int cod;
	string nom_cli;
	string nom_pro;
	int cantidad;
	float precioUnit;
	float precioTotal;
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
ListaEn Lista=NULL,Lista1=NULL;
NodoArbol3 *Arbol_Venta=NULL;
NodoArbol *Arbol_Insumo=NULL;
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
            //cout<<endl<<" Encontrada en posicion "<< i <<endl;
            busc = 1;
            return q->dato;
        }
        q = q->next;
        i++;
    }
    
  if(busc==0){
    cout<<"\n\n Codigo no encontrado..!"<< endl;
    return "XXXX";
    }
        
}

string buscarElementoNombre(ListaEn lista,string valor){
    ListaEn q = lista;
    int  busc = 0;
  
  while(q!=NULL)
    {
        if(q->dato==valor)
        {
            busc = 1;
            q=q->next;
            return q->dato;
        }
        q = q->next;
        
    }
}

string buscarElementoPrecio(ListaEn lista,string valor){
    ListaEn q = lista;
    int  busc = 0,i=1;
  
  while(q!=NULL)
    {
        if(q->dato==valor)
        {
            while(i<5){
               q=q->next;
               i++;
            }

            return q->dato;
        }
        q = q->next;
        
    }
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
void menuCliente(nodoArbol1 *a){
    int opcion=0;
    cout<<"*------------------------------*"<<endl;
    cout<<"\tMenu Clientes"<<endl;
    cout<<"*------------------------------*"<<endl;
    cout<<"1.Listar Cliente"<<endl;
    cout<<"2.Buscar Cliente"<<endl;
    cout<<"3.Eliminar Cliente"<<endl;
    cout<<"4.Volver al menu principal"<<endl;
    cout<<"Digite una opción: ";
    cin>>opcion;
    switch(opcion){
        case 1:
            //mostrarArbol(a);
            break;
        case 2:
            //buscarCliente(a,buscar);
            break;
        case 3:
            //eliminarCliente(a,c2);
            break;
        case 4:
            break;
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
  
}
void buscarInsumo(nodoArbol* ArbolInsumo){
  
}
void eliminarInsumo(){
  
}

//////////////////////////////////////////////////////////////////
///////////////////////////VENTAS//////////////////////////////////////////////////
Ventas* crearVenta(int codIn, string nombIn, string nompro, int cant, float precio,float precioT){
    Ventas* i= new Ventas();
    i->cod = codIn;
    i->nom_cli = nombIn;
    i->nom_pro = nompro;
    i->cantidad = cant;
    i->precioUnit = precio;
    i->precioTotal=precioT;
    return i;
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
void crearArbol(NodoArbol3 *raiz){
  raiz = NULL;
  return;
}


NodoArbol3 *crearNodo(Ventas* ventas,NodoArbol3 *izq,NodoArbol3 *der){
    
    NodoArbol3 * c = new NodoArbol3();
    c->sell=ventas;
    c->izq=izq;
    c->der=der;
    //cout<<"Hola";
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
Ventas *Buscar(NodoArbol3 *n,int valor){
    //Ventas *venta;
    if (n == NULL){
        cout<<"No hay Venta\n";
        return NULL; 
    }
    else if(valor==n->sell->cod)
        return n->sell;
    else if(valor>n->sell->cod)
        return (Buscar(n->der,valor));
    else 
        return (Buscar(n->izq,valor));
}
/////////////////////////////////////////////////////////////
NodoArbol3 *Insertar_Venta(NodoArbol3 *nodo, Ventas *venta) {
  if(nodo==NULL){
     return crearNodo(venta,NULL,NULL);
  }
  if(venta->cod<=nodo->sell->cod){
    nodo->izq=Insertar_Venta(nodo->izq,venta);
  }
  else{
    nodo->der=Insertar_Venta(nodo->der,venta);
  }
  return nodo;
}
//////////////////////////////////////////////////////

NodoArbol3 *retirar(NodoArbol3 *nodo, Ventas* v){
    NodoArbol3 *nodo1,*nodo2;
    
    if(nodo==NULL)
        return NULL;
    else if(v->cod<nodo->sell->cod)
        nodo->izq=retirar(nodo->izq,v);
    else if(v->cod>nodo->sell->cod)
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

        insertarFinal(lista, CODIGO);
        insertarFinal(lista, NOMBRES);
        insertarFinal(lista, CATEGORIAS);
        insertarFinal(lista, IMAGENES);
        insertarFinal(lista,PRECIOS);
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

        insertarFinal(lista1, codigo);
        insertarFinal(lista1, nombre);
        insertarFinal(lista1, apellido);
        insertarFinal(lista1, dni);
        insertarFinal(lista1, telefono);
   }  
}
//////////////////////////////////////////////////////////////////
//Agregar Clientes al txt
void AgregarClientetxt(Cliente* x){
    
    ofstream archivo;
    archivo.open("Clientes.txt", ios::app);
    if (archivo.good()) {
	    
	    archivo<<x->cod_cl<<" "<<x->nom_cl<<" "<<x->ape_cl<<" "<<x->dni_cl<<" "<<x->tel_cl<<endl;
	    archivo.close();
      cout<<"Informacion Guardada Satisfactoriamente"<<endl;    
	  }else{
	     cout << "\n Error al querer agregar un cliente \n";
	     
	  }

}
//Eliminar clientes del txt
void EliminarInfoCliente(Cliente* x){
    ifstream archivo;
    archivo.open("Clientes.txt", ios::app);
    ofstream archi;
    archi.open("Cli.txt", ios::out);
    if (archivo.good()) {
        int aux;
        
        cout<<"Ingrese el codigo:"<<endl;
        cin>>aux;
        
        archivo>>x->cod_cl;
        if (archivo.eof()){
            cout<<"Hubo un problema!!! El archivo no contiene datos";
            
        }
        while(!archivo.eof()){
            archivo>>x->nom_cl>>x->ape_cl>>x->dni_cl>>x->tel_cl;
            if(aux==x->cod_cl){
                cout<<"Se elimino la Informacion";
                
            }
            else{
                archi<<x->cod_cl<<" "<<x->nom_cl<<" "<<x->ape_cl<<" "<<x->dni_cl<<" "<<x->tel_cl<<endl;
                
                
                
            }
            archivo>>x->cod_cl;
        }
        archi.close();
        archivo.close();
        remove("Clientes.txt");
        rename("Cli.txt","Clientes.txt");
    }
    else {
        cout<<"Error al abrir el archivo";
    }
    
}      
//Agregar venta al txt
void AgregarVentatxt(Ventas* x){
    
    ofstream aventas;
    aventas.open("Ventas.txt", ios::app);
    if (aventas.good()) {
	    
	    aventas<<x->cod<<" "<<x->nom_cli<<" "<<x->nom_pro<<" "<<x->cantidad<<" "<<x->precioUnit<<" "<<x->precioTotal<<endl;
	    aventas.close();
      cout<<"Informacion Guardada Satisfactoriamente"<<endl;    
	}
	else{
	     cout << "\n Error al querer guardar la venta \n";
	     
	}

}
//Eliminar venta del txt
void EliminarInfoVentas(Ventas* x){
    ifstream aventas;
    aventas.open("Ventas.txt", ios::app);
    ofstream archi;
    archi.open("Ven.txt", ios::out);
    if (aventas.good()) {
        int aux;
        
        cout<<"Ingrese el codigo:"<<endl;
        cin>>aux;
        
        aventas>>x->cod;
        if (aventas.eof()){
            cout<<"Hubo un problema!!! El archivo no contiene datos";
            
        }
        while(!aventas.eof()){
            aventas>>x->nom_cli>>x->nom_pro>>x->cantidad>>x->precioUnit>>x->precioTotal;
            if(aux==x->cod){
                cout<<"Se elimino la Informacion";
                
            }
            else{
                archi<<x->cod<<" "<<x->nom_cli<<" "<<x->nom_pro<<" "<<x->cantidad<<" "<<x->precioUnit<<" "<<x->precioTotal<<endl;
                
                
                
            }
            aventas>>x->cod;
        }
        archi.close();
        aventas.close();
        remove("Ventas.txt");
        rename("Ven.txt","Ventas.txt");
    }
    else {
        cout<<"Error al abrir el archivo";
    }
    
}
//Guardar insumo en el txt
void AgregarInsumotxt(Insumo* x){
    
    ofstream ainsumo;
    ainsumo.open("Insumo.txt", ios::app);
    if (ainsumo.good()) {
	    
	    ainsumo<<x->cod_in<<" "<<x->nom_in<<" "<<x->cat_in<<" "<<x->imag_in<<" "<<x->precio_in<<endl;
	    ainsumo.close();
      cout<<"Informacion Guardada Satisfactoriamente"<<endl;    
	}
	else{
	     cout << "\n Error al querer agregar el insumo \n";
	     
	}

}
//Eliminar insumo del txt
void EliminarInfoInsumo(Insumo* y){
    ifstream ainsumo;
    ainsumo.open("Insumo.txt", ios::app);
    ofstream archi;
    archi.open("In.txt", ios::out);
    if (ainsumo.good()) {
        int aux;
        
        cout<<"Ingrese el codigo del producto:"<<endl;
        cin>>aux;
        
        ainsumo>>y->cod_in;
        if (ainsumo.eof()){
            cout<<"Hubo un problema!!! El archivo no contiene datos";
            
        }
        while(!ainsumo.eof()){
            ainsumo>>y->nom_in>>y->cat_in>>y->imag_in>>y->precio_in;
            if(aux==y->cod_in){
                cout<<"Se elimino la Informacion";
                
            }
            else{
                archi<<y->cod_in<<" "<<y->nom_in<<" "<<y->cat_in<<" "<<y->imag_in<<" "<<y->precio_in<<endl;
                
                
                
            }
            ainsumo>>y->cod_in;
        }
        archi.close();
        ainsumo.close();
        remove("Insumo.txt");
        rename("In.txt","Insumo.txt");
    }
    else {
        cout<<"Error al abrir el archivo";
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
                ///buscarInsumo(ArbolInsumo);
                system("pause");
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
  string codigo=buscarElemento(lista,codcli);
  if(codigo==codcli){
    return true;
  }
  else{
    return false;
  }
}

bool ExisteInsumo(ListaEn lista, string codins){
  string codigo=buscarElemento(lista,codins);
    if(codigo==codins){
    return true;
  }
  else{
    return false;
  }
}

void AgregarVenta(ListaEn &lista,ListaEn &lista1,Ventas *venta){
  
   string codCli;
   string codIns;
   string newinsu;
   string newcli;
   string precio;
   int cant,ver=0;
   bool existCli,existInsu;
   
  
  while(ver!=1){
     cout<<"Digite el codigo del cliente:";
  cin>>codCli;
  cout<<"Digite el codigo del insumo:";
  cin>>codIns;

  existCli=ExisteCliente(Lista1,codCli);
  existInsu=ExisteInsumo(Lista,codIns);
  
  if(existCli==true && existInsu==true){
    
    cout << "\n\t******Codigos encontrados satisfactoriamente******" << endl;
    cout << "\n\tDigite la cantidad del producto seleccionado a llevar: " << endl;
		cin >> cant;

    newinsu=buscarElementoNombre(Lista,codIns);
    newcli=buscarElementoNombre(Lista1,codCli);
    precio=buscarElementoPrecio(Lista,codIns);
    
    float precio1=std::stof(precio);

    float precioTotal=cant*precio1;
    cout << "\n\tGenerando Codigo..." << endl;
    int num=4000+rand()%(5001-4000);
    
    venta =crearVenta(num,newinsu,newcli,cant,precio1, precioTotal);
    Arbol_Venta=Insertar_Venta(Arbol_Venta, venta);
    //ImprimirArbol(Arbol_Venta);
    cout << "\n\t..Codigo Generado..." << endl;
    cout<<"Codigo de la Venta:"<<num<<"\n";
    cout<<"¿Desea Continuar? [SI=0]/[NO=1]:";
    cin>>ver;
  }
    else{
      cout<<"No existe Algun cliente o producto relacionado";
      cout<<"\n¿Desea Continuar? [SI=0]/[NO=1]:";
      cin>>ver;
    }
 
  }
}

void Buscar_Venta(NodoArbol3 *nodo){

  int valor,op=0;
  Ventas *venta;
  while(op!=1){
    
    cout<<"*****Digite el codigo que desea buscar:******";
    cout<<"\n Nota:||[1] SALIR";
    cin>>valor;
    venta=Buscar(nodo,valor);
    if(venta==NULL){
      op=1;
    }
    else{
    imprimirVentas(venta);
    cout<<"\n\t¿Que desea hacer?"<<endl;
    cout << "|| [1] Imprimir Ventas" << endl;
		cout << "|| [2] Salir\n" << endl;
    cout << "|| Digite una opcion : \t " << endl; 
    cin>>op;
    switch(op){
      case 1:
        AgregarVentatxt(venta);
        break;
      case 2:
        op=1;
        break;
    }
  
    }
  }
}


void Eliminar_Venta(NodoArbol3 *nodo){
  Ventas *venta;
  int valor,op=0;
  cout<<"Digite el codigo que desea eliminar:";
  cin>>valor;
  venta=Buscar(nodo,valor);
  retirar(nodo,venta);
  cout<<"\nVenta Retirada\n"<<endl;
  
}


//////////////////////////////////////////
void Menu_Venta(){
  Ventas *venta;
  int opc = 0;
  while(opc!=5){
    cout << "*********************************************" << endl;
		cout << "\t.:.:.:.:.Menu de Ventas.:.:.:.:." << endl;
		cout << "*********************************************" << endl;
		cout << "|| [1] Agregar Ventas" << endl;
		cout << "|| [2] Listar Ventas" << endl;
		cout << "|| [3] Buscar Ventas" << endl;
    cout << "|| [4] Eliminar Ventas" << endl;
		cout << "|| [5] Salir" << endl;
		cout << "|| Digite una opcion : \t " << endl; 
    cin>>opc;
    switch(opc){
      case 1:
        AgregarVenta(Lista,Lista1,venta);
        break;
      case 2:
        ImprimirArbol(Arbol_Venta);
        break;
      case 3:
        Buscar_Venta(Arbol_Venta);
        break;
      case 4:
        Eliminar_Venta(Arbol_Venta);
        break;
      case 5:
        opc=5;
        break;
    }
  }
}
/////////////////////////////////////////////////////
void MainMenu() 
{
	int opc = 0;
	do {
		cout << "*********************************************" << endl;
		cout << "\t.:.:.:.:.Main Menu.:.:.:.:." << endl;
		cout << "*********************************************" << endl;
		cout << "|| [1] Menu de Clientes" << endl;
		cout << "|| [2] Menu de Insumos" << endl;
		cout << "|| [3] Menu de Ventas" << endl;
		cout << "|| [4] Salir" << endl;
		cout << "|| Digite una opcion : \t " << endl; 
	    cin >> opc;
		//system("cls");
		switch (opc) 
		{
		case 1:
			//subMenuClientes();
			//system("pause");
			break;
		case 2:
			//subMenuInsumos();
			//system("pause");
			break;
		case 3:
			 Menu_Venta();
			//system("pause");
			break;
		case 4:
			//system("pause");
			break;
		}
		//system("cls");

	} while (opc != 4);
}
////////////////////////////////FUNCION PRINCIPAL///////////////////////////////////////
int main()
{
  AlmacenarArchivo(Lista,Lista1);
   MainMenu();
   
  //ImprimirLista(Lista1);
  //MainMenu() ;
  //subMenuInsumos();
  return 0;
}