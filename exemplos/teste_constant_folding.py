# Teste específico para Constant Folding
# Esta otimização calcula expressões constantes em tempo de compilação

print("=== TESTE CONSTANT FOLDING ===")

# Operações aritméticas básicas
a = 2 + 3          # Deve virar: local a = 5
b = 10 * 5         # Deve virar: local b = 50
c = 8 / 2          # Deve virar: local c = 4
d = 15 - 7         # Deve virar: local d = 8
e = 17 % 3         # Deve virar: local e = 2

# Expressões aninhadas
f = (2 + 3) * 4    # Deve virar: local f = 20
g = 2 * (3 + 4)    # Deve virar: local g = 14
h = (10 / 2) + (6 * 3)  # Deve virar: local h = 23

# Comparações lógicas
bool1 = 5 > 3      # Deve virar: local bool1 = 1 (true)
bool2 = 10 < 8     # Deve virar: local bool2 = 0 (false)
bool3 = 7 == 7     # Deve virar: local bool3 = 1 (true)

print("Resultados:", a, b, c, d, e)
print("Aninhadas:", f, g, h)
print("Lógicas:", bool1, bool2, bool3) 