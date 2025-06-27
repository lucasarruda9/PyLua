# Teste de otimizações básicas
# Demonstra constant folding funcionando

print("=== TESTE BÁSICO DE OTIMIZAÇÕES ===")

# Constant folding - expressões que devem ser calculadas
a = 2 + 3          # deve se tornar 5
b = 10 * 5         # deve se tornar 50  
c = 8 / 2          # deve se tornar 4
d = 15 - 7         # deve se tornar 8
e = 17 % 3         # deve se tornar 2

# Expressões mais complexas
f = (2 + 3) * 4    # deve se tornar 5 * 4 = 20
g = 2 * (3 + 4)    # deve se tornar 2 * 7 = 14
h = (10 / 2) + (6 * 3)  # deve se tornar 5 + 18 = 23

# Operações lógicas constantes
bool1 = 5 > 3      # deve se tornar True
bool2 = 10 < 8     # deve se tornar False
bool3 = 7 == 7     # deve se tornar True

print("Resultados:", a, b, c, d, e)
print("Complexas:", f, g, h)
print("Lógicas:", bool1, bool2, bool3) 