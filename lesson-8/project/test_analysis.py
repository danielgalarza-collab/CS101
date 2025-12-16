# Importamos las funciones que queremos probar
from analysis import calculate_score, get_status


# Test para verificar el cálculo del puntaje
def test_calculate_score():
    # 1 login (2 puntos) + 1 post (5 puntos) = 7
    assert calculate_score(1, 1) == 7
    # Sin actividad, el puntaje debe ser 0
    assert calculate_score(0, 0) == 0


# Test para verificar el estado del usuario
def test_get_status():
    # Puntaje bajo
    assert get_status(5) == "Dormant"
    # Puntaje medio
    assert get_status(20) == "Regular"
    # Puntaje alto
    assert get_status(50) == "Active"


# Mensaje simple para indicar que los tests terminaron
print("Tests OK")
