INTERFACES = ICollection/interfaces/
COLECCIONES = ICollection/collections/

all: Venta.o Producto.o ICollectible.o IIterator.o ICollection.o ListNode.o ListIterator.o List.o main.o
	g++ Producto.o ICollectible.o IIterator.o ICollection.o ListNode.o ListIterator.o List.o main.o -o programa

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

Producto.o: Producto.cpp ICollectible.o
	g++ -c Producto.cpp

Venta.o: Venta.cpp ICollectible.o
	g++ -c Venta.cpp

Factura.o: Factura.cpp ICollectible.o
	g++ -c Factura.cpp

main.o: main.cpp Producto.o
	g++ -c main.cpp

clean:
	rm -f programa *.o $(INTERFACES)*.o $(COLECCIONES)*.o

run:
	make clean
	make
	clear
	./programa
