#include "common.h"

//Martrix类未完成
template<int N>
class Martrix {
public:
	double* _elem;
	Martrix() { _elem = new double[N*N]; }
	Martrix(double m[][N]) { _elem = new double[N*N]; for (int i = 0; i < N*N; i++)_elem[i] = m[0][i]; }
	~Martrix() { delete[]_elem; }
};

//方阵相乘,求逆,求解
template<int N>
class Martrix_calculate {
private:
	//寻找某行中[lo,hi)列中绝对值最大的数,返回其列
	static int find_abs_min_in_row(double M[][N], int row,int lo,int hi) {
		int col = lo;
		for (int i = lo; i < hi; i++)
			if (abs(M[row][i] > abs(M[row][col])))
				col = i;
		return col;
	}
	//寻找某列中[lo,hi)行中绝对值最大的数,返回其地址
	static int find_abs_min_in_col(double M[][N], int col,int lo,int hi) {
		int row = lo;
		for (int i = lo; i < hi; i++)
			if (abs(M[i][col] > abs(M[row][col])))
				row = i;
		return row;
	}
	//交换列
	static void swap_col(double M[][N], int col1, int col2) {
		for (int i = 0; i < N; i++)
			swap(M[i][col1], M[i][col2]);
	}
	//交换行
	static void swap_row(double M[][N],int row1,int row2) {
		for (int i = 0; i < N; i++)
			swap(M[row1][i], M[row2][i]);
	}
	//行i-m*行j
	static void minus_row(double M[][N],int row_i, double m, int row_j) {
		for (int i = 0; i < N; i++)
			M[row_i][i] -= m * M[row_j][i];
	}
	//列i-m*列j
	static void minus_col(double M[][N], int col_i, double m, int col_j) {
		for (int i = 0; i < N; i++)
			M[i][col_i] -=  m * M[i][col_j];
	}
public:
	//矩阵求逆,若是奇异矩阵返回false
	static bool Martrix_reverse(double M[][N], double reverse[][N]) {
		double L[N][N], U[N][N], P[N][N];
		if (!LUP_decomposition(M, L, U, P))//奇异矩阵
			return false;
		//通过Ax=b一个一个求出矩阵的每一列逆
		double x[N], b[N];
		for (int i = 0; i < N; i++) //初始化
			b[i] = 0;
		//计算Ax=[1,0,0,..],Ax=[0,1,0,..},...
		for (int i = 0; i < N; i++) {
			if (i != 0)b[i - 1] = 0.0;
			b[i] = 1.0;
			Martrix_solution(M, b, x);//求得x
			for (int j = 0; j < N; j++) {
					reverse[j][i] = x[j];
			}
		}
		precision_adjust(&reverse[0][0], N, N);
		return true;
	}
	//计算C=A*B,用最平凡的O(n^3)方法
	static void Martrix_multiplication(double A[][N],double B[][N],double C[][N]) {
		double *temp = new double[N*N];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				temp[i*N+j] = 0.0;
				for (int k = 0; k < N; k++)
					temp[i*N+j] += A[i][k] * B[k][j];
			}
		}
		//将temp复制到C中
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				C[i][j] = temp[i*N + j];
			}
		precision_adjust(&C[0][0], N, N);
		delete[]temp;
	}
	//将A进行LUP分解,PA=LU,若返回false表示A是奇异矩阵
	static bool LUP_decomposition(double A[][N], double L[][N], double U[][N], double P[][N]) {
		//先把A复制到U中
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				U[i][j] = A[i][j];
		//P矩阵初始化为对角矩阵,并随着选取最大值的过程调整,并把L更新为0数组
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) {
				if (i == j)
					P[i][j] = 1.0;
				else P[i][j] = 0.0;
				L[i][j] = 0.0;
			}
		for (int i = 0; i < N; i++) {
			int row = find_abs_min_in_col(U, i, i, N);//在第i列中寻找最大绝对值的行所在
			if (U[row][i] == 0.0)//最大绝对值是0,则这一行都是0,返回false
				return false;
			if (i != row) {
				swap_row(U, i, row);//交换这两行
				swap_row(P, i, row);//P也进行调整
				swap_row(L, i, row);//L也要调整
			}
			//更新L数组
			L[i][i] = 1;
			for (int j = i + 1; j < N; j++) {//将U数组行第i列调整为上对角,即减到0,并且在L数组中更新
				double div = U[j][i]/U[i][i];
				L[j][i] = div;
				minus_row(U, j, div, i);
			}
		}
		return true;
	}
	//Ax=b,通过传入的A和b求x,返回true表示正常求解,false表示A是奇异矩阵,无解或有多个解
	static bool Martrix_solution(double A[][N], double b[N], double x[N]) {
		double L[N][N], U[N][N], P[N][N];
		//求得PA=LU
		if (!LUP_decomposition(A, L, U, P))//奇异矩阵
			return false;
		/*
		Ax=b,PAx=Pb,LUx=Pb,Ly=Pb,求得y,由Ux=y求得x
		*/
		//计算pb
		double pb[N];
		for (int i = 0; i < N; i++) {
			pb[i] = 0.0;
			for (int j = 0; j < N; j++) {
				pb[i] += P[i][j] * b[j];
			}
		}
		double y[N];
		//计算y,Ly=Pb
		for (int i = 0; i < N; i++) {
			y[i] = pb[i];
			for (int j = 0; j < i; j++) 
				y[i] -= L[i][j] * y[j];
			y[i] /= L[i][i];
		}
		//计算x,Ux=y
		for (int i = N - 1; i >= 0; i--) {
			x[i] = y[i];
			for (int j = i + 1; j < N; j++)
				x[i] -= U[i][j] * x[j];
			x[i] /= U[i][i];
		}
		precision_adjust(x, N, 1);
		return true;
	}
	static void log_martrix(const char*str, double* M,int row_num,int col_num) {
		std::cout << str << std::endl;
		//cout << fixed;
		for (int i = 0; i < row_num; i++) {
			for (int j = 0; j < col_num; j++)
				std::cout << setw(7) << setprecision(3)<<  M[i*col_num+j];
			std::cout << std::endl;
		}
	}
	//由于double存在精度问题,所以对其进行调整,并且使-0都变为0
	static void precision_adjust(double *M, int row_num, int col_num) {
		for (int i = 0; i < row_num*col_num; i++) {
			double db = round(M[i]);
			if (abs(M[i] - db) <= 0.000001)
				M[i] = db;
			if (M[i] == 0.0)
				M[i] = 0.0;
		}
	}
};

