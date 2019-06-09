#ifndef GEL_GSYSTEM_RANKTABLE_HPP
#define GEL_GSYSTEM_RANKTABLE_HPP
#include <array>
#include <fstream>
#include <algorithm>
#include <optional>
#include <string>
#include <stdexcept>
namespace gel {
template<typename D, int N>
class RankTable {
	public:
	explicit RankTable();
	void reset();
	void insert(const D data);
	template<int Index>
	std::optional<D> at() const;

	static RankTable<D, N> read(const std::string& filename);

	static void write(const std::string& filename, const RankTable<D, N>& data);

	private:
	// D required value_t
	// example: class HogeData { using value_t = float; }
	std::array<std::optional<D>, N> table;
};

template<typename D, int N>
inline RankTable<D, N>::RankTable() : table() {
	reset();
}

template<typename D, int N>
inline void RankTable<D, N>::reset() {
	std::fill(table.begin(), table.end(), std::nullopt);
}

template<typename D, int N>
inline void RankTable<D, N>::insert(const D data) {
	int r = N;
	for(int i=0; i<N; i++) {
		if(!table[i]) {
			table[i] = data;
			r = i;
			break;
		}
	}
	if(r == N) {
		for(int i=N-1; i>=0; i++) {
			auto ev = ((*table[i]).value);
			//if(data.value > ev) {
			if(D::compare(data, *table[i]) > 0) {
				for(int j=N-1; j>i; j--) {
					table[j-1] = table[j];
				}
				table[i] = data;
				break;
			}
		}
	}
	std::sort(table.begin(), table.end(), [](auto a, auto b){
		if(!a && !b) {
			return true;
		}
		if(!a) {
			return false;
		}
		if(!b) {
			return false;
		}
		//return (*a).value > (*b).value;
		return (D::compare(*a, *b)) > 0;
	});
}

template<typename D, int N>
template<int Index>
inline std::optional<D> RankTable<D,N>::at() const {
	return table[Index];
}

template<typename D, int N>
inline RankTable<D,N> RankTable<D,N>::read(const std::string& filename) {
	RankTable<D, N> rdata;
	std::ifstream ifs(filename);
	// read item count
	std::string line;
	std::getline(ifs, line);
	int items = std::stoi(line);
	int icount = 0;
	if(items != N) {
		throw std::logic_error("invalid item count");
	}
	// read items
	while(!ifs.eof())  {
		std::getline(ifs, line);
		// D required |D D::read(const std::string& line)|
		if(line == "NULL") {
			rdata.table[icount] = std::nullopt;
		} else {
			D data = D::read(line);
			rdata.table[icount] = data;
		}

		icount++;
		if(icount == items) {
			break;
		}
	}
	return rdata;
}
template<typename D, int N>
inline void RankTable<D,N>::write(const std::string& filename, const RankTable<D, N>& data) {
	std::ofstream ofs(filename);
	ofs << N << std::endl;
	for(int i=0; i<N; i++) {
		// D required |std::string D::write(const D& data)|
		if(data.table[i]) {
			ofs << D::write(*(data.table[i])) << std::endl;
		} else {
			ofs << "NULL" << std::endl;
		}
	}
}

template<typename T>
struct NumericRData {
	T value;
	// converting constructor
	NumericRData(const T value);
	using value_t = T;
	static int compare(const NumericRData<T>& a, const NumericRData<T>& b);
	static std::string write(const NumericRData<T>& data);
	static NumericRData<T> read(const std::string& line);
};
template<typename T>
inline NumericRData<T>::NumericRData(const T value) : value(value) {
}


template<typename T>
inline int NumericRData<T>::compare(const NumericRData<T>& a, const NumericRData<T>& b)  {
	return a.value - b.value;
}

template<typename T>
inline std::string NumericRData<T>::write(const NumericRData<T>& data) {
	return std::to_string(data.value);
}

template<>
inline NumericRData<int> NumericRData<int>::read(const std::string& line) {
	NumericRData<int> d(0);
	d.value = std::stoi(line);
	return d;
}
template<>
inline NumericRData<float> NumericRData<float>::read(const std::string& line) {
	NumericRData<float> d(0);
	d.value = std::stof(line);
	return d;
}
template<>
inline NumericRData<double> NumericRData<double>::read(const std::string& line) {
	NumericRData<double> d(0);
	d.value = std::stod(line);
	return d;
}
using IntegerRData = NumericRData<int>;
using FloatRData = NumericRData<float>;
using DoubleRData = NumericRData<double>;
}
#endif