INTERFACES = ICollection/interfaces/
COLECCIONES = ICollection/collections/

all: DtHora.o DtVenta.o DtFecha.o DtMesa.o DtComun.o DtMenu.o DtProducto.o DtAsignacion.o DtDireccion.o Domicilio.o Local.o Venta.o Producto.o Comun.o Comun-Menu.o Menu.o Empleado.o Factura.o Mesa.o Mozo.o Pedido.o Repartidor.o ICollectible.o IIterator.o ICollection.o ListNode.o ListIterator.o List.o main.o
	g++ Domicilio.o Local.o Venta.o Producto.o Comun.o Comun-Menu.o Menu.o Empleado.o Factura.o Mesa.o Mozo.o Pedido.o Repartidor.o ICollectible.o IIterator.o ICollection.o ListNode.o ListIterator.o List.o main.o -o programa


ICollectible.o: $(INTERFACES)ICollectible.h
	g++ -c $(INTERFACES)ICollectible.cpp

IIterator.o: $(INTERFACES)IIterator.h
	g++ -c $(INTERFACES)IIterator.cpp

ICollection.o: $(INTERFACES)ICollection.h IIterator.o ICollectible.o
	g++ -c $(INTERFACES)ICollection.cpp

ListNode.o: $(COLECCIONES)ListNode.h
	g++ -c $(COLECCIONES)ListNode.cpp

ListIterator.o: $(COLECCIONES)ListIterator.h ListNode.o
	g++ -c $(COLECCIONES)ListIterator.cpp

List.o: $(COLECCIONES)List.h ICollection.o ListIterator.o
	g++ -c $(COLECCIONES)List.cpp

Factura.o: Factura.cpp ICollectible.o
	g++ -c Factura.cpp

Producto.o: Producto.cpp ICollectible.o
	g++ -c Producto.cpp

Comun.o: Producto.o
	g++ -c Comun.cpp

Menu.o:Producto.o
	g++ -c Menu.cpp

Comun-Menu.o: Comun-Menu.cpp
	g++ -c Comun-Menu.cpp

Venta.o: Venta.cpp ICollectible.o
	g++ -c Venta.cpp

Domicilio.o: Venta.o
	g++ -c Domicilio.cpp

Local.o: Venta.o
	g++ -c Local.cpp


DtDireccion.o:
	g++ -c "./DataTypes/DtDireccion.cpp"

DtAsignacion.o:
	g++ -c "./DataTypes/DtAsignacion.cpp"

DtProducto.o:
	g++ -c "./DataTypes/DtProducto.cpp"

DtComun.o:
	g++ -c "./DataTypes/DtComun.cpp"

DtMenu.o:
	g++ -c "./DataTypes/DtMenu.cpp"

DtMesa.o:
	g++ -c "./DataTypes/DtMesa.cpp"

DtFecha.o:
	g++ -c "./DataTypes/DtFecha.cpp"

DtVenta.o:
	g++ -c "./DataTypes/DtVenta.cpp"

DtHora.o:
	g++ -c "./DataTypes/DtHora.cpp"

main.o: main.cpp Producto.o
=======
Empleado.o: Empleado.cpp ICollectible.o
	g++ -c Empleado.cpp

Mozo.o: Empleado.o
	g++ -c Mozo.cpp

Repartidor.o: Empleado.o
	g++ -c Repartidor.cpp

Cliente.o: Cliente.cpp
	g++ -c Cliente.cpp

Mesa.o: Mesa.cpp ICollectible.o
	g++ -c Mesa.cpp

Pedido.o: Pedido.cpp ICollectible.o
	g++ -c Pedido.cpp


main.o: main.cpp Domicilio.o Local.o Venta.o Producto.o Comun.o Comun-Menu.o Menu.o Empleado.o Factura.o Mesa.o Mozo.o Pedido.o Repartidor.o
	g++ -c main.cpp

clean:
	rm -f programa *.o $(INTERFACES)*.o $(COLECCIONES)*.o

run:
	make clean
	make
	clear
	./programa
