#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <complex>
using namespace std;


class Error {
public:
	virtual void print() = 0;
};

class ENotExistsIndex : public Error {
public:
	string ENEI;
	ENotExistsIndex() :ENEI("Invalid index!\n") {}
	void print() {
		cout << ENEI << endl;
	}
};

class EDivisionByZero : public Error {
public:
	string ENEI;
	EDivisionByZero() :ENEI("Division by zero!\n") {}
	void print() {
		cout << ENEI << endl;
	}
};

class ESize : public Error {
public:
	string ENEI;
	ESize() :ENEI("Sizes are't equal!") {}
	void print() {
		cout << ENEI << endl;
	}
};

class ESizeLessThan2 : public Error {
public:
	string ENEI;
	ESizeLessThan2() :ENEI("Sizes less than 2") {}
	void print() {
		cout << ENEI << endl;
	}
};


template <typename T>

class TemplateVector
{
private:
	size_t size;
	vector<T> arr;
	T eps;

public:

	/*class Iterator
	{
		vector<T>* ar = nullptr;
		size_t index = 0;
		friend class TemplateVector;

	public:

		Iterator() = default;

		Iterator(const TemplateVector<T>& _v, size_t i)
		{
			index = i;
			ar = _v.arr;
		}

		const vector<T>& operator*() const
		{
			return *ar[index];
		}

		vector<T>& operator*()
		{
			return *ar[index];
		}

		static Iterator begin(TemplateVector<T>& _v)
		{
			return Iterator(_v, 0);
		}

		static Iterator end(TemplateVector<T>& _v)
		{
			return Iterator(_v, _v.get_size());
		}

		Iterator& operator++()
		{
			if (index + 1 < *ar.size())
			{
				++index;
			}
			
			else
			{
				index = 0;
			}
			return *this;
		}

		bool operator==(const Iterator& v) const
		{
			return v.ar == ar && v.index == index;
		}
		bool operator!=(const Iterator& v) const
		{
			return !(*this == v);
		}
		
	};*/

	TemplateVector()
	{
		size = 0;
		eps = 0;
	}

	TemplateVector(const size_t d)
	{
		size = d;
		arr.reserve(d);
		eps = 0;
	}

	TemplateVector(const size_t d, const T* ar, const T epsilon)
	{
		size = d;
		arr.reserve(d);
		eps = epsilon;

		for (size_t i = 0; i < size; ++i)
		{
			arr.push_back(ar[i]);
		}

	}



	vector<T>& begin()
	{
		return arr.begin();
	}

	vector<T>& end()
	{
		return arr.end();
	}

	TemplateVector(const TemplateVector& source) = default;
	//{
	//	size = source.size;
	//	eps = source.eps;
	//	array.reserve(size);
	//	for (size_t i = 0; i < size; ++i)
	//	{
	//		array.push_back(source[i]);
	//	}
	//}

	~TemplateVector() = default;


	friend ostream& operator<<(ostream& os, TemplateVector& v)
	{
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i == 0)
			{
				os << '(' << v.arr.at(0) << ',';
			}

			else if (i < v.size - 1)
			{
				os << v.arr.at(i) << ',';
			}

