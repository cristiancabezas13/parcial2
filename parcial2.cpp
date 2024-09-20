#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura para representar una orden de cliente
struct Orden {
    int dia;
    int idOrden;
    int idCliente;
    string nombreCliente;
    string tipoPizza;
    string bebida;
};

// Estructura para representar los detalles de la venta
struct Venta {
    int dia;
    int idOrden;
    string tipoPizza;
    string bebida;
    double valorOrden;
};

// Función para generar un nombre de cliente aleatorio
string generarNombre() {
    string nombres[] = {"Juan", "Maria", "Luis", "Ana", "Pedro"};
    string apellidos[] = {"Perez", "Gomez", "Rodriguez", "Lopez", "Martinez"};
    return nombres[rand() % 5] + " " + apellidos[rand() % 5] + " " + apellidos[rand() % 5];
}

// Función para generar un tipo de pizza aleatorio
string generarPizza() {
    string pizzas[] = {"Pepperoni", "Hawaiana", "Vegetariana"};
    return pizzas[rand() % 3];
}

// Función para generar una bebida aleatoria
string generarBebida() {
    string bebidas[] = {"Coca-Cola", "Fanta", "Sprite", "Agua", "Ninguna"};
    return bebidas[rand() % 5];
}

// Función para calcular el valor de la orden
double calcularValorOrden(const string& pizza, const string& bebida, int mes) {
    double precioPizza = 15000 + (mes - 1) * 500; // Precio de la pizza aumenta cada mes
    double precioBebida = 0;
    if (bebida != "Ninguna") {
        precioBebida = 3000 + (mes - 1) * 70; // Precio de la bebida aumenta cada mes
    }
    return precioPizza + precioBebida;
}

int main() {
    srand(time(0));

    queue<Orden> colaOrdenes;
    stack<Venta> pilaVentas;

    int idOrden = 1;

    // Simulación de 360 días de ventas
    for (int dia = 1; dia <= 360; dia++) {
        int pizzasVendidas = 40 + rand() % 61; // Entre 40 y 100 pizzas al día

        for (int i = 0; i < pizzasVendidas; i++) {
            // Generar datos de la orden
            Orden orden;
            orden.dia = dia;
            orden.idOrden = idOrden++;
            orden.idCliente = 1000000000 + rand() % 1000000000; // ID de cliente aleatorio
            orden.nombreCliente = generarNombre();
            orden.tipoPizza = generarPizza();
            orden.bebida = generarBebida();

            // Añadir orden a la cola
            colaOrdenes.push(orden);

            // Calcular valor de la venta y añadir a la pila
            Venta venta;
            venta.dia = orden.dia;
            venta.idOrden = orden.idOrden;
            venta.tipoPizza = orden.tipoPizza;
            venta.bebida = orden.bebida;
            venta.valorOrden = calcularValorOrden(orden.tipoPizza, orden.bebida, (dia - 1) / 30 + 1);
            pilaVentas.push(venta);
        }
    }

    // Imprimir las primeras 10 órdenes
    cout << "Primeras 10 ordenes atendidas:" << endl;
    for (int i = 0; i < 10 && !colaOrdenes.empty(); i++) {
        Orden orden = colaOrdenes.front();
        colaOrdenes.pop();
        cout << "Dia: " << orden.dia << ", IdOrden: " << orden.idOrden
             << ", Cliente: " << orden.nombreCliente << ", Pizza: " << orden.tipoPizza
             << ", Bebida: " << orden.bebida << endl;
    }

    // Imprimir las últimas 5 órdenes
    cout << "\nUltimas 5 ordenes atendidas:" << endl;
    stack<Orden> ultimasOrdenes;
    while (!colaOrdenes.empty()) {
        ultimasOrdenes.push(colaOrdenes.front());
        colaOrdenes.pop();
    }
    for (int i = 0; i < 5 && !ultimasOrdenes.empty(); i++) {
        Orden orden = ultimasOrdenes.top();
        ultimasOrdenes.pop();
        cout << "Dia: " << orden.dia << ", IdOrden: " << orden.idOrden
             << ", Cliente: " << orden.nombreCliente << ", Pizza: " << orden.tipoPizza
             << ", Bebida: " << orden.bebida << endl;
    }

    return 0;
}