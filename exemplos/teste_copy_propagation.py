# Teste específico para Copy Propagation
# Esta otimização elimina cópias desnecessárias de variáveis

print("=== TESTE COPY PROPAGATION ===")

# Cadeias de cópias simples
x = 42
y = x              # y é uma cópia de x
z = y              # z é uma cópia de y (que é cópia de x)

# Uso das variáveis copiadas
resultado1 = z + 10    # Pode usar x diretamente
resultado2 = y * 2     # Pode usar x diretamente

# Cadeias mais complexas
a = 100
b = a
c = b
d = c + 5          # Pode usar a diretamente

# Cópias com modificação
temp = x
final = temp + 1   # Pode usar x + 1 diretamente

print("Originais:", x, a)
print("Cópias:", y, z, b, c)
print("Resultados:", resultado1, resultado2, d, final) 