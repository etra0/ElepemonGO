# Tarea 1: "Elepemon GO"

|Integrante|Rol|Usuario|
|----|----|----|
| Sebastián Aedo |201573057-1|saedo|
| Gaspar Correa |201573009-1|gcorrea|

# Instrucciones

Para compilar el código correctamente, necesitamos [**inih**](https://github.com/benhoyt/inih) en la carpeta raíz del código:
```bash
git clone https://github.com/benhoyt/inih.git
```

Para que funcione, primero ejecutar
```bash
make
```
con esto se compila el inih para cargar el archivo, luego
```bash
make compile
```

para compilar y obtener el ejecutable. Para probar usar
```bash
make run
```
debido a que el ejecutable se guarda en la carpeta bin

# Supuestos

* Se asume que no habrán elepemones con el mismo nombre.
* Se exige que el primer parametro sea el directorio donde estarán los ataques y el segundo el nombre del ini.
* Se exige que al escoger los elepemones se utilicen números.


# Breve descripción de la estrategia

* Se tiene el stack principal, donde se cargan todos los elepemones, luego se tiene un stack por cada jugador, los cuales tienenlos punteros a los elepemones de cada uno. Y por último, se tiene un stack `deadpool`, en el cual se almacenan los elepemones muertos.

* Respecto al cargado dinámico de los ataques, preferimos por cargar los ataques solo cuando el usuario desee utilizarlos, los handlers respectivos los almacenamos en un stack de handlers `global_handlers`, con el fin de una vez finalizado el programa, realizar un `dlclose` a todos los handlers del stack.


# Ejemplo
```
Bienvenidos a un nuevo elepeduelo
Ingrese el nombre del primer entrenador: 
> Gaspar
Ingrese el nombre del segundo entrenador: 
> Sebastian
Ingrese la cantidad de elepemones:
> 1
Gaspar, elije tus elepemones (uno a uno y utiizando numeros):
1. Lugia
2. Blastoise
3. Vinasaur
4. Charizard
5. Charmander

> 3
Sebastian, elije tus elepemones (uno a uno y utiizando numeros):
1. Lugia
2. Blastoise
3. Charizard
4. Charmander

> 4
Elepemones Gaspar:
1. Vinasaur

---------
Elepemones Sebastian:
1. Charmander

---------
IT'S TIME TO DU-DU-DU-DU-DUEL!!!11!!uno!
Gaspar, que elepemon ataca?
> Lugia
No tienes ese elepemon!, Gaspar, que elepemon ataca?
> *LISTA* 
Actualmente, tienes estos elepemones:
1. Vinasaur


Gaspar, que elepemon ataca?
> Vinasaur
Que ataque usara?
> *ATAQUES*
El elepemon Vinasaur tiene estos ataques:
Rayosolar
Latigocepa

Vinasaur, a que elepemon ataca?
> Charmander
Vinasaur ha usado Rayosolar contra Charmander
Ha causado un daño de 130 puntos de vida
No ha sido efectivo
El elepemon Charmander ha muerto! :(
El jugador Sebastian se ha quedado sin elepemones.

Felicidades Gaspar, has ganado!

```

