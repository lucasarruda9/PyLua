# Teste específico para As-if Optimization
# Esta otimização simplifica estruturas de controle com condições constantes

print("=== TESTE AS-IF OPTIMIZATION ===")

# If com condição sempre true - só o then deve permanecer
if True:
    a = 10
    print("Sempre executado")

# If com condição sempre false - só o else deve permanecer
if False:
    b = 20
else:
    c = 30
    print("Sempre no else")

# While com condição sempre false - pode ser removido completamente
x = 0
# while False:  # Comentado pois pode causar erro sintático
#     x = x + 1

# Condições que podem ser simplificadas
if 5 > 3:  # Sempre true
    resultado_true = "Cinco é maior que três"

if 2 > 10:  # Sempre false
    resultado_false = "Nunca executado"
else:
    resultado_else = "Dois não é maior que dez"

print("Resultados:", a, c)
print("Condições:", resultado_true, resultado_else) 