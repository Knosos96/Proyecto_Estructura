//Funciones Miscelaneas
void MainMenu() {
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
		// system("cls");
		switch (opc) {
		case 1:
			menuCliente();
			// system("pause");
			break;
		case 2:
			subMenuInsumos();
			// system("pause");
			break;
		case 3:
			Menu_Venta();
			// system("pause");
			break;
		case 4:
			// system("pause");
			break;
		}
		// system("cls");

	} while (opc != 4);
}
//Funciones de archivos
void AlmacenarArchivo(ListaEn &lista, ListaEn &lista1) {
	ifstream archivo("Insumos.csv");
	ifstream archivo1("Clientes.csv");
	string linea, linea1;
	char delimitador = ',';

	getline(archivo, linea);
	getline(archivo1, linea1);

	while (getline(archivo, linea)) {
		stringstream stream(linea); // Convertir la cadena a un stream
		string CODIGO, NOMBRES, CATEGORIAS, IMAGENES, PRECIOS, STOCK,
			EXISTENCIA;

		// Extraer todos los valores de esa fila
		getline(stream, CODIGO, delimitador);
		getline(stream, NOMBRES, delimitador);
		getline(stream, CATEGORIAS, delimitador);
		getline(stream, IMAGENES, delimitador);
		getline(stream, PRECIOS, delimitador);
		getline(stream, STOCK, delimitador);
		getline(stream, EXISTENCIA, delimitador);

		insertarFinal(lista, CODIGO);
		insertarFinal(lista, NOMBRES);
		insertarFinal(lista, CATEGORIAS);
		insertarFinal(lista, IMAGENES);
		insertarFinal(lista, PRECIOS);
		insertarFinal(lista, STOCK);
		insertarFinal(lista, EXISTENCIA);
	}

	while (getline(archivo1, linea1)) {
		stringstream stream(linea1); // Convertir la cadena a un stream
		string codigo, nombre, apellido, dni, telefono;

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
// Agregar cliente al txt
void AgregarClientetxt(Cliente *x) {
	ofstream archivo;
	archivo.open("Clientes.txt", ios::app);
	if (archivo.good()) {
		archivo << x->cod_cl << " " << x->nom_cl << " " << x->ape_cl << " "
				<< x->dni_cl << " " << x->tel_cl << endl;
		archivo.close();
		cout << "Informacion Guardada Satisfactoriamente" << endl;
	} else {
		cout << "\n Error al querer agregar un cliente \n";
	}
}
// Eliminar clientes del txt
void EliminarInfoCliente(Cliente *x) {
	ifstream archivo;
	archivo.open("Clientes.txt", ios::app);
	ofstream archi;
	archi.open("Cli.txt", ios::out);
	if (archivo.good()) {
		int aux;

		cout << "Ingrese el codigo:" << endl;
		cin >> aux;

		archivo >> x->cod_cl;
		if (archivo.eof()) {
			cout << "Hubo un problema!!! El archivo no contiene datos";
		}
		while (!archivo.eof()) {
			archivo >> x->nom_cl >> x->ape_cl >> x->dni_cl >> x->tel_cl;
			if (aux == x->cod_cl) {
				cout << "Se elimino la Informacion";
			} else {
				archi << x->cod_cl << " " << x->nom_cl << " " << x->ape_cl
					  << " " << x->dni_cl << " " << x->tel_cl << endl;
			}
			archivo >> x->cod_cl;
		}
		archi.close();
		archivo.close();
		remove("Clientes.txt");
		rename("Cli.txt", "Clientes.txt");
	} else {
		cout << "Error al abrir el archivo";
	}
}
