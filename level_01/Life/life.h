/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 03:20:24 by fbetul            #+#    #+#             */
/*   Updated: 2026/02/24 16:43:23 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE
#define LIFE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


typedef struct s_game
{
	int ancho;
	int alto;
	int iterations;
	int i;
	int j;
	int draw;
	char vivo;
	char dead;
	char** board;
} t_game;

#endif