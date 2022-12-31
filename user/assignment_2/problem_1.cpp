#include <limits>

#include "problem_1.hpp"

void mv_sec(const Matrix& a, double* b,  double* c){
  int i, j;
	double s;
	
	for(i=0; i<a.rows(); i++) {
		s = 0.0;
		for(j=0; j<a.cols(); j++) {
			s += a[i][j] * b[j];
		}
		c[i] = s;
	}
}

void mv_par(const Matrix& a, double* b, double* c){
  // TODO(exercise): Implement this for exercise

}

int search_sec(double* a, int a_size, double e){
  int i;
	int position = -1;
	
	for(i=0; i<a_size; i++) {
		if (a[i] == e) {
			position = i;
			break;
		}
	}
	return position;
}

int search_par(double* a, int a_size, int e){
  // TODO(exercise): Implement this for exercise
}

void merge(double* a, int der, int med, int izq){
  int i, j, k;
	double *temp = (double *) malloc(sizeof(double)*(der-izq));
	k = 0;
	i = izq;
	j = med;
	while((i < med) && (j < der))
	{
		if(a[i] < a[j]) {
			temp[k] = a[i];
			i++;
		}
		else {
			temp[k] = a[j];
			j++;
		}
		k++;
	}
	
	for(; i<med; i++) {
		temp[k] = a[i];
		k++;
	}
	
	for(; j<der; j++) {
		temp[k] = a[j];
		k++;
	}
	
	for(i=0; i<der-izq; i++) {
		a[i+izq] = temp[i];
	}
	free(temp);
}

void merge_sec(double* a, int size){
  if (size < 2) {return; }
  merge_sec(a, size/2);
  merge_sec(&a[size/2], size-size/2);

  merge(a,0,size/2, size);
}

void merge_par(double* a, int size){
  // TODO(exercise): Implement this for first exercise
}

void mm_sec(const Matrix& a,const Matrix& b,Matrix& c){
  int i, j, k;
	double s;
	
	for(i=0; i<a.rows(); i++) {
		for(j=0; j<b.cols(); j++) {
			s = 0.0;
			for(k=0; k<a.cols(); k++) {
				s += a[i][k] * b[k][j];
			}
			c[i][j] = s;
		}
	}  
}

void mm_par(const Matrix& a,const Matrix& b,Matrix& c){
  // TODO(exercise): Implement this for exercise
}