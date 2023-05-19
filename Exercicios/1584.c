// Fun��o para calcular o valor absoluto de um n�mero
int mod(int x){
  if(x < 0) return -1 * x; // Retorna o valor absoluto de x se x for negativo
  return x; // Retorna x se x for positivo ou zero
}

// Fun��o para calcular a dist�ncia de Manhattan entre dois pontos
int manhattandistance(int** points, int i, int j, int* pointsColSize){
  int* p1 = *(points + i); // Obt�m o ponteiro para a linha i da matriz de pontos
  int* p2 = *(points + j); // Obt�m o ponteiro para a linha j da matriz de pontos
  int distancia = 0; // Inicializa a dist�ncia como zero
  for(int k = 0; k < (*pointsColSize); k++){ // Percorre as colunas das linhas i e j
    distancia = distancia + mod(*(p1 + k) - *(p2 + k)); // Calcula a dist�ncia de Manhattan entre os pontos p1 e p2
  }
  return distancia; // Retorna a dist�ncia de Manhattan entre os pontos p1 e p2
}

// Fun��o para calcular o custo m�nimo de conex�o entre todos os pontos
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    int distancia = 0; // O custo final
    int distMinima; // Dist�ncia m�nima tempor�ria
    int dist; // Dist�ncia tempor�ria
    int S[pointsSize]; // O conjunto S (cont�m os v�rtices da MST)
    int top = 0; // �ndice do topo do conjunto S
    int present[pointsSize]; // Array que marca a presen�a dos v�rtices contidos em S
    int v2; // V�rtice, usado com distMinima para adicionar a S
    int edges[pointsSize]; // A dist�ncia m�nima para v�rtices (fora de S) a partir de v�rtices dentro de S

    // Inicializa��o dos arrays
    for(int j = 0; j < pointsSize; j++){
        edges[j] = INT_MAX; // Valor m�ximo para representar infinito
        present[j] = 0; // N�o presente
    }
    edges[0] = 1; // Definindo uma dist�ncia inicial para o primeiro v�rtice

    S[top] = 0; // Adicionando o primeiro elemento ao conjunto S
    top++;
    present[0] = 1; // Marcando o primeiro v�rtice como presente

    while(top != pointsSize){ // Enquanto o conjunto S n�o cont�m todos os v�rtices
        for(int j = 1; j < pointsSize; j++){
            // Ignora se o v�rtice j j� est� presente
            if(present[j] == 1) continue;

            dist = manhattandistance(points, S[top-1], j, pointsColSize); // Calcula a dist�ncia de Manhattan entre o v�rtice j e o �ltimo v�rtice adicionado a S

            if(edges[j] > dist){ // Atualiza a dist�ncia m�nima se a nova dist�ncia for menor
                edges[j] = dist;
            }
        }

        distMinima = INT_MAX; // Valor m�ximo para representar infinito
        for(int i = 0; i<pointsSize; i++){
            if(present[i] == 1) continue; // Ignora se o v�rtice i j� est� presente em S
            if(edges[i] < distMinima){ // Encontra a menor dist�ncia m�nima e o v�rtice correspondente
                distMinima = edges[i];
                v2 = i;
            }
        }
        S[top] = v2; // Adiciona o v�rtice v2 ao conjunto S
        top++;
        present[v2] = 1; // Marca o v�rtice v2 como presente
        distancia = distancia+distMinima; // Adiciona a dist�ncia m�nima ao custo total
    }

    return distancia; // Retorna o custo total (dist�ncia m�nima para conectar todos os pontos)
}
