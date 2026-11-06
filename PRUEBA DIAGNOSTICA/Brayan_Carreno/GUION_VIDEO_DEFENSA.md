# Guion Oficial de Defensa Audiovisual - Prueba Diagnóstica (5%)
**Asignatura:** Lenguajes y Compiladores (Lapso 2026-II)  
**Profesor:** Msc. Félix Márquez  
**Estudiante:** Brayan Carreño | **C.I.:** V-32.015.527 | **Sección:** 01  
**Equipo:** ParseCore | **Eslogan:** *"Estructurando la sintaxis, optimizando la ejecución."*  
**Tiempo Límite:** Menos de 5:00 minutos | **Tiempo Estimado del Guion:** 4:30 minutos  

---

## 🎬 Recomendaciones Técnicas Previas a la Grabación

1. **Formato Obligatorio:** Horizontal (16:9, 1080p). Prohibido vertical/shorts.
2. **Cámara Web:** Activa en una esquina (ej. superior o inferior derecha) donde tu rostro se vea claramente durante todo el video.
3. **Grabación de Pantalla:** Usa OBS Studio o la barra de juegos de Windows (`Win + G` o `Win + Alt + R`).
4. **Disposición de Pantalla:**
   - Mitad izquierda: Visual Studio Code con el código abierto.
   - Mitad derecha: Terminal de PowerShell lista para compilar y ejecutar.
   - Zoom en VS Code (`Ctrl + +`) para que las fuentes se lean con total nitidez.

---

## ⏱️ Estructura Cronológica y Diálogos

```
[0:00 - 0:25] | Introducción Reglamentaria y Presentación Formal
[0:25 - 1:40] | Ejercicio 1: Validación y Benchmark del Caballo en Ajedrez
[1:40 - 2:50] | Ejercicio 2: Polinomio (x+1)^n y Pascal con Memoria Dinámica
[2:50 - 4:10] | Ejercicio 3: Analizador Léxico (Traductor de C a Español)
[4:10 - 4:35] | Conclusiones Técnicas y Despedida
```

---

### Bloque 1: Presentación Formal Obligatoria (0:00 - 0:25)
> **En pantalla:** Cámara web visible. Terminal o diapositiva de portada abierta con el nombre de ParseCore.

**Texto a decir:**
> *"Saludos cordiales, profesor Félix Márquez.  
> Somos el grupo **ParseCore**, bajo el eslogan: **'Estructurando la sintaxis, optimizando la ejecución.'**  
> Mi nombre es **Brayan Carreño**, portador de la cédula de identidad **V-32.015.527**, cursante de la sección **01** en la cátedra de **Lenguajes y Compiladores**.  
> A continuación, presento la defensa técnica y demostración en vivo de los tres ejercicios desarrollados para la Prueba Diagnóstica."*

---

### Bloque 2: Ejercicio 1 - Validación y Rendimiento de Caballo (0:25 - 1:40)
> **Acción en pantalla:** Muestra en VS Code `caballo.c` y corre en la terminal:  
> `gcc -O3 caballo.c -o caballo.exe; .\caballo.exe`

**Texto a decir:**
> *"Iniciamos con el **Ejercicio 1**, cuyo objetivo es validar una secuencia algebraica de movimientos de un caballo en un tablero de 8x8.  
> Matemáticamente, el caballo se desplaza en forma de L, lo cual verificamos mediante la condición cuadrática $\Delta x^2 + \Delta y^2 = 5$, equivalente a que el producto de las diferencias sea 2 y su suma sea 3.  
> 
> Como observamos en pantalla, nuestro algoritmo valida primero el prefijo 'K'; si se ingresa una pieza distinta como 'Q', reporta de inmediato: 'movimiento INCORRECTO falla letra Q no pertenece a un caballo'. Si el movimiento es geométricamente inválido o sale del tablero, identifica con exactitud el índice del fallo, superando todos los casos de prueba del enunciado.  
> 
> En cuanto al rendimiento, ejecutamos 10 repeticiones consecutivas de 500 movimientos:  
> En **Lenguaje C**, las 10 iteraciones toman apenas **0.12 milisegundos**.  
> Y en el benchmark para **$n = 100$**, **C completa la verificación en solo 2.39 microsegundos**, frente a **36.7 microsegundos en Python**, logrando un factor de aceleración de **15.3 veces más rápido en C**, debido a la gestión en registros y la ausencia del overhead de CPython."*

---

### Bloque 3: Ejercicio 2 - Polinomio $(x+1)^n$ y Pascal Dinámico (1:40 - 2:50)
> **Acción en pantalla:** Pasa a la carpeta `Ejercicio_2_Pascal_Polinomio` en VS Code. Muestra `pascal_polinomio.c` y ejecuta en terminal:  
> `gcc -O3 pascal_polinomio.c -o pascal_polinomio.exe -lm; .\pascal_polinomio.exe`

