
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define ERROR 0 

typedef struct quadEq {

	double a, b, c; 
	double d; 
	double x1, x2;

int input(quadEq *temp) { 
	if (temp == NULL) return ERROR;
	scanf("%lf %lf %lf", &(temp->a), &(temp->b), &(temp->c));
	return 1;
}

int D(quadEq* eq) { 
	if (eq == NULL) return ERROR;
	double a = eq->a;
	double b = eq->b;
	double c = eq->c;
	eq->d = b * b - 4 * a * c;
	return 1;
}

int roots(quadEq* eq) {
	if (eq == NULL) return ERROR;
	double a = eq->a;
	double b = eq->b;
	double d = eq->d;

	if (d < 0) return 0;
	eq->x1 = (-b + sqrt(d)) / (2 * a);
	eq->x2 = (-b - sqrt(d)) / (2 * a);
	return 1;
}

int print(quadEq* eq) {
	if (eq == NULL) return ERROR;

	if (eq->d < 0) {

		printf("No roots");
		return 1;
	}
	if (eq->d == 0) {

		printf("x = %f", eq->x1);
		return 1;
	}
	if (eq->d > 0) {

		printf("x1 = %f\nx2 = %f", eq->x1, eq->x2);
		return 1;
	}

}

int main() {

	quadEq eq;
	input(&eq);
	D(&eq);
	roots(&eq);
    print(&eq);

	return 0;
}