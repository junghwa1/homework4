#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);                  //이차원 배열 동적 메모리 할당
void print_matrix(int** matrix, int row, int col);      //이차원 배열 출력
int free_matrix(int** matrix, int row, int col);        //할당받은 동적 메모리 해제
int fill_data(int** matrix, int row, int col);          //0~19사이의 정수로 이차원 배열 채우기
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //두 행렬의 합
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //두 행렬의 차
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //전치행렬을 만듦
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //행렬의 곱(행렬x전치행렬)

int main()
{
    char command;                   //메뉴 선택 변수
    printf("[----- [염중화]  [2019038062] -----]\n");

	int row, col;                   //행렬의 행과 열
	srand(time(NULL));              //난수 발생 초기화

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);     //사용자에게 행과 열의 개수를 입력받음
    int** matrix_a = create_matrix(row, col);       //row X col인 행렬a 동적 메모리 할당
	int** matrix_b = create_matrix(row, col);       //row X col 행렬b 동적 메모리 할당
    int** matrix_a_t = create_matrix(col, row);     //col X row인 전치행렬 동적 메모리 할당

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL){      //행렬 a, b가 생성되지 않았을 때
        return -1;          //리턴 -1(비정상 종료)
    }

	do{
		printf("----------------------------------------------------------------\n");       //메뉴 출력
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");        //z: 행렬 채우기        p: 행렬 출력
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");        //a: 행렬의 합          s: 행렬의 차
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");        //t: 행렬a의 전치행렬   m: 행렬의 곱 
		printf(" Quit                = q \n");                                          //q: 프로그램 종료
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);         //메뉴 선택

		switch(command) {
		case 'z': case 'Z':             //행렬 채우기
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);      //행렬a에 0~19사이의 정수로 채움
			fill_data(matrix_b, row, col);      //행렬b에 0~19사이의 정수로 채움
			break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);   //행렬a 출력   
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);   //행렬b 출력
			break;
        case 'a': case 'A':
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);      //행렬a,b의 합
			break;
        case 's': case 'S':
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);   //행렬a,b의 차
			break;
        case 't': case 'T':
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);   //행렬a의 전치행렬을 a_t에 만듦
            print_matrix(matrix_a_t, col, row);                 //행렬a의 전치행렬 a_t 출력
			break;
        case 'm': case 'M':
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);   //행렬a의 전치행렬을 a_t에 만듦
            multiply_matrix(matrix_a, matrix_a_t, row, col);    //행렬a와 전치행렬a_t의 곱
			break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);                  //행렬 a_t가 할당받은 동적 메모리 해제
            free_matrix(matrix_a, row, col);                    //행렬 a가 할당받은 동적 메모리 해제
            free_matrix(matrix_b, row, col);                    //행렬 b가 할당받은 동적 메모리 해제
			break;
		default:
			printf("\n       >>>>>   again.   <<<<<     \n");   //메뉴 이외의 값 입력 시
			break;
		}

	}while(command != 'q' && command != 'Q');                   //while문 안에 프로그램을 수행하고 command에 입력받은 값이 q, Q일때 반복문 종료

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)           //이차원 배열 동적 메모리 할당
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때 
		printf("Check the size of row and col!\n");
		return NULL;                            //NULL 리턴(비정상 종료)
	}

	int** arr = (int**)malloc(sizeof(int*) * row);  //이차원 배열의 행의 개수만큼 동적 메모리 할당
	for (int r = 0; r < row; r++) {
		*(arr+r) = (int*)malloc(sizeof(int) * col); //이차원 배열의 각 행의 요소만큼(행렬의 열) 동적 메모리 할당
	}

	/* Check post conditions */
	if (arr == NULL) {                          //이차원 배열이 메모리 할당을 못받았을때
		printf("Memory Allocation Failed.\n");  
		return NULL;                            //리턴 NULL(비정상 종료)
	}

	return arr;         //이차원 배열 arr 리턴(정상 종료)
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)   //이차원 배열 출력
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때 
		printf("Check the size of row and col!\n");
		return;                                 //함수 종료(비정상 종료)
	}

    for (int i = 0; i < row; i++) {             //행의 개수만큼 반복
		for (int j = 0; j < col; j++)           //열의 개수만큼 반복
			printf("%-6d ", matrix[i][j]);      //matrix[i][j]의 값 출력 
		printf("\n");
	}
	printf("\n");

	/* Check post conditions */
	 if (matrix == NULL) {                      //이차원 배열이 메모리 할당을 못받았을때
		printf("Memory Allocation Failed.\n");
		return;                                 //함수 종료(비정상 종료)
	}
	return;         //(정상 종료)
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //할당받은 동적 메모리 해제
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때 
		printf("Check the size of row and col!\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

	for (int i = 0; i < row; i++) {             //이차원 배열 matrix의 각 행이 할당 받았던 동적 메모리 해제
		free(matrix[i]);
	}
	free(matrix);                               //이차원 배열 matrix가 할당 받았던 동적 메모리 해제
	
    return 1;       //(정상 종료)
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)   //0~19사이의 정수로 이차원 배열 채우기
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때
		printf("Check the size of row and col!\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

    for (int i = 0; i < row; i++)               //행의 개수만큼 반복
		for (int j = 0; j < col; j++)           //열의 개수만큼 반복
			*(*(matrix+i)+j) = rand() % 20;     //matrix[i][j]에 0~19 사이의 정수를 저장

	/* Check post conditions */
    if (matrix == NULL) {                       //이차원 배열이 메모리 할당을 못받았을때
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

	return 1;       //(정상 종료)
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)      //두 행렬의 합
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때
		printf("Check the size of row and col!\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

    int** matrix_sum = create_matrix(row, col); //두 행렬의 합을 저장할 행렬을 동적 메모리 할당
    
	for (int i = 0; i < row; i++) {             //행의 개수만큼 반복
		for (int j = 0; j < col; j++)           //열의 개수만큼 반복
			*(*(matrix_sum + i)+ j) = matrix_a[i][j] + matrix_b[i][j];  //행렬 a,b의 같은 위치([i][j])에 있는 정수끼리 더한 값을 matrix_sum[i][j]에 저장
	}
	
	print_matrix(matrix_sum, row, col);         //행렬 matrix_sum 출력
	free_matrix(matrix_sum, row, col);          //matrix_sum이 할당받은 동적 메모리 해제

    /* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {   //이차원 배열 a,b,sum 중 메모리 할당을 못받은 행렬이 있을 때
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

	return 1;       //(정상 종료)
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)      //두 행렬의 차
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때
		printf("Check the size of row and col!\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

    int** matrix_sub = create_matrix(row, col); //두 행렬의 합을 저장할 행렬을 동적 메모리 할당

	for (int i = 0; i < row; i++) {             //행의 개수만큼 반복
		for (int j = 0; j < col; j++)           //열의 개수만큼 반복
			*(*(matrix_sub + i) + j) = matrix_a[i][j] - matrix_b[i][j]; //행렬 a,b의 같은 위치([i][j])에 있는 정수끼리 더한 값을 matrix_sum[i][j]에 저장
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {   //이차원 배열 a,b,sum 중 메모리 할당을 못받은 행렬이 있을 때
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

	print_matrix(matrix_sub, row, col);         //행렬 matrix_sub 출력
	free_matrix(matrix_sub, row, col);          //matrix_sub이 할당받은 동적 메모리 해제

	return 1;       //(정상 종료)
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)       //전치행렬을 만듦
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때
		printf("Check the size of row and col!\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

	for (int i = 0; i < row; i++) {             //행의 개수만큼 반복
		for (int j = 0; j < col; j++)           //열의 개수만큼 반복
			matrix_t[i][j] = matrix[j][i];      //matrix_t[i][j]에 matrix[j][i]의 값을 저장
	}

	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {    //이차원 배열 matrix, matrix_t 중 메모리 할당을 못받은 행렬이 있을 때
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

	return 1;       //(정상 종료)
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //행과 열이 0보다 작거나 같을때
		printf("Check the size of row and col!\n");
		return -1;                              //-1 리턴(비정상 종료)
	}

    int** matrix_axt = create_matrix(row, row); //두 행렬의 곱을 저장할 행렬을 동적 메모리 할당

	for (int k = 0; k < row; k++) {             //행의 개수만큼 반복
		for (int i = 0; i < row; i++) {         //행의 개수만큼 반복
			int temp = 0;                       //곱의 합들을 저장할 변수
			for (int j = 0; j < col; j++)       //열의 개수만큼 반복
				temp += matrix_a[k][j] * matrix_t[j][i];        //matrix_a의 i번째 행의 요소와 matrix_t의 j번째 열의 요소의 곱의 합
			matrix_axt[k][i] = temp;            //matrix_art[k][i]에 temp 값을 저장
		}
	}

	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {//이차원 배열 matrix_t, matrix_axt 중 메모리 할당을 못받은 행렬이 있을 때
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 리턴(비정상 종료)
	}
	print_matrix(matrix_axt, row, row);         //행렬 matrix_axt 출력
	free_matrix(matrix_axt, row, col);          //matrix_axt가 할당받은 동적 메모리 해제
	return 1;       //(정상 종료)
}