**Texto a decir:**
> *"Continuamos con el **Ejercicio 2**: generación de los coeficientes del polinomio $(x+1)^n$ aplicando el Triángulo de Pascal y su evaluación numérica paso a paso.  
> 
> La consigna exige expresamente el uso de **memoria dinámica**. En nuestro código en C, cada nivel del triángulo se reserva dinámicamente en el Heap con `malloc`, se calcula sumando los términos contiguos del nivel anterior, y se libera inmediatamente la fila previa con `free` para garantizar cero fugas de memoria.  
> 
> Además, resolvimos un desafío crítico: para **$n = 100$**, el coeficiente central supera los $10^{29}$ (29 dígitos), lo que desborda un entero de 64 bits en C. Implementamos una estructura `BigInt` de alta precisión que nos permite calcular el valor exacto: 100 quintillones sin ninguna pérdida de precisión.  
> 
> Al evaluar con $x = 2.0$ para $n = 4$, vemos el desglose paso a paso término a término, totalizando exactamente **81.0**, coincidiendo con la fórmula $(2+1)^4$.  
> En la prueba comparativa de $n = 100$, C genera la fila y gestiona la memoria dinámica en **184 microsegundos**."*

---

### Bloque 4: Ejercicio 3 - Analizador Léxico C a Español (2:50 - 4:10)
> **Acción en pantalla:** Abre `lexer_traductor.c` y `programa_prueba.c`. Corre en terminal:  
> `gcc -O3 lexer_traductor.c -o lexer_traductor.exe; .\lexer_traductor.exe`  
> Abre `programa_traducido.c` al lado para comparar.

**Texto a decir:**
> *"Llegamos al **Ejercicio 3**, el núcleo de nuestra asignatura: la construcción de un **Analizador Léxico (Lexer)** que carga un programa en C dinámicamente en memoria RAM y traduce sus palabras reservadas al español.  
> 
> Primero, usamos `fseek`, `ftell` y `malloc` para alojar dinámicamente en memoria el tamaño exacto del archivo fuente.  
> Luego, nuestro lexer implementa un autómata finito determinista que reconoce tokens caracter a caracter.  
> 
> Es fundamental destacar las reglas de compilación aplicadas:  
> 1. **Literales de cadena:** Si dentro de un `printf` aparece la palabra 'if' o 'for', el lexer la preserva intacta porque pertenece a un string.  
> 2. **Comentarios:** El contenido dentro de `//` o `/* */` se mantiene inalterado.  
> 3. **Subcadenas:** Variables como 'contador_while' no se alteran porque son identificadores completos.  
> 
> Al ejecutar el traductor sobre nuestro archivo de prueba de 837 bytes, vemos que 'int' se convierte en 'entero', 'if' en 'si', 'else' en 'sino', 'while' en 'mientras' y 'return' en 'retornar', generando el archivo traducido y emitiendo una tabla estadística con la frecuencia de cada token reconocido."*

---

### Bloque 5: Conclusiones y Despedida (4:10 - 4:35)
> **Acción en pantalla:** Vuelve a la cámara web o al repositorio de GitHub en el navegador ([github.com/Bryd3n/lyc-parsecore](https://github.com/Bryd3n/lyc-parsecore)).

**Texto a decir:**
> *"En conclusión, hemos implementado con éxito los tres requerimientos técnicos cumpliendo estrictamente con la gestión de memoria dinámica, la prevención de desbordamientos y el análisis sintáctico-léxico.  
> Todo el código fuente, los scripts comparativos y las salidas de ejecución se encuentran organizados y versionados en el repositorio de nuestro equipo **ParseCore**.  
> 
> Muchísimas gracias por su atención, profesor Félix Márquez. Quedo atento a su evaluación."*

---

## 📌 Checklist de Verificación Final Antes de Subir el Video

- [ ] Duración del archivo de video: **entre 4:15 y 4:50 minutos** (nunca pasar de 5:00).
- [ ] Tu rostro y voz se perciben con total claridad.
- [ ] El código y las terminales tienen tamaño de letra legible.
- [ ] Subido a **Google Drive** con permiso configurado en: **"Cualquier persona que tenga el enlace puede ver"** (Acceso público).
- [ ] Copiar el enlace en el archivo:
  [`video_defensa.txt`](file:///C:/Users/bc151/Documents/UNIVERSIDAD/Semestre%20VII/Lenguajes%20y%20Compiladores/01_Prueba_Diagnostica/Brayan_Carreno/video_defensa.txt)
- [ ] Hacer `git add`, `git commit` y `git push` en `lyc-parsecore`.
