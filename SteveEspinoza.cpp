#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

nodoArbol1 *insertarCliente(nodoArbol1 *nodo, Cliente *c) {
	if (nodo == NULL) {
		return crearArbol(c, NULL, NULL);
	}
	if (c->cod_cl <= nodo->info->cod_cl) {
		nodo->izq = insertarCliente(nodo->izq, c);
	} else {
		nodo->der = insertarCliente(nodo->der, c);
	}
	return nodo;
}

void listarCliente(nodoArbol1 *a) {
	Cliente *x;
	int cod = 0;
	string nom, ape, dni, tel;
	if (a == NULL) {
		cout << "No existe registro de ningun cliente" << endl;
		cout << "Porfavor Agregue un Cliente:" << endl;
		cout << "Codigo: ";
		cin >> cod;
		cout << "Nombre: ";
		cin >> nom;
		cout << "Apellido: ";
		cin >> ape;
		cout << "DNI: ";
		cin >> dni;
		cout << "Telefono: ";
		cin >> tel;
		x = crearCliente(cod, nom, ape, dni, tel);
		a = crearArbol(x, NULL, NULL);

		// LLAMARFUNCION PARA AGREGAR CLIENTE
	} else {
		cout << "||\t\tLISTADO DE CLIENTES\t\t||" << endl;
		mostrarArbol(a);
	}
}

void actualizarStock(NodoArbol *x) {
	int cant = 0;
	if (x == NULL) {
		return;
	} else {
		if (x->info->stock == 0) {
			cout << "Usted no cuenta con stock suficiente en el siguiente "
					"producto: "
				 << x->info->cod_in << endl;
			cout << "Ingrese la cantidad que desea agregar al stock:";
			cin >> cant;
			while (x->info->exist < cant) {
				cout << "Disculpe usted no cuenta con cantidad suficiente, "
						"ingrese otro valor";
				cin >> cant;
			}
			if (x->info->exist >= cant) {
				x->info->stock = cant;
				x->info->exist += 0 - cant;
			}
		}

		actualizarStock(x->izq);
		actualizarStock(x->der);
	}
}

void AgregarInsumotxt(Insumo *x) {
	ofstream ainsumo;
	ainsumo.open("Insumo.txt", ios::app);
	if (ainsumo.good()) {
		ainsumo << x->cod_in << " " << x->nom_in << " " << x->cat_in << " "
				<< x->imag_in << " " << x->precio_in << " " << x->stock << " "
				<< x->exist << endl;
		ainsumo.close();
		// cout<<"Informacion Guardada Satisfactoriamente"<<endl;
	} else {
		cout << "\n Error al querer agregar el insumo \n";
	}
}

void EliminarInfoInsumo(Insumo *y) {
	ifstream ainsumo;
	ainsumo.open("Insumo.txt", ios::app);
	ofstream archi;
	archi.open("In.txt", ios::out);
	if (ainsumo.good()) {
		int aux;

		cout << "Ingrese el codigo del producto:" << endl;
		cin >> aux;

		ainsumo >> y->cod_in;
		if (ainsumo.eof()) {
			cout << "Hubo un problema!!! El archivo no contiene datos";
		}
		while (!ainsumo.eof()) {
			ainsumo >> y->nom_in >> y->cat_in >> y->imag_in >> y->precio_in;
			if (aux == y->cod_in) {
				cout << "Se elimino la Informacion";

			} else {
				archi << y->cod_in << " " << y->nom_in << " " << y->cat_in
					  << " " << y->imag_in << " " << y->precio_in << " "
					  << y->stock << " " << y->exist << endl;
			}
			ainsumo >> y->cod_in;
		}
		archi.close();
		ainsumo.close();
		remove("Insumo.txt");
		rename("In.txt", "Insumo.txt");
	} else {
		cout << "Error al abrir el archivo";
	}
}

void AgregarVentatxt(Ventas *x) {
	ofstream aventas;
	aventas.open("Ventas.txt", ios::app);
	if (aventas.good()) {
		aventas << x->cod << " " << x->nom_cli << " " << x->nom_pro << " "
				<< x->cantidad << " " << x->precioUnit << " " << x->precioTotal
				<< endl;
		aventas.close();
		cout << "Informacion Guardada Satisfactoriamente" << endl;
	} else {
		cout << "\n Error al querer guardar la venta \n";
	}
}
// Eliminar venta del txt
void EliminarInfoVentas(Ventas *x, int aux) {
	ifstream aventas;
	aventas.open("Ventas.txt", ios::app);
	ofstream archi;
	archi.open("Ven.txt", ios::out);
	if (aventas.good()) {
		aventas >> x->cod;
		if (aventas.eof()) {
			cout << "Hubo un problema!!! El archivo no contiene datos";
		}
		while (!aventas.eof()) {
			aventas >> x->nom_cli >> x->nom_pro >> x->cantidad >>
				x->precioUnit >> x->precioTotal;
			if (aux == x->cod) {
				cout << "Se elimino la Informacion";

			} else {
				archi << x->cod << " " << x->nom_cli << " " << x->nom_pro << " "
					  << x->cantidad << " " << x->precioUnit << " "
					  << x->precioTotal << endl;
			}
			aventas >> x->cod;
		}
		archi.close();
		aventas.close();
		remove("Ventas.txt");
		rename("Ven.txt", "Ventas.txt");
	} else {
		cout << "Error al abrir el archivo";
	}
}

