#include <iostream>
#include <thread>

#define CONST_ORDER 1000

void multMatrix(long* A, long* B, long* C, int start, int end);
void readMatrix(long* A, long* B);
void writeMatrix(long* C);

int main(int argc, char* argv[]){
    int i, numt, total, division, rest, start, end;
    long *A, *B, *C;
    
    if(argc >= 2){
        try {
            std::size_t pos;
            numt = std::stoi(argv[1], &pos);
        } catch (std::invalid_argument const &ex) {
            std::cerr << "Invalid number: " << argv[1] << '\n';
        } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << argv[1] << '\n';
        }
    }else numt = 1;
    
    std::cout << "Número de threads: " << numt << "\n";

    total = CONST_ORDER*CONST_ORDER;
    division = total/numt;
    rest = total%numt;
    
    A = (long*) malloc(total*sizeof(long));
    B = (long*) malloc(total*sizeof(long));
    C = (long*) malloc(total*sizeof(long));
    
    readMatrix(A, B);
    
    // Criar numt-1 novas threads
    std::thread threads[numt-1];
    
    for(i = 0; i < numt-1; i++){
        start = (i)*division + (i>rest)*rest + (i<=rest)*i;
        end = (i+1)*division + ((i+1)>rest)*rest + ((i+1)<=rest)*(i+1);
        threads[i] = std::thread(multMatrix, A, B, C, start, end);
    }
    
    start = total - division;
    end = total;
    multMatrix(A, B, C, start, end);
    
    for(i = 0; i < numt - 1; i++){
        threads[i].join();
    }
    
    writeMatrix(C);
    
    return 0;
} 

void multMatrix(long* A, long* B, long* C, int start, int end){
    int i, j, lin, col;
    long result, a, b;
    
    for(i = start; i < end; i++){
        lin = i/CONST_ORDER;
        col = i%CONST_ORDER;
        
        result = 0;
        
        for(j = 0; j < CONST_ORDER; j++){
            a = A[lin*CONST_ORDER + j];
            b = B[j*CONST_ORDER + col];
            result += a*b;
        }
        
        C[i] = result;
    }
}

void readMatrix(long* A, long* B){
	int i, j;
	FILE *AFile, *BFile;
	
	AFile = fopen("matrixA.txt", "r");
    BFile = fopen("matrixB.txt", "r");
	
	//Abre o .txt e lê cada um dos valores, colocando-os na matriz
	for(i = 0; i < CONST_ORDER; i++)
		for(j = 0; j < CONST_ORDER; j++){
            fscanf(AFile, "%ld", &A[i*(CONST_ORDER)+j]);
            fscanf(BFile, "%ld", &B[i*(CONST_ORDER)+j]);
        }
			
	fclose(AFile);
    fclose(BFile);
}

void writeMatrix(long* C){
    int i, j;
    FILE *CFile;
    
    CFile = fopen("matrixC", "w");

	for(i = 0; i < CONST_ORDER; i++){
		for(j = 0; j < CONST_ORDER; j++)
			fprintf(CFile, "%ld ", C[i*CONST_ORDER + j]);
	    fprintf(CFile, "\n");
	}
	
	fclose(CFile);
}
