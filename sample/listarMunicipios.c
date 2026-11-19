#include <stdio.h>

#include "ibge_api.h"

/* Callback executado uma vez para cada município retornado pela API. */
static int mostrarMunicipio(int codigo, const char *nome, void *contexto) {
    /* Este exemplo não precisa de dados adicionais no contexto. */
    (void)contexto;

    /* Exibe o código IBGE e o nome do município atual. */
    printf("%d: %s\n", codigo, nome);

    /* Um valor diferente de zero solicita que a listagem continue. */
    return 1;
}

int main(void) {
    /* Percorre os municípios e chama mostrarMunicipio para cada um deles. */
    IbgeStatus status = ibgeListarMunicipios(mostrarMunicipio, NULL);

    /* Exibe o motivo caso a consulta ou a listagem tenha falhado. */
    if (status != IBGE_OK) {
        fprintf(stderr, "Erro: %s\n", ibgeStatusMensagem(status));
        return 1;
    }

    return 0;
}
