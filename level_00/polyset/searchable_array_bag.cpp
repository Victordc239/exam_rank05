/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:26:23 by fatkeski          #+#    #+#             */
/*   Updated: 2026/02/19 20:46:28 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{

}

searchable_array_bag::searchable_array_bag(const searchable_array_bag& source) : array_bag(source)
{

}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
	if(this != &source)
	{
		array_bag::operator=(source);
	}
	return(*this);
}

searchable_array_bag::~searchable_array_bag()
{

}

bool searchable_array_bag::has(int value) const
{
	for(int i = 0; i < this->size; i++)
	{
		if(this->data[i] == value)
			return (true);
	}
	return(false);
}
