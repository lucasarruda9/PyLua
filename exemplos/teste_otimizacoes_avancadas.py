# Teste completo de otimizações avançadas
# Este arquivo demonstra todas as otimizações implementadas

print("=== TESTE DE OTIMIZAÇÕES AVANÇADAS ===")

# ==== CONSTANT PROPAGATION ====
print("--- Constant Propagation ---")
x = 42
y = x  # y deve ser propagado como 42
z = y + 10  # deve se tornar 42 + 10 = 52

# ==== COPY PROPAGATION ====
print("--- Copy Propagation ---")
a = x  # a é cópia de x
b = a  # b é cópia de a (que é cópia de x)
c = b + 5  # deve usar x diretamente

# ==== ALGEBRAIC SIMPLIFICATION ====
print("--- Algebraic Simplification ---")
# Identidades aditivas
soma_zero = x + 0  # deve se tornar apenas x
zero_soma = 0 + x  # deve se tornar apenas x

# Identidades multiplicativas  
mult_um = x * 1    # deve se tornar apenas x
um_mult = 1 * x    # deve se tornar apenas x
mult_zero = x * 0  # deve se tornar 0

# Identidades de subtração
sub_zero = x - 0   # deve se tornar apenas x
sub_self = x - x   # deve se tornar 0

# Identidades de divisão
div_um = x / 1     # deve se tornar apenas x
div_self = x / x   # deve se tornar 1

# Identidades de potenciação
pot_zero = x ** 0  # deve se tornar 1
pot_um = x ** 1    # deve se tornar apenas x
um_pot = 1 ** x    # deve se tornar 1

# ==== STRENGTH REDUCTION ====
print("--- Strength Reduction ---")
# Multiplicação por 2 -> adição
mult_dois = x * 2  # deve se tornar x + x

# Potência de 2 -> multiplicação
quad = x ** 2      # deve se tornar x * x

# Multiplicação por potência de 2 -> shift
mult_quatro = x * 4   # deve se tornar x << 2
mult_oito = x * 8     # deve se tornar x << 3

# Divisão por potência de 2 -> shift
div_quatro = x / 4    # deve se tornar x >> 2
div_oito = x / 8      # deve se tornar x >> 3

# ==== CONSTANT FOLDING COMPLEXO ====
print("--- Constant Folding Complexo ---")
# Expressões aninhadas que devem ser calculadas
complexa1 = (2 + 3) * (4 - 1)  # deve se tornar 5 * 3 = 15
complexa2 = 2 ** 3 + 4 * 5     # deve se tornar 8 + 20 = 28
complexa3 = (10 / 2) - (6 % 4) # deve se tornar 5 - 2 = 3

# Operações lógicas constantes
bool1 = 5 > 3    # deve se tornar True
bool2 = 10 < 8   # deve se tornar False
bool3 = 7 == 7   # deve se tornar True
bool4 = 4 != 4   # deve se tornar False

# ==== COMBINAÇÕES COMPLEXAS ====
print("--- Combinações Complexas ---")
# Múltiplas otimizações aplicadas
resultado1 = ((x + 0) * 1) + (y - 0)  # deve se tornar x + y
resultado2 = (a / 1) * (2 ** 1)       # deve se tornar a * 2 -> a + a
resultado3 = (x * 4) / 2              # deve se tornar (x << 2) >> 1

# Propagação seguida de simplificação
temp = 100
final = temp + 0 - 0 * 5 + 1 * temp  # deve se tornar 100 + 100 = 200

print("Resultado final:", final)
print("=== FIM DOS TESTES ===") 