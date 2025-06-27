# Teste específico para Dead Code Elimination
# Esta otimização remove código que nunca será executado

print("=== TESTE DEAD CODE ELIMINATION ===")

# Código após return (se suportado)
x = 10

# Código dentro de if(false) - deve ser removido
if False:
    codigo_morto1 = 100
    print("Nunca executado")

# Código dentro de if(true) - só o then deve permanecer
if True:
    codigo_vivo = 200
    print("Sempre executado")

# Expressões sem efeito - podem ser removidas
5 + 3              # Expressão calculada mas não usada
x * 2              # Resultado não atribuído

# Variáveis nunca usadas
variavel_nao_usada = 999

print("Código vivo:", codigo_vivo, x) 