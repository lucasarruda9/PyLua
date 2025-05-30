#include <stdio.h>
#include "../../ast/ast.h"

int main() {
    printf("Testando criação de nós novos na AST:\n\n");

    No* nfloat = CriarNoFloat(3.14f);
    printf("NoFloat:\n");
    imprimeArvore(nfloat, 0);
    DesalocarArvore(nfloat);

    No* nstr = CriarNoString("hello");
    printf("\nNoString:\n");
    imprimeArvore(nstr, 0);
    DesalocarArvore(nstr);

    No* nbool = CriarNoBool(1);
    printf("\nNoBool:\n");
    imprimeArvore(nbool, 0);
    DesalocarArvore(nbool);

    // Bloco com dois literais
    ListaNo* lista = NULL;
    lista = AdicionarNoLista(lista, CriarNoInteiro(1));
    lista = AdicionarNoLista(lista, CriarNoFloat(2.5f));
    No* nbloco = CriarNoBloco(lista);
    printf("\nNoBloco:\n");
    imprimeArvore(nbloco, 0);
    DesalocarArvore(nbloco);

    // If simples
    No* nif = CriarNoIf(CriarNoBool(1), CriarNoInteiro(42), NULL);
    printf("\nNoIf:\n");
    imprimeArvore(nif, 0);
    DesalocarArvore(nif);

    // While simples
    No* nwhile = CriarNoWhile(CriarNoBool(0), CriarNoFloat(7.7f));
    printf("\nNoWhile:\n");
    imprimeArvore(nwhile, 0);
    DesalocarArvore(nwhile);

    // For simples
    No* nfor = CriarNoFor(CriarNoVariavel("i"), CriarNoInteiro(0), CriarNoInteiro(10), CriarNoFloat(1.1f));
    printf("\nNoFor:\n");
    imprimeArvore(nfor, 0);
    DesalocarArvore(nfor);

    // Função
    ListaNo* params = NULL;
    params = AdicionarNoLista(params, CriarNoVariavel("x"));
    No* nfunc = CriarNoFuncao("f", params, CriarNoInteiro(99));
    printf("\nNoFuncao:\n");
    imprimeArvore(nfunc, 0);
    DesalocarArvore(nfunc);

    // Chamada de função
    ListaNo* args = NULL;
    args = AdicionarNoLista(args, CriarNoFloat(8.8f));
    No* nchamada = CriarNoChamadaFuncao("f", args);
    printf("\nNoChamadaFuncao:\n");
    imprimeArvore(nchamada, 0);
    DesalocarArvore(nchamada);

    return 0;
}
