# Tarea 1: "Elepemon GO"

|Integrante|Rol|Usuario|
|----|----|----|
| Sebastián Aedo |201573057-1|saedo|
| Gaspar Correa |201573009-1|gcorrea|

Para compilar el código correctamente, necesitamos [**inih**](https://github.com/benhoyt/inih) en la carpeta raíz del código.

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
* Se exige que al escoger los elepemones se utilizen números.

# Ejemplo
```bash

Bienvenidos a un nuevo elepeduelo
Ingrese el nombre del primer entrenador:
> Ingrese el nombre del segundo entrenador:
> Ingrese la cantidad de elepemones:
 
> Gaspar, elije tus elepemones (uno a uno y utiizando numeros):
1. Lugia
2. Blastoise
3. Vinasaur
4. Charizard
5. Charmander
 
> Sebastian, elije tus elepemones (uno a uno y utiizando numeros):
1. Lugia
2. Blastoise
3. Charizard
4. Charmander
 
> Elepemones Gaspar:
1. Vinasaur
 
---------
Elepemones Sebastian:
1. Charmander
 
---------
IT'S TIME TO DU-DU-DU-DU-DUEL!!!11!!uno!
Gaspar, que elepemon ataca?
> Que ataque usara?
> Vinasaur, a que elepemon ataca?
> Vinasaur ha usado Latigocepa contra Charmander
Ha causado un daño de 1594 puntos de vida
No ha sido efectivo
Charmander ha quedado envenenado
El elepemon Charmander ha muerto! :(
El jugador Sebastian se ha quedado sin elepemones.
 
Felicidades Gaspar, has ganado!

```

