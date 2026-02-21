/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:20:54 by fatkeski          #+#    #+#             */
/*   Updated: 2026/02/20 11:27:59 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

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

std::ostream& operator<<(std::ostream& os,const vect2& source);
vect2 operator*(int num, const vect2& source);

#endif

