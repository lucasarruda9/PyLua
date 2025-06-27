# Exemplo para testar otimizações
# Este arquivo contém código que pode ser otimizado

# Constant folding - expressões constantes que podem ser calculadas em tempo de compilação
x = 2 + 3 * 4
y = 10 - 5 + 1
z = (8 / 2) * 3

# Dead code elimination - código que nunca é executado ou não tem efeito
if True:
    print("Este código sempre executa")
else:
    print("Este código nunca executa")  # Dead code

if False:
    print("Este bloco inteiro é dead code")  # Dead code

# Expressões sem efeito colateral (dead code)
5 + 3  # Esta expressão não faz nada
x * 2  # Esta expressão não faz nada

# As-if optimization - simplificação de estruturas de controle
if 1:  # Condição sempre verdadeira
    a = 10

if 0:  # Condição sempre falsa
    b = 20
else:
    c = 30

# While com condição constante
while False:  # Loop que nunca executa
    print("Nunca imprime")

# Mais constant folding
resultado = 1 + 2 + 3 + 4 + 5
multiplicacao = 2 * 2 * 2 * 2

# Operações lógicas constantes
comparacao1 = 5 > 3  # True
comparacao2 = 10 < 5  # False
comparacao3 = 7 == 7  # True

print("Resultado:", resultado)
print("Multiplicação:", multiplicacao)
print("Comparações:", comparacao1, comparacao2, comparacao3) 