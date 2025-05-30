#include <stdio.h>
#include "../../ast/ast.h"

int main() {
    printf("Testando nós de função e chamada de função na AST:\n\n");

    // Função: def soma(x, y): return x + y
    ListaNo* params = NULL;
    params = AdicionarNoLista(params, CriarNoVariavel("x"));
    params = AdicionarNoLista(params, CriarNoVariavel("y"));
    No* corpo = CriarNoOperador(CriarNoVariavel("x"), CriarNoVariavel("y"), '+');
    No* nfunc = CriarNoFuncao("soma", params, corpo);
    printf("NoFuncao:\n");
    imprimeArvore(nfunc, 0);
    DesalocarArvore(nfunc);

    // Chamada: soma(2, 3)
    ListaNo* args = NULL;
    args = AdicionarNoLista(args, CriarNoInteiro(2));
    args = AdicionarNoLista(args, CriarNoInteiro(3));
    No* nchamada = CriarNoChamadaFuncao("soma", args);
    printf("\nNoChamadaFuncao:\n");
    imprimeArvore(nchamada, 0);
    DesalocarArvore(nchamada);

    return 0;
}
