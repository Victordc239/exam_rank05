/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:20 by victor            #+#    #+#             */
/*   Updated: 2026/02/20 14:28:48 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRUEBA_HPP
#define PRUEBA_HPP

#include <iostream>

class vect2
{
	private:
		int x;
		int y;

	public:
		vect2();
		vect2(int num1, int num2);
		vect2(const vect2& source);
		vect2& operator=(const vect2& source);
		~vect2();

		int& operator[](int index);
		int operator[](int index) const;

		vect2& operator*=(int num);
		vect2& operator+=(const vect2& source);
		vect2& operator-=(const vect2& source);
		vect2& operator*=(const vect2& source);
		vect2& operator++();
		vect2& operator--();
		vect2 operator++(int);
		vect2 operator--(int);

		vect2 operator*(int num) const;
		vect2 operator+(const vect2& source) const;
		vect2 operator-(const vect2& source) const;
		vect2 operator*(const vect2& source) const;
		vect2 operator-() const;
		bool operator==(const vect2& source) const;
		bool operator!=(const vect2& source) const;
};



#endif