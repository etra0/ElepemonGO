# Tarea 1: "Elepemon GO"

|Integrante|Rol|
|----|----|
| Sebastián Aedo |201573057-1|
| Gaspar Correa |201573009-1|

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


# Milestones

|Función|Estado|
|----|----|
|`print_elepemon`|listo|
|`init_elepemon`|listo|
|`free_elepemon`|listo|
|`get_attacks_ids`|listo|
|`load_attacks`|Que retorna? - Casi listo|
|`unload_attacks`|listo|
|`push_elepemon`|listo|
|`get_elepemon`|listo|
|`free_elepemon_stack`|listo|

|To-Do|Estado|
|----|----|
|Deadpool|1|
|Hacer funciones ataque|8/8|
|Terminar el loop principal|1|
|Armar struct attack|listo|
|Documentar|0.5|

# Supuestos

* Se asume que no habrán elepemones con el mismo nombre.
* Se exige que el primer parametro sea el directorio donde estarán los ataques y el segundo el nombre del ini.
