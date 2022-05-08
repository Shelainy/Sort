#include <cstdlib>
#include <ctime>
#include <iostream>
#include <new>
using namespace std;

int pivo_fixo(int ini, int fim){
   return ((fim-ini)/2)+ini;
}

int pivo_aleatorio(int ini, int fim){
   return ini+(rand() % (fim-ini+1));
}

template <typename T>
void instancia_aleatoria(T *v,int tamanho){
    for(int i = 0; i < tamanho; i++){
        v[i] = rand();
    }
}

template <typename T>
void instancia_pior_caso(T *v, int tamanho){
   T *v2 = new(nothrow) T [tamanho];
   for(int i = 0; i < tamanho; i++){
      v2[i] = -1;
   }
   for(int i = 0; i < tamanho; i++){
      int p = pivo_fixo(i, tamanho-1);
      if(v2[p] == -1){
         v[p] = i;
         if(v2[i] == -1){
            v2[i] = p;
            v2[p] = i;
         }
         else{
            int aux = v2[i];
            v2[i] = p;
            v2[p] = aux;
         }
      }
      else{
         v[v2[p]] = i;
         if(v2[i] == -1){
            v2[i] = v2[p];
            v2[p] = i;
         }
         else{
            int aux = v2[i];
            v2[i] = v2[p];
            v2[p] = aux;
         }
      }
   }
}

template <typename T>
void instancia_crescente(T *v, int tamanho){
    T j = 0;
    for(int i = 0; i < tamanho; i++){
        v[i] = j;
        j++;
    }
}

template <typename T>
void instancia_decrescente(T *v, int tamanho){
    T j = tamanho-1;
    for(int i = 0; i < tamanho; i++){
        v[i] = j;
        j--;
    }
}

int heap_fesq(int i){ return 2*i+1; }

int heap_fdir(int i){ return 2*i+2; }

int heap_pai(int i){ return (i-1)/2;}

template <typename T>
void heap_descer(T *vetor,int elem, int tamanho){
    while (heap_fesq(elem) < tamanho && (vetor[elem] < vetor[heap_fesq(elem)] || vetor[elem] < vetor[heap_fdir(elem)])){
        if (vetor[elem] < vetor[heap_fesq(elem)] || vetor[elem] < vetor[heap_fdir(elem)]){
            if(vetor[heap_fesq(elem)] > vetor[heap_fdir(elem)]) {
                T aux = vetor[elem];
                vetor[elem] = vetor[heap_fesq(elem)];
                vetor[heap_fesq(elem)] = aux;
                elem = heap_fesq(elem);
            }
            else{
                T aux = vetor[elem];
                vetor[elem] = vetor[heap_fdir(elem)];
                vetor[heap_fdir(elem)] = aux;
                elem = heap_fdir(elem);
            }
        }
    }
}

template <typename T>
T heap_extrair_max(T *vetor,int ini, int tamanho){
   T max = vetor[ini];
   vetor[ini] = vetor[tamanho-1];
   heap_descer(vetor, ini, tamanho-1);
   return max; 
}

template <typename T>
void heap_criar(T *vetor,int ini, int tamanho){
   for(int i = tamanho-1; i >= ini; i--){
      heap_descer(vetor, i, tamanho);
   }
}

template <typename T>
void intro_heapsort(T *vetor,int ini, int tamanho){
   heap_criar(vetor, ini, tamanho);
   T max;
   while (tamanho > 1){
      max = heap_extrair_max(vetor, ini, tamanho);
      vetor[tamanho-1] = max;
      tamanho--;
   }
}

template <typename T>
void heapsort(T *vetor, int tamanho){
   clock_t tempo;
   tempo = clock();
   intro_heapsort(vetor, 0, tamanho);
   tempo = clock() - tempo;
   cout << "Tempo heapsort: " << ((double)tempo)/(CLOCKS_PER_SEC) << '\n';
}

