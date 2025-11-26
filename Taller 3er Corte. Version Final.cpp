#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Usuario
{
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena;
    string direccion;
    string metodoDePago;
};

struct Producto
{
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

struct CarritoDeCompras
{
    int idCarrito;
    Usuario usuario;
    Producto productos[50];
    double subtotal;
    double impuestos;
};

struct OrdenDeCompra
{
	int idOrden;
	Producto productos[50];
	double subtotal;
	double impuestos;
	double envio;
	double total;	
};

struct Categoria
{
	int idCategoria;
	string nombre;	
};

struct Comentario
{
    int idComentario;
    string producto;
    string usuario;
    string comentario;
    string fecha;
};

CarritoDeCompras carrito;
int cantidadProductosCarrito = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leerArchivos(Usuario u[], int &numUsuarios, Producto p[], int &numProductos, Comentario c[], int &numComentarios);
int iniciarSesion(Usuario u[], int numUsuarios);
void listarProductos(Producto p[], int numProductos);
void mostrarComentarios(Comentario c[], int numComentarios);
void listarUsuarios(Usuario u[], int numUsuarios);
void carritoCompras(Producto p[], int numProductos);
void mostrarCarrito();
void generarReporteCarrito();
void reporteproductospocoStock(Producto p[], int numProductos);
void reportecommentsporfecha(Comentario c[], int numComentarios);
void reporteprecios(Producto p[], int numProductos);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "spanish");
	
    Usuario usuarios[50];
    Producto productos[100];
    Comentario comentarios[100];
    int numUsuarios = 0, numProductos = 0, numComentarios = 0;

    leerArchivos(usuarios, numUsuarios, productos, numProductos, comentarios, numComentarios);

    cout << "Datos cargados correctamente desde los archivos." << endl;
    system("pause");
    system("cls");

    cout << "Bienvenido a Tecnonline" << endl;

    if (iniciarSesion(usuarios, numUsuarios) == 1)
    {
        int opc = 0;
				int opc2 = 0;

        do
        {
            system("pause");
            system("cls");

            cout << "-----  PORTAL DE USUARIOS  -----" << endl;
            cout << "\n\t1. Listar Productos" << endl;
            cout << "\t2. Comentarios" << endl;
            cout << "\t3. Listar Usuarios" << endl;
            cout << "\t4. Ir al carrito" << endl;
            cout << "\t5. Ver carrito" << endl;
            cout << "\t6. Reportes" << endl; 
            cout << "\t7. Salir" << endl;
            cout << "\n\tOpción: ";
            cin >> opc;
            cin.ignore();

            switch (opc)
            {
            case 1:
                system("cls");
                listarProductos(productos, numProductos);
                break;

            case 2:
                system("cls");
                mostrarComentarios(comentarios, numComentarios);
                break;

            case 3:
                system("cls");
                listarUsuarios(usuarios, numUsuarios);
                break;

            case 4:
                system("cls");
                carritoCompras(productos, numProductos);
                break;

            case 5:
                system("cls");
                mostrarCarrito();
                break;

            case 6:
	                system("cls");
	          
	                cout<<"-----  MENU DE REPORTES  -----"<<endl;
	                
		                do
		                {
		                	cout << "\n\t1. Reporte del carrito" << endl;
					            cout << "\t2. Reporte de productos con menor stock" << endl;
					            cout << "\t3. Reporte de cantidad de comentarios por fecha" << endl;
					            cout << "\t4. Reporte precio maximo y minimo de productos" << endl;
					            cout << "\t5. Salir" << endl;
					            cout << "\n\tOpción: ";
					            cin >> opc2;
	                	
		                	switch(opc2)
		                	{
		                			case 1: system("pause"); system("cls");
		                							generarReporteCarrito();
																	
																	break;
		                							
		                			case 2: system("pause"); system("cls");
		                							reporteproductospocoStock(productos, numProductos);
																	break;
		                			
		                			case 3: system("pause"); system("cls");
		                							reportecommentsporfecha(comentarios, numComentarios);
																	break;
		                			
													case 4: system("pause"); system("cls");	
		                							reporteprecios(productos, numProductos);			
		                							break;
		                							
		                			case 5: system("cls");
		                							cout << "Regresando al menu principal..." << endl;
		                							break;
		                							
		                			default: cout << "Opción inválida. Intende de nuevo." << endl;
		                							
											}
	                	
										} while(opc2 != 5);
	                
	                break;
                
            case 7:
            		system("cls");
                cout << "Saliendo del portal..." << endl;
                break;

            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
            }

        } while (opc != 7);
    }

    system("pause");
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leerArchivos(Usuario u[], int &numUsuarios, Producto p[], int &numProductos, Comentario c[], int &numComentarios)
{
    setlocale(LC_ALL, "spanish");
	
	ifstream archivoUsuarios("Usuarios.txt");
    ifstream archivoProductos("Productos.txt");
    ifstream archivoComentarios("Comentarios.txt");

    string linea;

    getline(archivoUsuarios, linea);
    numUsuarios = 0;
    while (getline(archivoUsuarios, linea))
    {
        stringstream ss(linea);
        string id, nombre, correo, contrasena, direccion, metodo;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, correo, ',');
        getline(ss, contrasena, ',');
        getline(ss, direccion, ',');
        getline(ss, metodo, ',');

        u[numUsuarios].idUsuario = stoi(id);
        u[numUsuarios].nombre = nombre;
        u[numUsuarios].correoElectronico = correo;
        u[numUsuarios].contrasena = contrasena;
        u[numUsuarios].direccion = direccion;
        u[numUsuarios].metodoDePago = metodo;
        numUsuarios++;
    }

    getline(archivoProductos, linea);
    numProductos = 0;
    while (getline(archivoProductos, linea))
    {
        stringstream ss(linea);
        string id, nombre, descripcion, precio, stock;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, descripcion, ',');
        getline(ss, precio, ',');
        getline(ss, stock, ',');

        p[numProductos].idProducto = stoi(id);
        p[numProductos].nombre = nombre;
        p[numProductos].descripcion = descripcion;
        p[numProductos].precio = stod(precio);
        p[numProductos].stock = stoi(stock);
        numProductos++;
    }

    getline(archivoComentarios, linea);
    numComentarios = 0;
    while (getline(archivoComentarios, linea))
    {
        stringstream ss(linea);
        string id, producto, usuario, comentario, fecha;
        getline(ss, id, ',');
        getline(ss, producto, ',');
        getline(ss, usuario, ',');
        getline(ss, comentario, ',');
        getline(ss, fecha, ',');

        c[numComentarios].idComentario = stoi(id);
        c[numComentarios].producto = producto;
        c[numComentarios].usuario = usuario;
        c[numComentarios].comentario = comentario;
        c[numComentarios].fecha = fecha;
        numComentarios++;
    }

    archivoUsuarios.close();
    archivoProductos.close();
    archivoComentarios.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int iniciarSesion(Usuario u[], int numUsuarios)
{
    setlocale(LC_ALL, "spanish");
	
	string nombre, contrasena;
    int aux = 0;

    do
    {
        cout << "-----  INICIO DE SESION  -----" << endl;
        cout << "Ingrese su nombre de usuario: ";
        getline(cin, nombre);
        cout << "Ingrese su contraseña: ";
        getline(cin, contrasena);

        for (int i = 0; i < numUsuarios; i++)
        {
            if (nombre == u[i].nombre && contrasena == u[i].contrasena)
            {
                cout << "Inicio de sesión exitoso." << endl;
                aux = 1;
                return 1;
            }
        }

        if (aux == 0)
        {
            cout << "Usuario y/o contraseña inválidos. Intente de nuevo." << endl;
            system("pause");
            system("cls");
        }

    } while (aux == 0);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void listarProductos(Producto p[], int numProductos)
{
    setlocale(LC_ALL, "spanish");
	
	int x = 0;

    cout << "-----  PRODUCTOS CON POCO STOCK  -----" << endl;

    for (int i = 0; i < numProductos; i++)
    {
        if (p[i].stock < 15)
        {
            cout << ++x << ". " << p[i].nombre << " --- " << p[i].stock << " unidades." << endl;
        }
    }

    if (x == 0)
        cout << "No hay productos con stock bajo." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrarComentarios(Comentario c[], int numComentarios)
{
	setlocale(LC_ALL, "spanish");

    string fechaFiltro;
    cout << "----- FILTRAR COMENTARIOS POR FECHA -----" << endl;
    cout << "Ingrese una fecha (YYYY-MM-DD): ";
    getline(cin, fechaFiltro);

    cout << "\n----- COMENTARIOS DESDE " << fechaFiltro << " -----\n";

    for (int i = 0; i < numComentarios; i++)
    {
        if (c[i].fecha >= fechaFiltro)
        {
            cout << "\nProducto: " << c[i].producto << endl;
            cout << "Usuario: " << c[i].usuario << endl;
            cout << "Comentario: " << c[i].comentario << endl;
            cout << "Fecha: " << c[i].fecha << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void listarUsuarios(Usuario u[], int numUsuarios)
{
    setlocale(LC_ALL, "spanish");
	
	cout << "-----  USUARIOS  -----" << endl;

    for (int i = 0; i < numUsuarios; i++)
    {
        string mayus = u[i].nombre;
        for (char &c : mayus)
            c = toupper(c);
        cout << mayus << " --- " << u[i].correoElectronico << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void carritoCompras(Producto p[], int numProductos)
{
    setlocale(LC_ALL, "spanish");
	
	int id, cantidad, aux, opc;

    do
    {
        cout << "----- AGREGAR PRODUCTO AL CARRITO -----" << endl;
        cout << "Ingrese el ID del producto: ";
        cin >> id;

        aux = 0;

        for (int i = 0; i < numProductos; i++)
        {
            if (p[i].idProducto == id)
            {
                aux = 1;
                cout << "Producto: " << p[i].nombre << endl;
                cout << "Precio: $" << p[i].precio << endl;
                cout << "Stock disponible: " << p[i].stock << endl;
                cout << "Cantidad a comprar: ";
                cin >> cantidad;

                if (cantidad <= p[i].stock && cantidad > 0)
                {
                    carrito.productos[cantidadProductosCarrito] = p[i];
                    carrito.productos[cantidadProductosCarrito].stock = cantidad;
                    carrito.subtotal += p[i].precio * cantidad;
                    cantidadProductosCarrito++;
                    cout << "Producto agregado correctamente al carrito." << endl;
                }
                else
                {
                    cout << "Cantidad no válida o insuficiente en stock." << endl;
                }
                break;
            }
        }

        if (aux == 0)
            cout << "No se encontró un producto con ese ID." << endl;

        cout << "\n¿Desea agregar otro producto?\n1. Sí\n2. No\nOpción: ";
        cin >> opc;
        system("cls");

    } while (opc == 1);

    carrito.impuestos = carrito.subtotal * 0.19;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrarCarrito()
{
    setlocale(LC_ALL, "spanish");
	
	cout << "----- CARRITO DE COMPRAS -----" << endl;

    if (cantidadProductosCarrito == 0)
    {
        cout << "El carrito está vacío." << endl;
        return;
    }

    for (int i = 0; i < cantidadProductosCarrito; i++)
    {
        cout << i + 1 << ". " << carrito.productos[i].nombre
             << " x" << carrito.productos[i].stock
             << " - $" << carrito.productos[i].precio * carrito.productos[i].stock << endl;
    }

    cout << "\nSubtotal: $" << carrito.subtotal << endl;
    cout << "Impuestos (19%): $" << carrito.impuestos << endl;
    cout << "Total: $" << carrito.subtotal + carrito.impuestos << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generarReporteCarrito()
{
	if (cantidadProductosCarrito == 0)
    {
        cout << "No hay productos en el carrito para generar un reporte." << endl;
        return;
    }

    ofstream reporte("reporte_carrito.txt");

    if (!reporte)
    {
        cout << "Error al crear el archivo de reporte." << endl;
        return;
    }

    reporte << "-----------------------------------------" << endl;
    reporte << "         REPORTE DEL CARRITO DE COMPRAS  " << endl;
    reporte << "-----------------------------------------" << endl << endl;

    for (int i = 0; i < cantidadProductosCarrito; i++)
    {
        reporte << i + 1 << ". " << carrito.productos[i].nombre << endl;
        reporte << "   Cantidad: " << carrito.productos[i].stock << endl;
        reporte << "   Precio Unitario: $" << carrito.productos[i].precio << endl;
        reporte << "   Subtotal: $" << carrito.productos[i].precio * carrito.productos[i].stock << endl;
        reporte << "-----------------------------------------" << endl;
    }

    reporte << fixed;
    reporte.precision(2);
    reporte << "\nSubtotal general: $" << carrito.subtotal << endl;
    reporte << "Impuestos (19%): $" << carrito.impuestos << endl;
    reporte << "Total a pagar: $" << carrito.subtotal + carrito.impuestos << endl;

    reporte.close();
    cout << "\nReporte generado exitosamente en 'reporte_carrito.txt'." << endl;
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reporteproductospocoStock(Producto p[], int numProductos)
{
    if (numProductos == 0)
    {
        cout << "No hay productos cargados para generar el reporte." << endl;
        return;
    }

    Producto temp[100];
    for (int i = 0; i < numProductos; i++)
    {
		
        temp[i] = p[i];
		}


    for (int i = 0; i < numProductos - 1; i++)
    {
        for (int j = 0; j < numProductos - i - 1; j++)
        {
            if (temp[j].stock > temp[j + 1].stock)
            {
                Producto aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    ofstream reporte("reporte_stock_bajo.txt");

    if (!reporte)
    {
        cout << "Error al crear el archivo del reporte." << endl;
        return;
    }

    reporte << "------------------------------------------\n";
    reporte << "     REPORTE: PRODUCTOS CON MENOR STOCK   \n";
    reporte << "------------------------------------------\n\n";

    int limite = (numProductos < 5) ? numProductos : 5;

    for (int i = 0; i < limite; i++)
    {
        reporte << i + 1 << ". " << temp[i].nombre << endl;
        reporte << "   Stock: " << temp[i].stock << endl;
        reporte << "   Precio: $" << temp[i].precio << endl;
        reporte << "------------------------------------------\n";
    }

    reporte.close();

    cout << "\nReporte generado exitosamente en 'reporte_stock_bajo.txt'." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reportecommentsporfecha(Comentario c[], int numComentarios)
{
    if (numComentarios == 0)
    {
        cout << "No hay comentarios cargados para generar el reporte." << endl;
        return;
    }

    string fechas[100];
    int conteo[100];
    int nFechas = 0;

    for (int i = 0; i < numComentarios; i++)
    {
        bool encontrada = false;

        for (int j = 0; j < nFechas; j++)
        {
            if (c[i].fecha == fechas[j])
            {
                conteo[j]++;
                encontrada = true;
                break;
            }
        }

        if (!encontrada)
        {
            fechas[nFechas] = c[i].fecha;
            conteo[nFechas] = 1;
            nFechas++;
        }
    }

    ofstream reporte("reporte_comentarios_por_fecha.txt");

    if (!reporte)
    {
        cout << "Error al crear el archivo de reporte." << endl;
        return;
    }

    reporte << "------------------------------------------\n";
    reporte << "   REPORTE: CANTIDAD DE COMENTARIOS POR FECHA\n";
    reporte << "------------------------------------------\n\n";

    for (int i = 0; i < nFechas; i++)
    {
        reporte << fechas[i] << " : " << conteo[i] << " comentarios\n";
    }

    reporte.close();

    cout << "Reporte generado exitosamente en 'reporte_comentarios_por_fecha.txt'." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reporteprecios(Producto p[], int numProductos)
{
    if (numProductos == 0)
    {
        cout << "No hay productos cargados para generar este reporte." << endl;
        return;
    }

    Producto maxP = p[0];
    Producto minP = p[0];

    for (int i = 1; i < numProductos; i++)
    {
        if (p[i].precio > maxP.precio)
            maxP = p[i];

        if (p[i].precio < minP.precio)
            minP = p[i];
    }

    ofstream reporte("reporte_precios.txt");

    if (!reporte)
    {
        cout << "Error al crear el archivo de reporte." << endl;
        return;
    }

    reporte << "------------------------------------------\n";
    reporte << "     REPORTE: PRECIO MÁXIMO Y MÍNIMO\n";
    reporte << "------------------------------------------\n\n";

    reporte << "Producto más caro:\n";
    reporte << "Nombre: " << maxP.nombre << "\n";
    reporte << "Precio: $" << maxP.precio << "\n";
    reporte << "------------------------------------------\n\n";

    reporte << "Producto más barato:\n";
    reporte << "Nombre: " << minP.nombre << "\n";
    reporte << "Precio: $" << minP.precio << "\n";
    reporte << "------------------------------------------\n";

    reporte.close();

    cout << "Reporte generado exitosamente en 'reporte_precios.txt'." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