int main28() {
	const int N = 4;
	double A[N][N] = 
	{ 
		2,1,4,3,
		4,2,1,3,
		1,3,4,6,
		4,1,4,3 
	};
	std::cout << "测试LUP分解" << std::endl;
	double L[N][N], U[N][N], P[N][N];
	Martrix_calculate<N>::LUP_decomposition(A, L, U, P);
	Martrix_calculate<N>::log_martrix("L:", &L[0][0], N, N);
	Martrix_calculate<N>::log_martrix("U:", &U[0][0], N, N);
	Martrix_calculate<N>::log_martrix("P:", &P[0][0], N, N);
	double temp[N][N];
	Martrix_calculate<N>::Martrix_multiplication(L, U, temp);
	Martrix_calculate<N>::log_martrix("LU:", &temp[0][0], N, N);
	Martrix_calculate<N>::Martrix_multiplication(P, A, temp);
	Martrix_calculate<N>::log_martrix("PA:", &temp[0][0], N, N);

	std::cout << "测试矩阵求解Ax=b" << std::endl;
	double b[N] = { 2,7,-1,6 };
	double x[N];
	Martrix_calculate<N>::Martrix_solution(A, b, x);
	Martrix_calculate<N>::log_martrix("x:", x, 4,1);

	std::cout << "测试矩阵求逆A^-1" << std::endl;
	double reverse_A[N][N];
	Martrix_calculate<N>::Martrix_reverse(A, reverse_A);
	Martrix_calculate<N>::log_martrix("reverse_A:", &reverse_A[0][0], N, N);
	double E[N][N];
	Martrix_calculate<N>::Martrix_multiplication(A, reverse_A, E);
	Martrix_calculate<N>::log_martrix("A*reverse_A:", &E[0][0], N, N);


	return 0;
}