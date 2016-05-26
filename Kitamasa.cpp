#include<vector>
#include<algorithm>
#include<assert.h>
#include<iostream>
using namespace std;

//O(N^2log(K))   
//N:�Q�����̍���
//K:���Ƃ߂鍀

//�X�[�p�[�t�B�{�i�b�`�����K���̒l�����߂���
//(�O��N�����玟�̍������܂鐔��)
//
//�Ⴆ�΁@N=3,
//���� a0=1,a1=2,a2=3, 
//�Q���� an = 2 * an-1 + 3 * an-2 + 4 * an-3
//���^����ꂽ���A
// a3 = 2 * a2 + 3 * a1 + 4 * a0 = 16
// a4 = 2 * a3 + 3 * a2 + 4 * a1 = 49
// ........
//
// an = {1,2,3,16,49,155, ......}    �ƂȂ�B

template<class T>
struct Kitamasa {
public:

	//�Q���� an = zenka[0] * an-k+1 + zenka[1] * an-k+2 + zenka[2] * an-k+3 + ......zenka[k-1]*an-1
	Kitamasa(const vector<int>&zenka) :z_size(zenka.size()), terms(2 * z_size-1, vector<T>(z_size)) {
		for (int i = 0; i < z_size; ++i) {
			vector<T>a(z_size, static_cast<T>(0));
			a[i] = static_cast<T>(1);
			terms[i] = (a);
		}

		for (int i = z_size; i < 2 * z_size-1; ++i) {
			for (int j = 0; j < z_size;++j){
				for (int k = 0; k < z_size;++k){
					terms[i][j] += zenka[k]*terms[i-z_size+k][j];
				}
			}
		}
	}


	//��num�������߂�
	//
	//
	//����
	//fst_terms ����
	//fst_terms={a0,a1,a2,.......ak-1}
	//num:���߂鍀��
	T solve(const vector<T>&fst_terms,const long long int num) {
		assert(fst_terms.size() == z_size);
		vector<T>v(getterm(num));
		T ans(0);
		for (int i = 0; i < z_size; ++i) {
			ans += fst_terms[i] * v[i];
		}
		return ans;
	}


private:

	vector<T>getterm(const long long int num) {
		if (num < static_cast<long long int >(z_size * 2-1)) {
			return terms[static_cast<int >(num)];
		}
		if (num % 2) {
			return plusone(multitwo(getterm(num / 2)));
		}
		else {
			return multitwo(getterm(num / 2));
		}
	}

	vector<T>multitwo(const vector<T> f) {
		vector<T>ans(2 * z_size - 1);
		vector<T>to(z_size);
		for (int j = 0; j <z_size; ++j) {
			for (int k = 0; k < z_size; ++k) {
				ans[j + k] += f[j] * f[k];
			}
		}
		for (int j = 0; j < z_size * 2-1; ++j) {
			for (int k = 0; k < z_size; ++k) {
				to[k] += ans[j] * terms[j][k];
			}
		}
		return to;
	}


	vector<T>plusone(const vector<T> f) {
		vector<T>t(f.size());

		for (unsigned int i = 1; i < f.size(); ++i) {
			//t[1]=f[0]+f[k-1]*f[0]
			t[i] = f[i - 1] + f.back()*terms[z_size][i];
		}
		t[0] = f.back()*terms[z_size][0];
		return t;
	}
	const int z_size;
	vector<vector<T>> terms;
};