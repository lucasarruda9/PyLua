# teste mais avançado com funções
# pra ver se o gerador aguenta

def somar(a, b):
    return a + b

def calcular_media(lista):
    total = 0
    for item in lista:
        total += item
    return total / len(lista)

# testando as funções
resultado1 = somar(10, 20)
numeros = [1, 2, 3, 4, 5]
media = calcular_media(numeros)

print("Resultado:", resultado1)
print("Média:", media)
