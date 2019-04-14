#pragma once

#include <iostream>
#include <cstdint>
#include <array>
#include <bitset>

template<typename T, std::size_t UNIVERSE_SIZE>
class UniversalSet
{
	public:
		class Vector
		{
			public:
				class Iterator
				{
					private:
						Iterator(const Vector *vector_ptr);
						Iterator(const Vector *vector_ptr, std::size_t i);

					public:
						Iterator(const Iterator&) = default;
						Iterator& operator=(const Iterator&) = default;
						Iterator(Iterator&&) = default;
						Iterator& operator=(Iterator&&) = default;

						friend class Vector;

					private:
						const Vector *vector_ptr_;
						std::size_t i_;

					public:
						bool operator==(const Iterator &it) const;
						bool operator!=(const Iterator &it) const;
						// Przechodzi na kolejny (istniejacy!) element w "Vector"
						Iterator& operator++();
						Iterator operator++(int);
						const T& operator*() const;
						const T* operator->() const;
						operator bool() const;
				};

			public:
				Vector(const UniversalSet *universe_ptr);
				Vector(const UniversalSet *universe_ptr, const std::bitset<UNIVERSE_SIZE> &bs);
				Vector(const Vector&) = default;
				Vector& operator=(const Vector &universe) = default;
				Vector(Vector &&universe) = default;
				Vector& operator=(Vector &&universe) = default;

				friend class Iterator;

				std::bitset<UNIVERSE_SIZE> bs_;

			private:
				const UniversalSet<T, UNIVERSE_SIZE> *universe_ptr_;

			public:
				// Zwraca liczbe elementów reprezentowanych przez "Vector"
				std::size_t count() const;
				// Jezeli element o indeksie "i" nie nalezy do "Vector" to dodaje ten element oraz zwraca "Iterator" do dodanego elementu i "true", w przeciwnym razie zwraca samo co "end()" i "false"
				/*std::pair<Iterator, bool>*/ void insert(std::size_t i);
				// Jezeli element o indeksie "i" nalezy do "Vector" to zwraca "true", w przeciwnym razie zwraca "false"
				bool isMember(std::size_t i) const;
				// Jeżeli element o indeksie "i" należy do "Vector" to zwraca "Iterator" do tego elementu, w przeciwnym razie zwraca to samo co "end()"
				Iterator elemIterator(std::size_t i) const;
				// Jezeli element o indeksie "i" nalezy do "Vector" to usuwa ten element i zwraca "true", w przeciwnym razie zwraca "false"
				bool remove(std::size_t i);
				// Zwraca "true" jeżeli obiekt "v2" reprezentuje ten sam zestaw elementow z tego samego uniwersum, w przeciwnym razie zwraca "false"
				bool operator==(const Vector &v2) const;
				bool operator!=(const Vector &v2) const;
				// Zwraca sume zbiorow
				Vector operator+(const Vector &v2) const
				{
					typename UniversalSet<T, UNIVERSE_SIZE>::Vector helpvec(v2.universe_ptr_, UNIVERSE_SIZE);
					helpvec.bs_.reset();
					for(size_t i = 0; i < UNIVERSE_SIZE; i++)
					{
						if(this->bs_.test(i) == true)
							helpvec.bs_.set(i);
						if(v2.bs_.test(i) == true)
							helpvec.bs_.set(i);
					}

					return helpvec;
				}
				// Zwraca roznice zbiorow
				Vector operator-(const Vector &v2) const
				{
					typename UniversalSet<T, UNIVERSE_SIZE>::Vector helpvec(v2.universe_ptr_, UNIVERSE_SIZE);
					helpvec.bs_.reset();
					for(size_t i = 0; i < UNIVERSE_SIZE; i++)
					{
						if(this->bs_.test(i) == false)
							continue;
						else if(this->bs_.test(i) == v2.bs_.test(i))
							continue;
						else
							helpvec.bs_.set(i);
					}

					return helpvec;
				}
				// Zwraca czesc wspolna zbiorow
				Vector operator*(const Vector &v2) const
				{
					typename UniversalSet<T, UNIVERSE_SIZE>::Vector helpvec(v2.universe_ptr_, UNIVERSE_SIZE);
					helpvec.bs_.reset();
					for(size_t i = 0; i < UNIVERSE_SIZE; i++)
					{
						if(this->bs_.test(i) == false)
							continue;
						else if(this->bs_.test(i) != v2.bs_.test(i))
							continue;
						else
							helpvec.bs_.set(i);
						
					}

					return helpvec;
				}
				// Zwraca roznice symetryczna zbiorow
				Vector operator/(const Vector &v2) const
				{
					typename UniversalSet<T, UNIVERSE_SIZE>::Vector helpvec(v2.universe_ptr_, UNIVERSE_SIZE);
					helpvec.bs_.reset();
					for(size_t i = 0; i < UNIVERSE_SIZE; i++)
					{
						if(this->bs_.test(i) == v2.bs_.test(i))
							continue;
						else
							helpvec.bs_.set(i);
					}

					return helpvec;
				}
				// Zwraca "Iterator" na poczatek
				Iterator begin() const;
				// Zwraca "Iterator" za koniec
				Iterator end() const;
				void lol()
				{
					std::cout << bs_ << std::endl;
				}
				void lol() const
				{
					std::cout << bs_ << std::endl;
				}
				void lol1()
				{
					for(int i = 0; i < bs_.size(); i++)
					{
						std::cout << universe_ptr_.first.at(i) << std::endl;
					}
				}
		};

