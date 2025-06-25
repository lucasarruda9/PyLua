# testa loops mais complexos
# pra ver se não quebra nada

# loop simples
contador = 0
while contador < 3:
    print("Contador:", contador)
    contador += 1

# loop aninhado needled loop
for i in range(3):
    for j in range(2):
        produto = i * j
        if produto > 0:
            print("i:", i, "j:", j, "produto:", produto)

# teste com break e continue 
x = 0
while x < 10:
    x += 1
    if x == 5:
        continue
    if x == 8:
        break
    print("x =", x)
