#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct quadEq {

	double a, b, c; //�����������
	double d; // ������������
	double x1, x2; //�����
} quadEq;

quadEq* input() { //���� �������������

	quadEq* temp = (quadEq*)malloc(sizeof(quadEq));
	scanf("%lf %lf %lf", &(temp->a), &(temp->b), &(temp->c));
	return temp;
}

void D(quadEq* eq) { //������� ������������

	double a = eq->a;
	double b = eq->b;
	double c = eq->c;
	eq->d = b * b - 4 * a * c;
}

void roots(quadEq* eq) { //������� ����� ���������

	double a = eq->a;
	double b = eq->b;
	double d = eq->d;

	if (d < 0) return;
	eq->x1 = (-b + sqrt(d)) / (2 * a);
	eq->x2 = (-b - sqrt(d)) / (2 * a);
}

void print(quadEq* eq) { //�����

	if (eq->d < 0) {

		printf("No roots");
		return;
	}
	if (eq->d == 0) {

		printf("x = %f", eq->x1);
		return;
	}
	if (eq->d > 0) {

		printf("x1 = %f\nx2 = %f", eq->x1, eq->x2);
		return;
	}
}

int main() {

	quadEq *eq;
	eq = input();
	D(eq);
	roots(eq);
    print(eq);
	free(eq);

	return 0;
}