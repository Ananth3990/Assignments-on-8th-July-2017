#include<stdio.h>
#include<math.h>

typedef struct
{
	float arr[2][3];
}TwoArray;

typedef struct
{
	float arr[3][3];
}ThreeArray;

typedef struct
{
	float side_ab;
	float side_bc;
	float side_ac;  //This is base
}Triangle_sides;

int main()
{
	void Calculate_length(float arr[][3], float *result);
	void Calculate_Height(Triangle_sides *ts, float *height);
	void Calculate_Area(Triangle_sides *ts, float *area);
	void Calculate_Permeter(Triangle_sides *ta, float *perimeter);
	void Calculate_CenterOfIncircle(float vert[][3], Triangle_sides *ta, float *perimeter, float center[3]);
	void Calculate_RadiusOfIncircle(float *area, float *perimeter, float *rad);

	//Calculate_length(ta.arr,&side_ab);
	//Calculate_length(ta.arr, &side_ac);
	//Calculate_length(ta.arr, &side_bc);
	TwoArray ta;
	float side_ab;
	float side_ac;
	float side_bc;

	//Calculate_Height(&ts,&height);
	Triangle_sides ts;
	float height;

	//Calculate_Area(&ap,&area);
	float area;

	//Calculate_Permeter(&ts,&perimeter);	
	float perimeter;

	//Calculate_CenterOfIncircle(float vert[3], Triangle_sides *ta, *perimeter, float center[2]);
	ThreeArray thra;
	float center[3];

	//void Calculate_RadiusOfIncircle(float *area,float *perimeter,float *rad);
	float rad;

	//Calculate_length(ta.arr,&side_ab);
	ta = { {{-1.0f,-1.0f,0.0f},{0.0f,1.0f,0.0f}} };
	Calculate_length(ta.arr,&side_ab);
	printf("side_ab is %f\n",side_ab);

	//Calculate_length(ta.arr, &side_ac);
	ta = { { { -1.0f,-1.0f,0.0f },{ 1.0f,-1.0f,0.0f } } };
	Calculate_length(ta.arr, &side_ac);
	printf("side_bc is %f\n", side_ac);

	//Calculate_length(ta.arr, &side_bc);
	ta = { { { 0.0f,1.0f,0.0f },{ 1.0f,-1.0f,0.0f } } };
	Calculate_length(ta.arr, &side_bc);
	printf("side_bc is %f\n", side_bc);

	//Calculate_Height(&ts,&height);
	ts.side_ab = side_ab;
	ts.side_ac = side_ac;
	ts.side_bc = side_bc;
	Calculate_Height(&ts,&height);
	printf("Height is %f\n",height);

	 //Calculate_Area(&ap,&area);
	ts.side_ab = side_ab;
	ts.side_ac = side_ac;
	ts.side_bc = side_bc;
	 Calculate_Area(&ts,&area);
	 printf("Area is %f\n",area);

	 //Calculate_Permeter(&ts,&perimeter);
	 Calculate_Permeter(&ts,&perimeter);
	 printf("Perimeter is %f\n", perimeter);

	//Calculate_CenterOfIncircle(float vert[3], Triangle_sides *ta, *perimeter, float center[2]);
	 ts.side_ab = side_ab;
	 ts.side_ac = side_ac;
	 ts.side_bc = side_bc;
	 thra = { { { -1.0f,-1.0f,0.0f },{ 0.0f,1.0f,0.0f },{ 1.0f,-1.0f,0.0f }} };
	 Calculate_CenterOfIncircle(thra.arr, &ts,&perimeter,center);
	 printf("CenterOfIncircle is (%f,%f,%f)\n", center[0],center[1],center[2]);

	 //Calculate_RadiusOfIncircle(float *area, float *perimeter, float *rad);
	 Calculate_RadiusOfIncircle(&area,&perimeter,&rad);
	 printf("RadiusOfIncircle is %f\n", rad);

	return 0;
}

void Calculate_length(float arr[][3], float *result)
{
	float  x1, y1, z1;
	float  x2, y2, z2;

	x1 = arr[0][0];
	y1 = arr[0][1];
	z1 = arr[0][2];

	x2 = arr[1][0];
	y2 = arr[1][1];
	z2 = arr[1][2];

	float temp1 = (x2 - x1);
	float temp2 = (y2 - y1);

	*result = (temp1*temp1) + (temp2*temp2);
	*result = (float)sqrtf(result[0]);
}

void Calculate_Height(Triangle_sides *ts, float *height)
{
	float temp1 = (*ts).side_ab;
	float temp2 = (*ts).side_ac;
	float temp3 = (*ts).side_bc;

	*height = (temp3*temp3)-((0.5f*temp2)*(0.5f*temp2));
	*height = sqrtf(*height);
}

void Calculate_Area(Triangle_sides *ts,float *area)
{
	float s;
	s = (ts->side_ab) + (ts->side_ac) + (ts->side_bc);
	s = s / 2;
	*area = sqrtf((s * (s-ts->side_ab) * (s-ts->side_ac) * (s-(ts->side_bc))) );
}

void Calculate_Permeter(Triangle_sides *ta, float *perimeter)
{
	*perimeter = ((*ta).side_ab)+ ((*ta).side_ac)+ ((*ta).side_bc);
}

void Calculate_CenterOfIncircle(float vert[][3], Triangle_sides *ta,float *perimeter,float center[3])
{
	float temp;
	temp = (float) (vert[0][0] * (*ta).side_bc) + (vert[1][0]*(*ta).side_ac)+(vert[2][0]*(*ta).side_ab);
	temp = temp / (*perimeter);
	center[0] = temp;

	temp = (float)(vert[0][1] * (*ta).side_bc) + (vert[1][1] * (*ta).side_ac) + (vert[2][1] * (*ta).side_ab);
	temp = temp / (*perimeter);
	center[1] = temp;

	temp = (float)(vert[0][2] * (*ta).side_bc) + (vert[1][2] * (*ta).side_ac) + (vert[2][2] * (*ta).side_ab);
	temp = temp / (*perimeter);
	center[2] = temp;
}

void Calculate_RadiusOfIncircle(float *area,float *perimeter,float *rad)
{
	float temp = (2*(*area));
	temp = temp / (*perimeter);
	*rad = temp;
}


