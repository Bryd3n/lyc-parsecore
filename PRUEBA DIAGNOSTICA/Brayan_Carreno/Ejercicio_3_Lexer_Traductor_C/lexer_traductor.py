"""
Lenguajes y Compiladores - Semestre VII (UNEG)
Prueba Diagnostica - Ejercicio 3: Analizador Lexico (Traductor de C a Espanol)
Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
Grupo: ParseCore ("Estructurando la sintaxis, optimizando la ejecucion.")
Profesor: Msc. Felix Marquez
"""

import os
import sys

# Tabla de palabras reservadas de C y su traduccion oficial al espanol
TABLA_RESERVADAS = {
    "if": "si",
    "else": "sino",
    "while": "mientras",
    "for": "para",
    "do": "hacer",
    "int": "entero",
    "float": "flotante",
    "char": "caracter",
    "double": "doble",
    "void": "vacio",
    "return": "retornar",
    "struct": "estructura",
    "typedef": "definir_tipo",
    "switch": "segun",
    "case": "caso",
    "break": "romper",
    "continue": "continuar",
    "default": "defecto",
    "sizeof": "tamano_de",
    "const": "constante",
    "static": "estatico",
    "unsigned": "sin_signo",
    "signed": "con_signo",
    "long": "largo",
    "short": "corto"
}

def analizar_y_traducir_codigo(ruta_origen: str, ruta_destino: str):
    """
    Carga dinamicamente el archivo fuente en memoria y ejecuta el analizador lexico
    preservando intactos comentarios, cadenas de texto y literales de caracter.
    """
    # 1. Carga dinamica en memoria
    if not os.path.exists(ruta_origen):
        print(f"[ERROR] No existe el archivo de entrada: {ruta_origen}")
        return False
        
    with open(ruta_origen, "r", encoding="utf-8", errors="ignore") as f:
        codigo = f.read()
        
    tamano = len(codigo)
    i = 0
    salida = []
    conteo_tokens = {k: 0 for k in TABLA_RESERVADAS}
    total_identificadores = 0
    total_traducidos = 0
    
    # 2. Automata Finito Determinista (DFA)
    while i < tamano:
        c = codigo[i]
        
        # Literal de Cadena: "..." (Preservar)
        if c == '"':
            salida.append(c)
            i += 1
            while i < tamano:
                sc = codigo[i]
                salida.append(sc)
                if sc == '\\' and i + 1 < tamano:
                    i += 1
                    salida.append(codigo[i])
                elif sc == '"':
                    i += 1
                    break
                i += 1
            continue
            
        # Literal de Caracter: '...' (Preservar)
        if c == "'":
            salida.append(c)
            i += 1
            while i < tamano:
                sc = codigo[i]
                salida.append(sc)
                if sc == '\\' and i + 1 < tamano:
                    i += 1
                    salida.append(codigo[i])
                elif sc == "'":
                    i += 1
                    break
                i += 1
            continue
            
        # Comentarios: // o /* ... */
        if c == '/' and i + 1 < tamano:
            sig = codigo[i + 1]
            if sig == '/':
                salida.append(c)
                salida.append(sig)
                i += 2
                while i < tamano and codigo[i] != '\n':
                    salida.append(codigo[i])
                    i += 1
                continue
            elif sig == '*':
                salida.append(c)
                salida.append(sig)
                i += 2
                while i < tamano:
                    if codigo[i] == '*' and i + 1 < tamano and codigo[i + 1] == '/':
                        salida.append('*')
                        salida.append('/')
                        i += 2
                        break
                    salida.append(codigo[i])
                    i += 1
                continue
                
        # Identificadores y Palabras Clave: [a-zA-Z_][a-zA-Z0-9_]*
        if c.isalpha() or c == '_':
            inicio = i
            while i < tamano and (codigo[i].isalnum() or codigo[i] == '_'):
                i += 1
            palabra = codigo[inicio:i]
            total_identificadores += 1
            
            if palabra in TABLA_RESERVADAS:
                salida.append(TABLA_RESERVADAS[palabra])
                conteo_tokens[palabra] += 1
                total_traducidos += 1
            else:
                salida.append(palabra)
            continue
            
        # Operadores, espacios, puntuacion
        salida.append(c)
        i += 1
        
    resultado_texto = "".join(salida)
    
    with open(ruta_destino, "w", encoding="utf-8") as f_out:
        f_out.write(resultado_texto)
        
    # Reporte Estadístico
    print("=" * 70)
    print("   ESTADISTICAS DEL ANALIZADOR LEXICO (Python)")
    print("=" * 70)
    print(f"Caracteres procesados en RAM : {tamano} bytes")
    print(f"Total identificadores leidos : {total_identificadores}")
    print(f"Palabras reservadas traducidas: {total_traducidos}\n")
    print(f"{'Palabra en C':<18} | {'Traduccion (ES)':<18} | {'Frecuencia':<10}")
    print("-" * 52)
    for kw, cnt in conteo_tokens.items():
        if cnt > 0:
            print(f"{kw:<18} | {TABLA_RESERVADAS[kw]:<18} | {cnt:<10}")
    print("-" * 52)
    print(f"[EXITO] Archivo traducido generado en: {ruta_destino}\n")
    return True

if __name__ == "__main__":
    dir_actual = os.path.dirname(os.path.abspath(__file__))
    orig = os.path.join(dir_actual, "programa_prueba.c")
    dest = os.path.join(dir_actual, "programa_traducido_py.c")
    analizar_y_traducir_codigo(orig, dest)
