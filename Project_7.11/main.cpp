#include<iostream>
#include<cstdlib>
using namespace std;
//P(x) = a0 + a1*x + a2*x^2 + ... + an*x^n - полином степени x

template<int power> class Polynom {
private:
	double a[power+1];
public:
	Polynom() {
		for (int i = 0; i <= power; i++) {
			a[i] = 0;
		}
	}

	Polynom(double* nums) {
		for (int i = 0; i <= power; i++) {
			a[i] = nums[i];
		}
	}

	void ShowAll(){
		cout << "| ";
		for (int i = 0; i <= power; i++) {
			cout<< a[i] << "| ";
		}
		cout << endl;
	}

	//Возвращает значение полинома в точке x
	double operator()(double x) {
		double S = 0; int q = 1; 
		for (int i = 0; i <= power; i++) {
			S += a[i] * q;
			q *= x;
		}
		return S;
	}

	//Возвращает коэффициент a 
	double &operator[](int x) {
		return a[x];
	}
	
	//Произведение двух полиномов
	template<int n> Polynom<power + n> operator*(Polynom<n> pol) {
		Polynom<power + n> tmp;
		for (int i = 0; i <= power; i++) {
			for (int j = 0; j <= n; j++) {
				tmp[i + j] += pol[j] * a[i];
			}
		}
		return tmp;
	}

	//Сложение двух полиномов
	template<int n> Polynom<(n > power ? n : power)> operator+ (Polynom<n> pol) {

		int i;
		Polynom<(n > power ? n : power)> tmp;
		for (i = 0; i <= power; i++) {
			tmp[i] += a[i];
		}
		for (i = 0; i <= n; i++) {
			tmp[i] += pol[i];
		}

		return tmp;
	};

	//Возвращает разность двух полиномов
	template<int n> Polynom<(n > power ? n : power)> operator-(Polynom<n> pol) {
		Polynom<(n > power ? n : power)> tmp;
		int i;
		for (i = 0; i <= power; i++) {
			tmp[i] += a[i];
		}
		for (i = 0; i <= n; i++) {
			tmp[i] -= pol[i];
		}
		return tmp;
	}

	//Нахождение производной нашего полинома по x 
	template<int power> Polynom<power - 1> Diff(Polynom<power> pol) {
		Polynom<power - 1> tmp;
		for (int i = 0; i <= power - 1; i++) {
			tmp[i] = pol[i + 1] * (i + 1);
		}
		return tmp;
	}
};

	int main() {
		setlocale(0, "rus");

		double A[] = { 1,2,3};
		double B[] = { 1,1,1,3 };

		Polynom<2> objA(A);
		Polynom<3> objB(B);
		objA.ShowAll();
		objB.ShowAll();
		

		Polynom<5> objC; 
		objC = objA * objB;
		objC.ShowAll();

		Polynom<3> objD;
		objD = objA + objB;
		objD.ShowAll();
	
		Polynom<3> objE;
		objE = objA - objB;
		objE.ShowAll();

		Polynom<2> objF;
		objF = objF.Diff(objB);
		objF.ShowAll();

		cin.get();
		return 0;
	}