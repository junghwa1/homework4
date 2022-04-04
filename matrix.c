#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);                  //������ �迭 ���� �޸� �Ҵ�
void print_matrix(int** matrix, int row, int col);      //������ �迭 ���
int free_matrix(int** matrix, int row, int col);        //�Ҵ���� ���� �޸� ����
int fill_data(int** matrix, int row, int col);          //0~19������ ������ ������ �迭 ä���
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //�� ����� ��
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //�� ����� ��
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //��ġ����� ����
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //����� ��(���x��ġ���)

int main()
{
    char command;                   //�޴� ���� ����
    printf("[----- [����ȭ]  [2019038062] -----]\n");

	int row, col;                   //����� ��� ��
	srand(time(NULL));              //���� �߻� �ʱ�ȭ

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);     //����ڿ��� ��� ���� ������ �Է¹���
    int** matrix_a = create_matrix(row, col);       //row X col�� ���a ���� �޸� �Ҵ�
	int** matrix_b = create_matrix(row, col);       //row X col ���b ���� �޸� �Ҵ�
    int** matrix_a_t = create_matrix(col, row);     //col X row�� ��ġ��� ���� �޸� �Ҵ�

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL){      //��� a, b�� �������� �ʾ��� ��
        return -1;          //���� -1(������ ����)
    }

	do{
		printf("----------------------------------------------------------------\n");       //�޴� ���
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");        //z: ��� ä���        p: ��� ���
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");        //a: ����� ��          s: ����� ��
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");        //t: ���a�� ��ġ���   m: ����� �� 
		printf(" Quit                = q \n");                                          //q: ���α׷� ����
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);         //�޴� ����

		switch(command) {
		case 'z': case 'Z':             //��� ä���
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);      //���a�� 0~19������ ������ ä��
			fill_data(matrix_b, row, col);      //���b�� 0~19������ ������ ä��
			break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);   //���a ���   
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);   //���b ���
			break;
        case 'a': case 'A':
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);      //���a,b�� ��
			break;
        case 's': case 'S':
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);   //���a,b�� ��
			break;
        case 't': case 'T':
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);   //���a�� ��ġ����� a_t�� ����
            print_matrix(matrix_a_t, col, row);                 //���a�� ��ġ��� a_t ���
			break;
        case 'm': case 'M':
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);   //���a�� ��ġ����� a_t�� ����
            multiply_matrix(matrix_a, matrix_a_t, row, col);    //���a�� ��ġ���a_t�� ��
			break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);                  //��� a_t�� �Ҵ���� ���� �޸� ����
            free_matrix(matrix_a, row, col);                    //��� a�� �Ҵ���� ���� �޸� ����
            free_matrix(matrix_b, row, col);                    //��� b�� �Ҵ���� ���� �޸� ����
			break;
		default:
			printf("\n       >>>>>   again.   <<<<<     \n");   //�޴� �̿��� �� �Է� ��
			break;
		}

	}while(command != 'q' && command != 'Q');                   //while�� �ȿ� ���α׷��� �����ϰ� command�� �Է¹��� ���� q, Q�϶� �ݺ��� ����

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)           //������ �迭 ���� �޸� �Ҵ�
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������ 
		printf("Check the size of row and col!\n");
		return NULL;                            //NULL ����(������ ����)
	}

	int** arr = (int**)malloc(sizeof(int*) * row);  //������ �迭�� ���� ������ŭ ���� �޸� �Ҵ�
	for (int r = 0; r < row; r++) {
		*(arr+r) = (int*)malloc(sizeof(int) * col); //������ �迭�� �� ���� ��Ҹ�ŭ(����� ��) ���� �޸� �Ҵ�
	}

	/* Check post conditions */
	if (arr == NULL) {                          //������ �迭�� �޸� �Ҵ��� ���޾�����
		printf("Memory Allocation Failed.\n");  
		return NULL;                            //���� NULL(������ ����)
	}

	return arr;         //������ �迭 arr ����(���� ����)
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)   //������ �迭 ���
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������ 
		printf("Check the size of row and col!\n");
		return;                                 //�Լ� ����(������ ����)
	}

    for (int i = 0; i < row; i++) {             //���� ������ŭ �ݺ�
		for (int j = 0; j < col; j++)           //���� ������ŭ �ݺ�
			printf("%-6d ", matrix[i][j]);      //matrix[i][j]�� �� ��� 
		printf("\n");
	}
	printf("\n");

	/* Check post conditions */
	 if (matrix == NULL) {                      //������ �迭�� �޸� �Ҵ��� ���޾�����
		printf("Memory Allocation Failed.\n");
		return;                                 //�Լ� ����(������ ����)
	}
	return;         //(���� ����)
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //�Ҵ���� ���� �޸� ����
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������ 
		printf("Check the size of row and col!\n");
		return -1;                              //-1 ����(������ ����)
	}

	for (int i = 0; i < row; i++) {             //������ �迭 matrix�� �� ���� �Ҵ� �޾Ҵ� ���� �޸� ����
		free(matrix[i]);
	}
	free(matrix);                               //������ �迭 matrix�� �Ҵ� �޾Ҵ� ���� �޸� ����
	
    return 1;       //(���� ����)
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)   //0~19������ ������ ������ �迭 ä���
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������
		printf("Check the size of row and col!\n");
		return -1;                              //-1 ����(������ ����)
	}

    for (int i = 0; i < row; i++)               //���� ������ŭ �ݺ�
		for (int j = 0; j < col; j++)           //���� ������ŭ �ݺ�
			*(*(matrix+i)+j) = rand() % 20;     //matrix[i][j]�� 0~19 ������ ������ ����

	/* Check post conditions */
    if (matrix == NULL) {                       //������ �迭�� �޸� �Ҵ��� ���޾�����
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 ����(������ ����)
	}

	return 1;       //(���� ����)
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)      //�� ����� ��
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������
		printf("Check the size of row and col!\n");
		return -1;                              //-1 ����(������ ����)
	}

    int** matrix_sum = create_matrix(row, col); //�� ����� ���� ������ ����� ���� �޸� �Ҵ�
    
	for (int i = 0; i < row; i++) {             //���� ������ŭ �ݺ�
		for (int j = 0; j < col; j++)           //���� ������ŭ �ݺ�
			*(*(matrix_sum + i)+ j) = matrix_a[i][j] + matrix_b[i][j];  //��� a,b�� ���� ��ġ([i][j])�� �ִ� �������� ���� ���� matrix_sum[i][j]�� ����
	}
	
	print_matrix(matrix_sum, row, col);         //��� matrix_sum ���
	free_matrix(matrix_sum, row, col);          //matrix_sum�� �Ҵ���� ���� �޸� ����

    /* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {   //������ �迭 a,b,sum �� �޸� �Ҵ��� ������ ����� ���� ��
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 ����(������ ����)
	}

	return 1;       //(���� ����)
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)      //�� ����� ��
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������
		printf("Check the size of row and col!\n");
		return -1;                              //-1 ����(������ ����)
	}

    int** matrix_sub = create_matrix(row, col); //�� ����� ���� ������ ����� ���� �޸� �Ҵ�

	for (int i = 0; i < row; i++) {             //���� ������ŭ �ݺ�
		for (int j = 0; j < col; j++)           //���� ������ŭ �ݺ�
			*(*(matrix_sub + i) + j) = matrix_a[i][j] - matrix_b[i][j]; //��� a,b�� ���� ��ġ([i][j])�� �ִ� �������� ���� ���� matrix_sum[i][j]�� ����
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {   //������ �迭 a,b,sum �� �޸� �Ҵ��� ������ ����� ���� ��
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 ����(������ ����)
	}

	print_matrix(matrix_sub, row, col);         //��� matrix_sub ���
	free_matrix(matrix_sub, row, col);          //matrix_sub�� �Ҵ���� ���� �޸� ����

	return 1;       //(���� ����)
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)       //��ġ����� ����
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������
		printf("Check the size of row and col!\n");
		return -1;                              //-1 ����(������ ����)
	}

	for (int i = 0; i < row; i++) {             //���� ������ŭ �ݺ�
		for (int j = 0; j < col; j++)           //���� ������ŭ �ݺ�
			matrix_t[i][j] = matrix[j][i];      //matrix_t[i][j]�� matrix[j][i]�� ���� ����
	}

	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {    //������ �迭 matrix, matrix_t �� �޸� �Ҵ��� ������ ����� ���� ��
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 ����(������ ����)
	}

	return 1;       //(���� ����)
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                 //��� ���� 0���� �۰ų� ������
		printf("Check the size of row and col!\n");
		return -1;                              //-1 ����(������ ����)
	}

    int** matrix_axt = create_matrix(row, row); //�� ����� ���� ������ ����� ���� �޸� �Ҵ�

	for (int k = 0; k < row; k++) {             //���� ������ŭ �ݺ�
		for (int i = 0; i < row; i++) {         //���� ������ŭ �ݺ�
			int temp = 0;                       //���� �յ��� ������ ����
			for (int j = 0; j < col; j++)       //���� ������ŭ �ݺ�
				temp += matrix_a[k][j] * matrix_t[j][i];        //matrix_a�� i��° ���� ��ҿ� matrix_t�� j��° ���� ����� ���� ��
			matrix_axt[k][i] = temp;            //matrix_art[k][i]�� temp ���� ����
		}
	}

	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {//������ �迭 matrix_t, matrix_axt �� �޸� �Ҵ��� ������ ����� ���� ��
		printf("Memory Allocation Failed.\n");
		return -1;                              //-1 ����(������ ����)
	}
	print_matrix(matrix_axt, row, row);         //��� matrix_axt ���
	free_matrix(matrix_axt, row, col);          //matrix_axt�� �Ҵ���� ���� �޸� ����
	return 1;       //(���� ����)
}

