#include <stdio.h>
#include "../../ast/ast.h"

int main() {
    printf("Testando nós de estruturas de controle na AST:\n\n");

    // IF simples: if (True) { 42 }
    No* nif = CriarNoIf(CriarNoBool(1), CriarNoInteiro(42), NULL);
    printf("NoIf (sem else):\n");
    imprimeArvore(nif, 0);
    DesalocarArvore(nif);

    // IF-ELSE: if (False) { 1 } else { 2 }
    No* nifelse = CriarNoIf(CriarNoBool(0), CriarNoInteiro(1), CriarNoInteiro(2));
    printf("\nNoIf (com else):\n");
    imprimeArvore(nifelse, 0);
    DesalocarArvore(nifelse);

    // WHILE: while (x < 10) { x = x + 1 }
    No* cond = CriarNoOperador(CriarNoVariavel("x"), CriarNoInteiro(10), '<');
    No* corpo = CriaNoAtribuicao(CriarNoVariavel("x"), CriarNoOperador(CriarNoVariavel("x"), CriarNoInteiro(1), '+'));
    No* nwhile = CriarNoWhile(cond, corpo);
    printf("\nNoWhile:\n");
    imprimeArvore(nwhile, 0);
    DesalocarArvore(nwhile);

    // FOR: for i = 0 to 5 { print(i) }
    No* nfor = CriarNoFor(CriarNoVariavel("i"), CriarNoInteiro(0), CriarNoInteiro(5), CriarNoChamadaFuncao("print", AdicionarNoLista(NULL, CriarNoVariavel("i"))));
    printf("\nNoFor:\n");
    imprimeArvore(nfor, 0);
    DesalocarArvore(nfor);

    return 0;
}
