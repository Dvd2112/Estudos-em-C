#include <stdio.h>

// Funções de cálculo
float margemBruta(float lucroBruto, float receitaLiquida) {
    return lucroBruto / receitaLiquida;
}

float margemOperacional(float EBIT, float receitaLiquida) {
    return EBIT / receitaLiquida;
}

float margemEBITDA(float EBITDA, float receitaLiquida) {
    return EBITDA / receitaLiquida;
}

float margemLiquida(float lucroLiquido, float receitaLiquida) {
    return lucroLiquido / receitaLiquida;
}

float ROA(float lucroLiquido, float ativoTotal) {
    return lucroLiquido / ativoTotal;
}

float ROE(float lucroLiquido, float patrimonioLiquido) {
    return lucroLiquido / patrimonioLiquido;
}

float liquidezCorrente(float ativoCirculante, float passivoCirculante) {
    return ativoCirculante / passivoCirculante;
}

float liquidezSeca(float ativoCirculante, float estoques, float passivoCirculante) {
    return (ativoCirculante - estoques) / passivoCirculante;
}

float liquidezImediata(float caixa, float passivoCirculante) {
    return caixa / passivoCirculante;
}

float endividamentoGeral(float passivoTotal, float ativoTotal) {
    return passivoTotal / ativoTotal;
}

float composicaoEndividamento(float passivoCirculante, float passivoTotal) {
    return passivoCirculante / passivoTotal;
}

float alavancagemFinanceira(float ativoTotal, float patrimonioLiquido) {
    return ativoTotal / patrimonioLiquido;
}

float giroAtivo(float receitaLiquida, float ativoTotal) {
    return receitaLiquida / ativoTotal;
}

float prazoMedioRecebimento(float clientes, float receitaLiquida) {
    return (clientes / receitaLiquida) * 360;
}

float prazoMedioPagamento(float fornecedores, float compras) {
    return (fornecedores / compras) * 360;
}

float prazoMedioEstoque(float estoques, float custoVendas) {
    return (estoques / custoVendas) * 360;
}

int main() {
    int opcao;
    printf("Escolha o indicador que deseja calcular:\n");
    printf("1 - Margem Bruta\n2 - Margem Operacional\n3 - Margem EBITDA\n4 - Margem Liquida\n");
    printf("5 - ROA\n6 - ROE\n7 - Liquidez Corrente\n8 - Liquidez Seca\n9 - Liquidez Imediata\n");
    printf("10 - Endividamento Geral\n11 - Composicao do Endividamento\n12 - Alavancagem Financeira\n");
    printf("13 - Giro do Ativo\n14 - Prazo Medio de Recebimento\n15 - Prazo Medio de Pagamento\n16 - Prazo Medio de Estoque\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    float a, b, c, resultado;

    switch (opcao) {
        case 1:
            printf("Lucro Bruto: "); scanf("%f", &a);
            printf("Receita Liquida: "); scanf("%f", &b);
            resultado = margemBruta(a, b);
            break;
        case 2:
            printf("EBIT: "); scanf("%f", &a);
            printf("Receita Liquida: "); scanf("%f", &b);
            resultado = margemOperacional(a, b);
            break;
        case 3:
            printf("EBITDA: "); scanf("%f", &a);
            printf("Receita Liquida: "); scanf("%f", &b);
            resultado = margemEBITDA(a, b);
            break;
        case 4:
            printf("Lucro Liquido: "); scanf("%f", &a);
            printf("Receita Liquida: "); scanf("%f", &b);
            resultado = margemLiquida(a, b);
            break;
        case 5:
            printf("Lucro Liquido: "); scanf("%f", &a);
            printf("Ativo Total: "); scanf("%f", &b);
            resultado = ROA(a, b);
            break;
        case 6:
            printf("Lucro Liquido: "); scanf("%f", &a);
            printf("Patrimonio Liquido: "); scanf("%f", &b);
            resultado = ROE(a, b);
            break;
        case 7:
            printf("Ativo Circulante: "); scanf("%f", &a);
            printf("Passivo Circulante: "); scanf("%f", &b);
            resultado = liquidezCorrente(a, b);
            break;
        case 8:
            printf("Ativo Circulante: "); scanf("%f", &a);
            printf("Estoques: "); scanf("%f", &b);
            printf("Passivo Circulante: "); scanf("%f", &c);
            resultado = liquidezSeca(a, b, c);
            break;
        case 9:
            printf("Caixa e Equivalentes: "); scanf("%f", &a);
            printf("Passivo Circulante: "); scanf("%f", &b);
            resultado = liquidezImediata(a, b);
            break;
        case 10:
            printf("Passivo Total: "); scanf("%f", &a);
            printf("Ativo Total: "); scanf("%f", &b);
            resultado = endividamentoGeral(a, b);
            break;
        case 11:
            printf("Passivo Circulante: "); scanf("%f", &a);
            printf("Passivo Total: "); scanf("%f", &b);
            resultado = composicaoEndividamento(a, b);
            break;
        case 12:
            printf("Ativo Total: "); scanf("%f", &a);
            printf("Patrimonio Liquido: "); scanf("%f", &b);
            resultado = alavancagemFinanceira(a, b);
            break;
        case 13:
            printf("Receita Liquida: "); scanf("%f", &a);
            printf("Ativo Total: "); scanf("%f", &b);
            resultado = giroAtivo(a, b);
            break;
        case 14:
            printf("Clientes: "); scanf("%f", &a);
            printf("Receita Liquida: "); scanf("%f", &b);
            resultado = prazoMedioRecebimento(a, b);
            break;
        case 15:
            printf("Fornecedores: "); scanf("%f", &a);
            printf("Compras: "); scanf("%f", &b);
            resultado = prazoMedioPagamento(a, b);
            break;
        case 16:
            printf("Estoques: "); scanf("%f", &a);
            printf("Custo das Vendas: "); scanf("%f", &b);
            resultado = prazoMedioEstoque(a, b);
            break;
        default:
            printf("Opcao invalida!\n");
            return 1;
    }

    printf("Resultado: %.2f\n", resultado);
    return 0;
}
