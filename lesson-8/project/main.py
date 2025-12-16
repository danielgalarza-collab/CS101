# Importamos sys para leer argumentos por consola
import sys

# Importamos json para leer archivos JSON
import json

# Importamos datetime para mostrar la fecha y hora del reporte
from datetime import datetime

# Importamos la función de análisis desde analysis.py
from analysis import analyze_users


# Función principal del programa
def main():
    # Verificamos que se haya pasado la ruta del archivo por consola
    if len(sys.argv) < 2:
        print("Usage: python main.py <data.json>")
        return

    # Guardamos la ruta del archivo JSON
    path = sys.argv[1]

    # Intentamos abrir y leer el archivo JSON
    try:
        with open(path, "r") as f:
            # Convertimos el contenido del archivo en un diccionario
            data = json.load(f)
    # Si el archivo no existe
    except FileNotFoundError:
        print("File not found")
        return
    # Si el archivo no tiene formato JSON válido
    except json.JSONDecodeError:
        print("Invalid JSON file")
        return

    # Analizamos los usuarios usando la función del otro módulo
    results, avg = analyze_users(data["users"])

    # Imprimimos el encabezado del reporte
    print("\n--- User Activity Report ---")
    print(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("-" * 30)

    # Recorremos los resultados y los mostramos por pantalla
    for r in results:
        print(f"{r['user']:<15} | Score: {r['score']} | Status: {r['status']}")

    # Mostramos el promedio de actividad
    print("-" * 30)
    print(f"Average score: {avg:.2f}")

    # Mostramos una recomendación según el promedio
    if avg > 20:
        print("Recommendation: System performance is healthy.")
    else:
        print("Recommendation: Investigate user engagement.")


# Punto de entrada del programa
# Esto evita que el código se ejecute si el archivo se importa
if __name__ == "__main__":
    main()
