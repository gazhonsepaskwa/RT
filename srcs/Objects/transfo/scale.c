/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:20:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/04/01 11:20:41 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Minirt.h"
#include "../../../includes/Vec.h"

void	scale_sp(int btn, t_sp *sp, t_mrt *mrt)
{
	if ((btn != 4 && btn != 5) || (btn == 5 && sp->dia <= 0.5))
		return ;
	if (btn == 4)
		sp->dia += 0.2;
	if (btn == 5)
		sp->dia -= 0.2;
	mrt->rst = true;
}

void	scale_cl(int btn, t_cl *cl, t_mrt *mrt)
{
	if ((btn != 4 && btn != 5 && btn != 6 && btn != 7)
		|| (btn == 5 && cl->h <= 0.5)
		|| (btn == 7 && cl->r <= 0.5))
		return ;
	if (btn == 4)
		cl->h += 0.2;
	if (btn == 5)
		cl->h -= 0.2;
	if (btn == 6)
		cl->r += 0.2;
	if (btn == 7)
		cl->r -= 0.2;
	mrt->rst = true;
}

void	scale(int btn, t_mrt *mrt)
{
	if (mrt->obj.type == OBJ_SP)
		scale_sp(btn, mrt->obj.sh, mrt);
	if (mrt->obj.type == OBJ_CL)
		scale_cl(btn, mrt->obj.sh, mrt);
	if (mrt->obj.type == OBJ_LI)
	{
		if (mrt->li->li < 0.95 && btn == 4)
			mrt->li->li += 0.05;
		if (mrt->li->li > 0.05 && btn == 5)
			mrt->li->li -= 0.05;
		mrt->rst = true;
	}
}
