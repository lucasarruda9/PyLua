# Teste específico para Algebraic Simplification
# Esta otimização aplica identidades algébricas conhecidas

print("=== TESTE ALGEBRAIC SIMPLIFICATION ===")

x = 42

# Identidades de soma
soma_zero = x + 0      # Deve virar: local soma_zero = x
zero_soma = 0 + x      # Deve virar: local zero_soma = x

# Identidades de multiplicação
mult_um = x * 1        # Deve virar: local mult_um = x
um_mult = 1 * x        # Deve virar: local um_mult = x
mult_zero = x * 0      # Deve virar: local mult_zero = 0

# Identidades de subtração
sub_zero = x - 0       # Deve virar: local sub_zero = x
sub_self = x - x       # Deve virar: local sub_self = 0

# Identidades de divisão
div_um = x / 1         # Deve virar: local div_um = x
div_self = x / x       # Deve virar: local div_self = 1

print("Soma:", soma_zero, zero_soma)
print("Mult:", mult_um, um_mult, mult_zero)
print("Sub:", sub_zero, sub_self)
print("Div:", div_um, div_self) 