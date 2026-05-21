/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:44:28 by victor            #+#    #+#             */
/*   Updated: 2026/04/23 11:55:09 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void printboard(char *board, int ancho, int alto)
{
	int x;
	int y;

	y = 0;
	while (y < alto)
	{
		x= 0;
		while (x < ancho)
		{
			if(board[ancho*y + x])
				putchar('0');
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

int countvecino(char *board, int ancho, int alto, int x, int y)
{
	int dx;
	int dy;
	int count;
	int vecino_x;
	int vecino_y;
	
	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if(dx == 0 && dy == 0)
			{
				dx++;
				continue;
			}
			vecino_x = dx+x;
			vecino_y = dy+y;
			if (vecino_x >= 0 && vecino_y >= 0 && vecino_x < ancho && vecino_y < alto)
				count += board[vecino_y*ancho + vecino_x];
			dx++;
		}
		dy++;
	}
	return count;
}

void step(char *board, char *next_board, int ancho, int alto)
{
	int x;
	int y;
	int n;

	y = 0;
	while (y < alto)
	{
		x = 0;
		while (x < ancho)
		{
			n = countvecino(board, ancho, alto, x, y);
			if (board[y*ancho +x])
			{
				if (n== 2 || n== 3)
					next_board[y*ancho + x] = 1;
				else
					next_board[y*ancho + x] = 0;
			}
			else
			{
				if (n== 3)
					next_board[y*ancho + x] = 1;
				else
					next_board[y*ancho + x] = 0;
			}
			x++;
		}
		y++;
	}
}

int main (int argc, char *argv[])
{
	if (argc != 4)
		return 1;
	
	int ancho = atoi (argv[1]);
	int alto = atoi(argv[2]);
	int iter = atoi (argv[3]);
	int x = 0;
	int y = 0;
	int i = 0;
	int pencil = 0;
	char *tmp;
	char *board;
	char *next_board;
	char c;

	board = calloc(ancho * alto, 1);
	next_board = calloc(ancho*alto, 1);
	if(!board || !next_board)
		return 1;
	
}