template <typename T>
int particionar(T *vetor, int ini, int fim, int p){
   T aux = vetor[ini];
   vetor[ini] = vetor[p];
   vetor[p] = aux;
   int j = fim;
   for(int i = ini+1; i<=fim; i++){
      if(vetor[i] > vetor[ini]){
         while(1==1){
	    if(vetor[j] <= vetor[ini]){
	       aux = vetor[j];
	       vetor[j] = vetor[i];
	       vetor[i] = aux;
	       break;
	    }
	    j--;
	    if(j < i) break;
	 }
      }
      if(j < i) break;
   }
   aux = vetor[ini];
   vetor[ini] = vetor[j];
   vetor[j] = aux;
   return j;
}

template <typename T>
void quicksort_rec_pivo_fixo(T *vetor, int ini, int fim){
   if(ini < fim){
      int p = particionar(vetor, ini, fim, pivo_fixo(ini,fim));
      quicksort_rec_pivo_fixo(vetor, ini, p-1);
      quicksort_rec_pivo_fixo(vetor, p+1, fim);
   }
}

template <typename T>
void quicksort_pivo_fixo(T *vetor, int tamanho){
   clock_t tempo;
   tempo = clock();
   quicksort_rec_pivo_fixo(vetor, 0, tamanho-1);
   tempo = clock() - tempo;
   cout << "Tempo quicksort fixo: " << ((double)tempo)/(CLOCKS_PER_SEC) << '\n';
}

template <typename T>
void quicksort_rec_pivo_aleatorio(T *vetor, int ini, int fim){
   if(ini < fim){
      int p = particionar(vetor, ini, fim, pivo_aleatorio(ini,fim));
      quicksort_rec_pivo_aleatorio(vetor, ini, p-1);
      quicksort_rec_pivo_aleatorio(vetor, p+1, fim);
   }
}

template <typename T>
void quicksort_pivo_aleatorio(T *vetor, int tamanho){
   clock_t tempo;
   tempo = clock();
   quicksort_rec_pivo_aleatorio(vetor, 0, tamanho-1);
   tempo = clock() - tempo;
   cout << "Tempo quicksort aleatório: " << ((double)tempo)/(CLOCKS_PER_SEC) << '\n';
}

template <typename T>
void insertionsort(T *vetor, int tamanho){
   clock_t tempo;
   tempo = clock();
   int j;
   T aux;
   for(int i = 1; i < tamanho; i++){
      aux = vetor[i];
      j = i-1;
      while(j >= 0 && vetor[j] > aux){
         vetor[j+1] = vetor[j];
         j--;
      }
      vetor[j+1] = aux;
   }
   tempo = clock() - tempo;
   cout << "Tempo insertionsort: " << ((double)tempo)/(CLOCKS_PER_SEC) << '\n';
}


int log(int n){
   int i = 0;
   while(n != 1){
      n >>= 1;
      i++;
   }
   return i;
}

template <typename T>
void introsort_rec(T *vetor, int ini, int fim, int limite){
    if(limite >= 1){
        if(ini < fim){
            int p = particionar(vetor, ini, fim, pivo_fixo(ini, fim));
            introsort_rec(vetor, ini, p-1, limite-1);
            introsort_rec(vetor, p+1, fim, limite-1);
        }
    }
    else{
      intro_heapsort(vetor, 0, fim+1);
    }
}

template <typename T>
void introsort(T *vetor, int tamanho){
    clock_t tempo;
    tempo = clock();
    introsort_rec(vetor, 0, tamanho-1, 2*log(tamanho));
    tempo = clock() - tempo;
    cout << "Tempo introsort sem insertion sort: " << ((double)tempo)/(CLOCKS_PER_SEC) << '\n';
}

template <typename T>
void introsort_insert_rec(T *vetor, int ini, int fim, int limite, int tamanho){
   if(ini >= fim) return;
    else if(limite >= 1){
        if(ini < fim){
            int p = particionar(vetor, ini, fim, pivo_fixo(ini, fim));
            introsort_insert_rec(vetor, ini, p-1, limite-1, tamanho);
            introsort_insert_rec(vetor, p+1, fim, limite-1, tamanho);
        }
    }
    else if (tamanho > 14){
        intro_heapsort(vetor, 0, fim+1);
    }
    else{
       insertionsort(vetor, fim+1);
    }
}