	public:
		UniversalSet(const std::array<T, UNIVERSE_SIZE> &elems);
		UniversalSet(const UniversalSet&) = default;
		UniversalSet& operator=(const UniversalSet&) = default;
		UniversalSet(UniversalSet&&) = default;
		UniversalSet& operator=(UniversalSet&&) = default;

	private:
		std::array<T, UNIVERSE_SIZE> elems_;

	public:
		constexpr std::size_t universeSize() const { return UNIVERSE_SIZE; }
		const T& elem(std::size_t i) const;
		const T& operator[](std::size_t i) const;
		// Zwraca pusty "Vector"
		Vector makeVector() const;
};

///////////////////////////////////////////////////////////////////////////////

/*Klasa UniversalSet funkcje publiczne****************************************/

template <typename T, std::size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::UniversalSet(const std::array<T, UNIVERSE_SIZE> &elem)
{
	for(size_t i = 0; i < elem.size(); i++)
	{
		this->elems_.at(i) = elem.at(i);
	}
}

template <typename T, std::size_t UNIVERSE_SIZE>
const T& UniversalSet<T, UNIVERSE_SIZE>::elem(std::size_t i) const
{
	return this->elems_.at(i);
}

template <typename T, std::size_t UNIVERSE_SIZE>
const T& UniversalSet<T, UNIVERSE_SIZE>::operator[](std::size_t i) const
{
	return this->elems_.at(i);
}

template<typename T, std::size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector UniversalSet<T, UNIVERSE_SIZE>::makeVector() const
{
	Vector helpvec ( this);
	helpvec.bs_.reset();
	return helpvec;
}

/*Klasa vector funkcje publiczne*/

template <typename T, std::size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Vector(const UniversalSet *universe_ptr)
{
	universe_ptr_ = universe_ptr;
}

template <typename T, std::size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Vector(const UniversalSet *universe_ptr, const std::bitset<UNIVERSE_SIZE> &bs)
{
	universe_ptr_ = universe_ptr;
	bs_ = bs;
}

template <typename T, std::size_t UNIVERSE_SIZE>
std::size_t UniversalSet<T, UNIVERSE_SIZE>::Vector::count() const
{
	int helpint = 0;

	for(std::size_t i = 0; i < bs_.size(); i++)
	{
		if(bs_.test(i))
		{
			helpint++;
		}
	}

	return helpint;
}

template <typename T, std::size_t UNIVERSE_SIZE>
void UniversalSet<T, UNIVERSE_SIZE>::Vector::insert(std::size_t i)
{
	if(bs_.test(i) == false)
		bs_.set(i);
}

template <typename T, std::size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::isMember(std::size_t i) const
{
	if(bs_.test(i) == true)
		return true;
	else 
		return false;
}

template <typename T, std::size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::remove(std::size_t i)
{
	if(bs_.test(i) == true)
	{
		bs_.reset(i);
		return true;
	} else
	{
		return false;
	}
}

template <typename T, std::size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::operator==(const Vector &v2) const
{
	if(this->bs_ == v2.bs_)
		return true;
	else 
		return false;
}

template <typename T, std::size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::operator!=(const Vector &v2) const
{
	if(this->bs_ != v2.bs_)
		return true;
	else 
		return false;
}

template <typename T, std::size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator UniversalSet<T, UNIVERSE_SIZE>::Vector::begin() const
{
	Iterator it(this, UNIVERSE_SIZE);
	return it;
}

template <typename T, std::size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator UniversalSet<T, UNIVERSE_SIZE>::Vector::end() const
{
	Iterator it(this);
	return it;
}

/*Klasa iterator funkcje prywatne*/

template <typename T, std::size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::Iterator(const Vector *vector_ptr)
{
	this->vector_ptr_ = vector_ptr;
}

template <typename T, std::size_t UNIVERSE_SIZE>
UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::Iterator(const Vector *vector_ptr, std::size_t i)
{
	this->vector_ptr_ = vector_ptr;
	this->i_ = i;
}

/*Klasa iterator funkcje publiczne*/

template <typename T, std::size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator==(const Iterator &it) const
{
	return (this->vector_ptr_ == it.vector_ptr_);
}

template <typename T, std::size_t UNIVERSE_SIZE>
bool UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator!=(const Iterator &it) const
{
	return !((*this) == it);
}

template <typename T, std::size_t UNIVERSE_SIZE>
typename UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::Iterator& UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator++()
{

}

template <typename T, std::size_t UNIVERSE_SIZE>
const T& UniversalSet<T, UNIVERSE_SIZE>::Vector::Iterator::operator*() const
{
	
}