			else if (i == v.size - 1)
			{
				os << v.arr.at(i) << ')';
			}
		}

		os << endl;

		return os;
	}

	void set_eps(const T e)
	{
		eps = e;
	}

	bool operator == (const TemplateVector& v) const
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			if (abs(arr.at(i) - v.arr.at(i)) > eps)
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const TemplateVector<T>& v) const
	{
		return !(*this == v);
	}

	TemplateVector operator + (const TemplateVector& v) const
	{
		TemplateVector obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) + v.arr.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector& operator += (const TemplateVector& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->arr.emplace(i,arr.at(i) + v.arr.at(i));
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector operator - (const TemplateVector& v) const
	{
		TemplateVector obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) - v.arr.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) - v[i]);
		}
		return obj;
	}

	TemplateVector& operator -= (const TemplateVector& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->arr.at(i) = arr.at(i) - v.arr.at(i);
		}
		return *this;
	}

	TemplateVector<complex<T>> operator -= (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.emplace(i, arr.at(i) - v[i]);
		}
		return obj;
	}

	T operator * (const TemplateVector& v) const
	{
		T multiplication = 0;
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += arr.at(i) * v.arr.at(i);
		}
		return multiplication;
	}

	complex<T> operator * (const TemplateVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += arr.at(i) * conj(v[i]);
		}
		return multiplication;
	}

	TemplateVector operator * (const T s)
	{
		TemplateVector<T> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) * s);
		}
		return obj;

	}

	TemplateVector<complex<T>> operator * (const complex<T> s)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back( arr.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector operator * (const T s, const TemplateVector& v)
	{
		TemplateVector<T> obj(v.size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v.arr.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector<complex<T>> operator * (const complex<T> s, const TemplateVector& v)
	{
		TemplateVector<complex<T>> obj(v.size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back( v.arr.at(i) * s);
		}
		return obj;

	}

	TemplateVector operator / (const T s) const
	{
		TemplateVector obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) / s);
		}
		return obj;
	}

	TemplateVector<complex<T>> operator / (const complex<T> s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj.arr.push_back(arr.at(i) / s);
		}
		return obj;
	}

	T operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return arr.at(i);
	}

	T& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return arr.at(i);
	}

	size_t get_size() const
	{
		return size;
	}

	T vector_length()
	{
		T sum = 0;

		for (size_t i = 0; i < size; ++i)
		{
			sum += pow(arr.at(i), 2);
		}

		return sqrt(sum);
	}


	T calc_coordinate(const T k, const TemplateVector& v, const size_t index)
	{
		T coordinate = (arr.at(index) + (v.arr.at(index) * k)) / (1.0 + k);
		return coordinate;
	}

	complex<T> calc_coordinate(const complex<T> k, const TemplateVector<complex<T>>& v, const size_t index)
	{
		complex<T> coordinate = (arr.at(index) + (v[index] * k)) / (1.0 + k);
		return coordinate;
	}

	TemplateVector radius_vector(TemplateVector& v)
	{
		if (size != v.size) throw ESize();
		T length_a = vector_length(), length_b = v.vector_length();
		//cout << length_a << " , " << length_b << endl; // ïðîñòî ïå÷àòü ïðîâåðêè
		T k = length_a / length_b;
		T* coordinates = new T[size];


		for (size_t i = 0; i < size; ++i)
		{
			coordinates[i] = calc_coordinate(k, v, i);
		}

		TemplateVector obj(size, coordinates, 0);

		return obj;
	}

	TemplateVector<complex<T>> radius_vector(TemplateVector<complex<T>>& v)
	{
		if (size != v.get_size()) throw ESize();
		T length_a = vector_length();
		complex<T> length_b = v.vector_length();
		//cout << length_a << " , " << length_b << endl; // ïðîñòî ïå÷àòü ïðîâåðêè
		complex<T> k = length_a / length_b;
		complex<T>* coordinates = new complex<T>[size];


		for (size_t i = 0; i < size; ++i)
		{
			coordinates[i] = calc_coordinate(k, v, i);
		}

		TemplateVector<complex<T>> obj(size, coordinates, 0);

		return obj;
	}

	//TemplateVector operator =(const TemplateVector& v)
	//{
	//	if (size != v.size)throw ESize();

	//	for (size_t i = 0; i < size; ++i)
	//	{
	//		array.emplace(i, v.array.at(i));
	//	}
	//	return *this;
	//}



};

template <typename T>

class TemplateVector<complex<T>>
{
private:
	size_t size;
	vector<complex<T>> array;
	T eps;
public:

	TemplateVector()
	{
		size = 1;
		eps = 0;
		array.reserve(1);
	}

	TemplateVector(const size_t d)
	{
		size = d;
		array.reserve(d);
		eps = 0;
	}

