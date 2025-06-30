# Teste específico para Strength Reduction
# Esta otimização substitui operações caras por equivalentes mais eficientes

print("=== TESTE STRENGTH REDUCTION ===")

x = 10

# Multiplicação por potências de 2 (pode virar shift)
mult_dois = x * 2      # Pode virar: x + x
mult_quatro = x * 4    # Pode virar: x << 2
mult_oito = x * 8      # Pode virar: x << 3

# Divisão por potências de 2 (pode virar shift)
div_dois = x / 2       # Pode virar: x >> 1
div_quatro = x / 4     # Pode virar: x >> 2

# Potenciação simples
quad = x * x           # x ao quadrado

# Operações que podem ser simplificadas
dobro = x + x          # Equivalente a x * 2

print("Multiplicações:", mult_dois, mult_quatro, mult_oito)
print("Divisões:", div_dois, div_quatro)
print("Outros:", quad, dobro) 