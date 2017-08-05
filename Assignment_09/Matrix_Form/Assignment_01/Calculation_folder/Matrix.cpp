#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define NUMBER_OF_ROWS 4
#define NUMBER_OF_COLOUMNS 4

static const float pi = 3.14285714286f;

void AllocateMatrix(float **arr,int row,int col)
{
	*arr = (float*)malloc(row*col* sizeof(float));
}

void LoadIdentityMatrix(float **arr,int row,int col) //Make passed matrix to Identity Matrix
{
	for (int i = 0; i<(row*col); i++)
	{
		if (i%5==0)
		{
			*((*arr)+i) = 1.0f;
		}
		else
		{
			*((*arr) + i) = 0.0f;
		}
	}
}

void FillMatrix(float **fill,float *values, int row, int col)
{
	for (int i = 0; i<(row*col); i++)
	{
		*((*fill) + i) = *(values + i);
	}
}

void PrintMatrix(float **arr, int row, int col)
{
	int i;

	for (i=0;i<row*col;i++)
	{
		printf("arr[%d] = %f\n",i,*((*arr)+i));
	}
}

void TransposeMatrix(float **arr,int row,int col)
{
	int i,j,z;
	float *dup = NULL;
	int index1, index2;
	AllocateMatrix(&dup,row, col);
	for (i=0;i<row;i++)
	{
		for (j=0;j<col;j++)
		{
			//index in original matrix
			index1 = i*col + j;

			//index in transposed matrix
			index2 = j*row + i;

			*(dup + index2) = *((*arr)+index1);
		}
	}

	for (z = 0; z < row*col; z++)
	{
		*((*arr) + z) = *(dup + z);
	}
}

void TranslationMatrix(float x, float y, float z,float **mat)
{ 
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat),NUMBER_OF_ROWS,NUMBER_OF_COLOUMNS);
	*((*mat) + 3) = x;
	*((*mat) + 7) = y;
	*((*mat) + 11) = z;
	TransposeMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}

void ScalingMatrix(float x,float y,float z,float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i=0;i<16;i++)
	{
		if (i%5==0)
		{
			if (i==15)
			{
				*((*mat)+i) = 1.0f;
			}
			else
			{
				if (i==0)
				{
					*((*mat) + i) = x;
				}

				if (i==5)
				{
					*((*mat) + i) = y;
				}

				if (i == 10)
				{
					*((*mat) + i) = z;
				}
			}
		}
		else
		{
			*((*mat) + i) = 0.0f;
		}
	}
	TransposeMatrix(&(*mat),NUMBER_OF_ROWS,NUMBER_OF_COLOUMNS);
}

void RotationMatrix_x(float angle_in_degree,float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	float angle_in_radian = 0.0f;
	angle_in_radian = angle_in_degree*(pi / 180.0f);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i=0;i<NUMBER_OF_COLOUMNS*NUMBER_OF_ROWS;i++)
	{
		if (i==5 ||i==10)
		{
			*((*mat) + i) = cosf(angle_in_radian);
		}

		if (i==6)
		{
			*((*mat) + i) = -sinf(angle_in_radian);
		}

		if (i == 9)
		{
			*((*mat) + i) = sinf(angle_in_radian);
		}
	}
	TransposeMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}

void RotationMatrix_y(float angle_in_degree, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	float angle_in_radian = 0.0f;
	angle_in_radian = angle_in_degree*(pi / 180.0f);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i = 0; i<NUMBER_OF_COLOUMNS*NUMBER_OF_ROWS; i++)
	{
		if (i == 0 || i == 10)
		{
			*((*mat) + i) = cosf(angle_in_radian);
		}

		if (i == 8)
		{
			*((*mat) + i) = -sinf(angle_in_radian);
		}

		if (i == 2)
		{
			*((*mat) + i) = sinf(angle_in_radian);
		}
	}
	TransposeMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}

void RotationMatrix_z(float angle_in_degree, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	float angle_in_radian = 0.0f;
	angle_in_radian = angle_in_degree*(pi / 180.0f);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i = 0; i<NUMBER_OF_COLOUMNS*NUMBER_OF_ROWS; i++)
	{
		if (i == 0 || i == 5)
		{
			*((*mat) + i) = cosf(angle_in_radian);
		}

		if (i == 1)
		{
			*((*mat) + i) = -sinf(angle_in_radian);
		}

		if (i == 4)
		{
			*((*mat) + i) = sinf(angle_in_radian);
		}
	}
	TransposeMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}


int main()
{
	void AllocateMatrix(float **arr,int row,int col);
	void LoadIdentityMatrix(float **arr,int row,int col);
	void TransposeMatrix(float **arr, int row, int col);
	void PrintMatrix(float **arr, int row, int col); //Of no use
	void FillMatrix(float **fill, float *values, int row, int col); //Of No use
	void TranslationMatrix(float x, float y, float z, float **mat);
	void ScalingMatrix(float x, float y, float z, float **mat);
	void RotationMatrix_x(float angle_in_degree, float **mat);
	void RotationMatrix_y(float angle_in_degree, float **mat);
	void RotationMatrix_z(float angle_in_degree, float **mat);

	float *translation_matrix = NULL;
	TranslationMatrix(-3.0f,-3.0f,-3.0f,&translation_matrix);
	PrintMatrix(&translation_matrix,4,4);

	printf("------------------------------\n");

	float *scaling_matrix = NULL;
	ScalingMatrix(0.75f,0.75f,0.75f,&scaling_matrix);
	PrintMatrix(&scaling_matrix,4,4);

	printf("------------------------------\n");

	float *rotation_x = NULL;
	RotationMatrix_x(30.0f,&rotation_x);
	PrintMatrix(&rotation_x,4,4);

	printf("------------------------------\n");

	float *rotation_y = NULL;
	RotationMatrix_y(60.0f,&rotation_y);
	PrintMatrix(&rotation_y,4,4);

	printf("------------------------------\n");

	float *rotation_z = NULL;
	RotationMatrix_z(20.0f,&rotation_z);
	PrintMatrix(&rotation_z,4,4);

	return 0;
}
