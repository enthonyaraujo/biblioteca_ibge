#include <errno.h>  // Erros de conversão.
#include <limits.h> // Limites de inteiros.
#include <stdio.h>  // Entrada e saída.
#include <stdlib.h> // Conversão numérica.

#include "ibge_api.h" // Interface da biblioteca.

static int lerCodigo(const char *texto,
                     int *codigo) { // Valida o código informado.
  char *fim;                        // Marca o fim da conversão.
  long valor;                       // Armazena o valor lido.

  errno = 0;                       // Limpa erro anterior.
  valor = strtol(texto, &fim, 10); // Converte texto em número.
  if (errno != 0 || fim == texto ||
      *fim != '\0' ||                        // Verifica conversão inválida.
      valor < 1000000L || valor > INT_MAX) { // Verifica o intervalo.
    return 0;                                // Informa falha.
  } // Finaliza a validação.
  *codigo = (int)valor; // Guarda o código válido.
  return 1;             // Informa sucesso.
}

int main(int argc, char *argv[]) {
  Municipio municipio; // Guarda os dados consultados.
  IbgeStatus status;   // Guarda o resultado.
  int codigo;          // Guarda o código IBGE.

  if (argc != 2 || !lerCodigo(argv[1], &codigo)) { // Valida o argumento.
    fprintf(stderr, "Uso: %s <codigo_ibge_de_7_digitos>\n",
            argv[0]); // Mostra o uso.
    return 1;         // Encerra com erro.
  }

  status = ibgeBuscarMunicipio(codigo, &municipio); // Consulta o município.
  if (status != IBGE_OK) {                          // Verifica a consulta.
    fprintf(stderr, "Erro na consulta: %s\n",
            ibgeStatusMensagem(status)); // Mostra o erro.
    return 1;                            // Encerra com erro.
  }

  printf("Codigo: %d\n", municipio.codigo);  // Mostra o código.
  printf("Municipio: %s\n", municipio.nome); // Mostra o nome.
  printf("UF: %s\n", municipio.uf);          // Mostra a UF.
  printf("Regiao: %s\n", municipio.regiao);  // Mostra a região.
  printf("Latitude aproximada: %.6f\n",
         municipio.latitude); // Mostra a latitude.
  printf("Longitude aproximada: %.6f\n",
         municipio.longitude); // Mostra a longitude.
  return 0;
}
