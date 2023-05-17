// Função para calcular o valor absoluto de um número
int mod(int x){
  if(x < 0) return -1 * x; // Retorna o valor absoluto de x se x for negativo
  return x; // Retorna x se x for positivo ou zero
}

// Função para calcular a distância de Manhattan entre dois pontos
int manhattandistance(int** points, int i, int j, int* pointsColSize){
  int* p1 = *(points + i); // Obtém o ponteiro para a linha i da matriz de pontos
  int* p2 = *(points + j); // Obtém o ponteiro para a linha j da matriz de pontos
  int distancia = 0; // Inicializa a distância como zero
  for(int k = 0; k < (*pointsColSize); k++){ // Percorre as colunas das linhas i e j
    distancia = distancia + mod(*(p1 + k) - *(p2 + k)); // Calcula a distância de Manhattan entre os pontos p1 e p2
  }
  return distancia; // Retorna a distância de Manhattan entre os pontos p1 e p2
}

// Função para calcular o custo mínimo de conexão entre todos os pontos
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    int distancia = 0; // O custo final
    int distMinima; // Distância mínima temporária
    int dist; // Distância temporária
    int S[pointsSize]; // O conjunto S (contém os vértices da MST)
    int top = 0; // Índice do topo do conjunto S
    int present[pointsSize]; // Array que marca a presença dos vértices contidos em S
    int v2; // Vértice, usado com distMinima para adicionar a S
    int edges[pointsSize]; // A distância mínima para vértices (fora de S) a partir de vértices dentro de S

    // Inicialização dos arrays
    for(int j = 0; j < pointsSize; j++){
        edges[j] = INT_MAX; // Valor máximo para representar infinito
        present[j] = 0; // Não presente
    }
    edges[0] = 1; // Definindo uma distância inicial para o primeiro vértice

    S[top] = 0; // Adicionando o primeiro elemento ao conjunto S
    top++;
    present[0] = 1; // Marcando o primeiro vértice como presente

    while(top != pointsSize){ // Enquanto o conjunto S não contém todos os vértices
        for(int j = 1; j < pointsSize; j++){
            // Ignora se o vértice j já está presente
            if(present[j] == 1) continue;

            dist = manhattandistance(points, S[top-1], j, pointsColSize); // Calcula a distância de Manhattan entre o vértice j e o último vértice adicionado a S

            if(edges[j] > dist){ // Atualiza a distância mínima se a nova distância for menor
                edges[j] = dist;
            }
        }

        distMinima = INT_MAX; // Valor máximo para representar infinito
        for(int i = 0; i<pointsSize; i++){
            if(present[i] == 1) continue; // Ignora se o vértice i já está presente em S
            if(edges[i] < distMinima){ // Encontra a menor distância mínima e o vértice correspondente
                distMinima = edges[i];
                v2 = i;
            }
        }
        S[top] = v2; // Adiciona o vértice v2 ao conjunto S
        top++;
        present[v2] = 1; // Marca o vértice v2 como presente
        distancia = distancia+distMinima; // Adiciona a distância mínima ao custo total
    }

    return distancia; // Retorna o custo total (distância mínima para conectar todos os pontos)
}