	TemplateVector(const size_t d, const complex<T>* ar, const T epsilon)
	{
		size = d;
		array.reserve(d);
		eps = epsilon;

		for (size_t i = 0; i < size; ++i)
		{
			array.push_back(ar[i]);
		}

	}


	TemplateVector(const TemplateVector<complex<T>>& source) = default;
	//{
	//	size = source.size;
	//	eps = source.eps;
	//	array.reserve(size);
	//	for (size_t i = 0; i < size; ++i)
	//	{
	//		array.push_back(source[i]);
	//	}
	//}

	~TemplateVector() = default;


	friend ostream& operator<<(ostream& os, const TemplateVector<complex<T>>& v)
	{
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i == 0)
			{
				os << '(' << v.array.at(0) << ',';
			}

			else if (i < v.size - 1)
			{
				os << v.array.at(i) << ',';
			}

			else if (i == v.size - 1)
			{
				os << v.array.at(i) << ')';
			}
		}

		os << endl;

		return os;
	}

	void set_eps(const T e)
	{
		eps = e;
	}

	bool operator == (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			if (abs(array.at(i) - v.array.at(i)) > eps)
			{
				return false;
			}
		}
		return true;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) + v.array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<T>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->array[i] = array[i] + v.array[i];
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<T>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->array.emplace(i, array.at(i) + v[i]);
		}
		return *this;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) - v.array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<T>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) - v[i]);
		}
		return obj;
	}

	TemplateVector<complex<T>>& operator -= (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->array.emplace(i, array.at(i) - v[i]);
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator -= (const TemplateVector<T>& v) const
	{
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->array.emplace(i, array.at(i) - v[i]);
		}
		return *this;
	}

	complex<T> operator * (const TemplateVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += array.at(i) * conj(v[i]); //a= [z1,z2,z3] b= [z4,z5,z6] multi += z1*z4
		}
		return multiplication;
	}

	complex<T> operator * (const TemplateVector<T>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += array.at(i) * v[i];
		}
		return multiplication;
	}

	TemplateVector<complex<T>> operator * (const T s)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector<complex<T>> operator * (const T s, const TemplateVector<complex<T>>& v)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v.array.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector<complex<T>> operator * (const complex<T> s, const TemplateVector<complex<T>>& v)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v.array.at(i) * s);
		}
		return obj;

	}

	TemplateVector<complex<T>> operator * (const complex<T> s)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array[i] * s);
		}
		return obj;

	}

	TemplateVector<complex<T>> operator / (const T s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) / s);
		}
		return obj;
	}

	TemplateVector<complex<T>> operator / (const complex<T> s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj.array.push_back(array.at(i) / s);
		}
		return obj;
	}

	complex<T> operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return array.at(i);
	}

	complex<T>& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return array.at(i);
	}

	size_t get_size() const
	{
		return size;
	}

	complex<T> vector_length()
	{
		complex<T> sum = 0;

		for (size_t i = 0; i < size; ++i)
		{
			sum += pow(array.at(i), 2);
		}

		return sqrt(sum);
	}

	complex<T> calc_coordinate(complex<T> k, TemplateVector<complex<T>>& v, const size_t index)
	{
		complex<T> coordinate = (array.at(index) + (v.array.at(index) * k)) / (1.0 + k);
		return coordinate;
	}

	complex<T> calc_coordinate(complex<T> k, TemplateVector<T>& v, const size_t index)
	{
		complex<T> coordinate = (array.at(index) + (v[index] * k)) / (1.0 + k);
		return coordinate;
	}

	TemplateVector<complex<T>> radius_vector(TemplateVector<T>& v)
	{
		if (size != v.get_size()) throw ESize();
		complex<T> length_a = vector_length();
		T length_b = v.vector_length();
		//cout << length_a << " , " << length_b << endl; // ïðîñòî ïå÷àòü ïðîâåðêè
		complex<T> k = length_a / length_b;
		complex<T>* coordinates = new complex<T>[size];


		for (size_t i = 0; i < size; ++i)
		{
			coordinates[i] = calc_coordinate(k, v, i);
		}

		TemplateVector<complex<T>> obj(size, coordinates, 0);

		return obj;
	}

	TemplateVector<complex<T>> radius_vector(TemplateVector<complex<T>>& v)
	{
		if (size != v.size) throw ESize();
		complex<T> length_a = vector_length();
		complex<T> length_b = vector_length();
		//cout << length_a << " , " << length_b << endl; // ïðîñòî ïå÷àòü ïðîâåðêè
		complex<T> k = length_a / length_b;
		complex<T>* coordinates = new complex<T>[size];


		for (size_t i = 0; i < size; ++i)
		{
			coordinates[i] = calc_coordinate(k, v, i);
		}

		TemplateVector<complex<T>> obj(size, coordinates, 0);

		return obj;
	}

	TemplateVector<complex<T>> operator =(const TemplateVector<complex<T>>& v)
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			array.emplace(i, v.array.at(i));
		}
		return *this;
	}

};


