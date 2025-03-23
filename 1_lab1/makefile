all: Turno.o DtSocio.o Fecha.o DtClase.o DtSpinning.o DtEntrenamiento.o Socio.o Inscripcion.o Clase.o Spinning.o Entrenamiento.o main.o 
	g++ Turno.o DtSocio.o Fecha.o DtClase.o DtSpinning.o DtEntrenamiento.o Socio.o Inscripcion.o Clase.o Spinning.o Entrenamiento.o main.o -o programa

Turno.o:
	g++ -c "./DataTypes/Turno.h"

DtSocio.o: 
	g++ -c "./DataTypes/DtSocio.cpp"

Fecha.o:
	g++ -c "./DataTypes/Fecha.cpp"

DtClase.o:
	g++ -c "./DataTypes/DtClase.cpp"

DtSpinning.o:
	g++ -c "./DataTypes/DtSpinning.cpp"

DtEntrenamiento.o:
	g++ -c "./DataTypes/DtEntrenamiento.cpp"

Socio.o: 
	g++ -c Socio.cpp

Inscripcion.o: 
	g++ -c Inscripcion.cpp

Clase.o: 
	g++ -c Clase.cpp

Spinning.o: 
	g++ -c Spinning.cpp

Entrenamiento.o: 
	g++ -c Entrenamiento.cpp
	
main.o: 
	g++ -c main.cpp

clean:
	rm -f Turno.o DtSocio.o Fecha.o DtClase.o DtSpinning.o DtEntrenamiento.o Socio.o Inscripcion.o Clase.o Spinning.o Entrenamiento.o main.o programa
run:
	make clean
	make
	clear
	./programa