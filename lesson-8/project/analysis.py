# Función que calcula el puntaje de actividad de un usuario
# Recibe la cantidad de logins y de posts
def calculate_score(logins, posts):
    # Cada login vale 2 puntos y cada post vale 5 puntos
    return (logins * 2) + (posts * 5)
# Función que devuelve el estado del usuario según su puntaje
def get_status(score):
    # Si el puntaje es menor a 10, el usuario está inactivo
    if score < 10:
        return "Dormant"
    # Si es menor a 30, es un usuario regular
    elif score < 30:
        return "Regular"
    # Si no, se considera activo
    else:
        return "Active"
# Función principal de análisis
# Recibe la lista de usuarios del archivo JSON
def analyze_users(users):
    # Lista donde se guardan los resultados finales
    results = []

    # Variable para acumular el total de puntajes
    total_score = 0
    # Recorremos cada usuario del JSON
    for user in users:
        # Obtenemos el nombre o "Unknown" si no existe
        name = user.get("name", "Unknown")

        # Obtenemos logins y posts, si no existen se usa 0
        logins = user.get("logins", 0)
        posts = user.get("posts", 0)

        # Calculamos el puntaje usando la función
        score = calculate_score(logins, posts)

        # Determinamos el estado del usuario
        status = get_status(score)

        # Guardamos la información del usuario en un diccionario
        results.append({
            "user": name,
            "score": score,
            "status": status
        })

    # Calculamos el promedio
    # Si no hay usuarios, el promedio es 0
    avg = total_score / len(results) if results else 0

    # Devolvemos los resultados y el promedio
    return results, avg