int main()
{
	int fir_array[3] = { 1, 2, 3 };
	int sec_array[3] = { 4, 5, 6 };

	TemplateVector<int> first(3, fir_array, 0), second(3, sec_array, 0);
	cout << first << endl;
	TemplateVector<int> resultsum = first + second;
	cout << "sum: " << resultsum << endl;

	double first_array[3] = { 1.1, 2.2, 3.3 };
	double second_array[3] = { 4.4, 5.5, 6.6 };

	TemplateVector<double> f_v(3, first_array, 0.5), s_v(3, second_array, 0.5);
	TemplateVector<double> resultsubtraction = s_v - f_v;
	cout << "subtraction: " << resultsubtraction << endl;
	cout << "operator [] test: " << resultsubtraction[0] << endl;

	int resultmultiv = first * second;
	cout << "result of multiplication of vectors : " << resultmultiv << endl;

	TemplateVector<double> resultmultic = s_v * 5;
	cout << "result of multiplication : " << resultmultic << endl;

	TemplateVector<double> rad_vec = f_v.radius_vector(s_v);
	cout << "test of radius vector : " << rad_vec << endl;

	complex<double>  z1(1, 2), z2(3, 4), z3(5, 6), z4(7, 8), z5(9, 10), z6(11, 12);
	complex<double> arr[3] = { z1, z2, z3 }, arr2[3] = { z4, z5, z6 };
	TemplateVector<complex<double>> complexv(3, arr, 0.5), complexv2(3, arr2, 0.5);
	cout << "complexv : " << complexv << endl;
	cout << "complexv2 : " << complexv2 << endl;

	complex<double> resultofmult = complexv * complexv2;
	cout << "test of multi : " << resultofmult << endl;
	complex<double> multi_of_double_and_complex = f_v * complexv;
	cout << "test multi_of_double_and_complex : " << multi_of_double_and_complex << endl;

	TemplateVector<complex<double>> plusresult = complexv + f_v;
	cout << "test of summ operation : " << plusresult << endl;

	TemplateVector<complex<double>> result1 = complexv.radius_vector(complexv2), result2 = complexv.radius_vector(f_v);
	cout << "test of radius_vector (complex<double>, complex<double>) : " << result1 << endl;
	cout << "test of radius_vector (complex<double>, double) : " << result2 << endl;

	double test_for_rv1[2] = { 3, 7 }, test_for_rv2[2] = { 8, 4 };
	TemplateVector<double> vector1(2, test_for_rv1, 0.5), vector2(2, test_for_rv2, 0.5);
	TemplateVector<double> result4 = vector1.radius_vector(vector2);
	TemplateVector<complex<double>> result3 = f_v.radius_vector(complexv);

	cout << "test of radius_vector (double , double) : " << result4 << endl;
	cout << "test of radius_vector (double, complex<double>) , must be same as (complex<double>, double) : " << endl << result3 << endl;



	for (auto y : f_v)
	{
		cout << y << endl;
	}



	return 0;
}