template <typename T>
void introsort_insert(T *vetor, int tamanho){
    clock_t tempo;
    tempo = clock();
    introsort_insert_rec(vetor, 0, tamanho-1, 2*log(tamanho), tamanho);
    tempo = clock() - tempo;
    cout << "Tempo introsort com insertionsort: " << ((double)tempo)/(CLOCKS_PER_SEC) << '\n';
}

template <typename T>
void verificar_ordenacao(T *v, int tamanho){
   for(int i = 0; i < tamanho-1; i++){
      if(v[i] > v[i+1]){
         cout << "vetor não ordenado!\n";
         return;
      }
   }
   cout << "vetor ordenado!\n";
}

int main(int argc, char *argv[]){
   srand(time(0));

   if(argc != 4){
      cout << "Usage: ./programa [Tipo de Instancia] [Tamanho do Vetor] [Numero de Instancias]" << endl;
      return 1;
   }

   char instancia = *argv[1];
   int tamanho = atoi(argv[2]);
   int num_instancias = atoi(argv[3]);

   if(instancia != 'A' && instancia != 'C' && instancia != 'D' && instancia != 'P'){
      cout << "Instância inválida\nA: Aleatória\nC: Crescente\nD: Decrescente\nP: Pior caso" << endl;
      return 1;
   }
   if(tamanho <= 0){
      cout << "tamanho do vetor inválido" << endl;
      return 1;
   }
   if(num_instancias <= 0){
      cout << "número de instâncias inválido" << endl;
      return 1;
   }

   int **v = new(nothrow) int * [num_instancias];
   if(instancia == 'A'){
      for(int i = 0; i < num_instancias; i++){
         v[i] = new(nothrow) int [tamanho];
         instancia_aleatoria(v[i], tamanho);
      }
   }
   else if(instancia == 'C'){
      for(int i = 0; i < num_instancias; i++){
         v[i] = new(nothrow) int [tamanho];
         instancia_crescente(v[i], tamanho);
      }
   }
   else if(instancia == 'D'){
      for(int i = 0; i < num_instancias; i++){
         v[i] = new(nothrow) int [tamanho];
         instancia_decrescente(v[i], tamanho);
      }
   }
   else{
      for(int i = 0; i < num_instancias; i++){
         v[i] = new(nothrow) int [tamanho];
         instancia_pior_caso(v[i], tamanho);
      }
   }

   int **v2 = new(nothrow) int * [num_instancias];
   int **v3 = new(nothrow) int * [num_instancias];
   int **v4 = new(nothrow) int * [num_instancias];
   int **v5 = new(nothrow) int * [num_instancias];

   for(int i = 0; i < num_instancias; i++){
         v2[i] = new(nothrow) int [tamanho];
         v3[i] = new(nothrow) int [tamanho];
         v4[i] = new(nothrow) int [tamanho];
         v5[i] = new(nothrow) int [tamanho];
   }

   for(int i = 0; i < num_instancias; i++){
      for (int j = 0; j < tamanho; j++){
         v2[i][j] = v[i][j];
         v3[i][j] = v[i][j];
         v4[i][j] = v[i][j];
         v5[i][j] = v[i][j];
      }
   }

   for(int i = 0; i < num_instancias; i++){
      cout << "Instância " << i+1 << ":\n";
      heapsort(v[i], tamanho);
      verificar_ordenacao(v[i],tamanho);

      introsort(v4[i], tamanho);
      verificar_ordenacao(v4[i],tamanho);

      introsort_insert(v5[i], tamanho);
      verificar_ordenacao(v5[i],tamanho);

      quicksort_pivo_aleatorio(v3[i], tamanho);
      verificar_ordenacao(v3[i],tamanho);

      quicksort_pivo_fixo(v2[i], tamanho);
      verificar_ordenacao(v2[i],tamanho);

      cout << endl;
   }

   return 0;
}