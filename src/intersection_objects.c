/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/06/06 18:10:52 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// static double _root3 ( double x )
// {
//     double s = 1.;
//     while ( x < 1. )
//     {
//         x *= 8.;
//         s *= 0.5;
//     }
//     while ( x > 8. )
//     {
//         x *= 0.125;
//         s *= 2.;
//     }
//     double r = 1.5;
//     r -= 1./3. * ( r - x / ( r * r ) );
//     r -= 1./3. * ( r - x / ( r * r ) );
//     r -= 1./3. * ( r - x / ( r * r ) );
//     r -= 1./3. * ( r - x / ( r * r ) );
//     r -= 1./3. * ( r - x / ( r * r ) );
//     r -= 1./3. * ( r - x / ( r * r ) );
//     return r * s;
// }

// double root3 ( double x )
// {
//     if ( x > 0 ) return _root3 ( x ); else
//     if ( x < 0 ) return-_root3 (-x ); else
//     return 0.;
// }


// // x - array of size 2
// // return 2: 2 real roots x[0], x[1]
// // return 0: pair of complex roots: x[0]±i*x[1]
// int   SolveP2(double *x, double a, double b) {			// solve equation x^2 + a*x + b = 0
// 	double D = 0.25*a*a - b;
// 	if (D >= 0) {
// 		D = sqrt(D);
// 		x[0] = 0.5*a + D;
// 		x[1] = 0.5*a - D;
// 		return 2;
// 	}
// 	x[0] = 0.5*a;
// 	x[1] = sqrt(-D);
// 	return 0;
// }
// //---------------------------------------------------------------------------
// // x - array of size 3
// // In case 3 real roots: => x[0], x[1], x[2], return 3
// //         2 real roots: x[0], x[1],          return 2
// //         1 real root : x[0], x[1] ± i*x[2], return 1
// int SolveP3(double *x,double a,double b,double c) {	// solve cubic equation x^3 + a*x^2 + b*x + c = 0
// 	double a2 = a*a;
//     double q  = (a2 - 3*b)/9; 
// 	double r  = (a*(2*a2-9*b) + 27*c)/54;
// 	// equation x^3 + q*x + r = 0
//     double r2 = r*r;
// 	double q3 = q*q*q;
// 	double A,B;
// 	if (r2 <= (q3 + eps)) {//<<-- FIXED!
// 		double t=r/sqrt(q3);
// 		if( t<-1) t=-1;
// 		if( t> 1) t= 1;
//         t=acos(t);
//         a/=3; q=-2*sqrt(q);
//         x[0]=q*cos(t/3)-a;
//         x[1]=q*cos((t+TwoPi)/3)-a;
//         x[2]=q*cos((t-TwoPi)/3)-a;
//         return(3);
//     } else {
//         //A =-pow(fabs(r)+sqrt(r2-q3),1./3); 
//         A =-root3(fabs(r)+sqrt(r2-q3)); 
// 		if( r<0 ) A=-A;
// 		B = A==0? 0 : B=q/A;

// 		a/=3;
// 		x[0] =(A+B)-a;
//         x[1] =-0.5*(A+B)-a;
//         x[2] = 0.5*sqrt(3.)*(A-B);
// 		if(fabs(x[2])<eps) { x[2]=x[1]; return(2); }
//         return(1);
//     }
// }// SolveP3(double *x,double a,double b,double c) {	
// //---------------------------------------------------------------------------
// // a>=0!
// void  CSqrt( double x, double y, double &a, double &b) // returns:  a+i*s = sqrt(x+i*y)
// {
// 	double r  = sqrt(x*x+y*y);
// 	if( y==0 ) { 
// 		r = sqrt(r);
// 		if(x>=0) { a=r; b=0; } else { a=0; b=r; }
// 	} else {		// y != 0
// 		a = sqrt(0.5*(x+r));
// 		b = 0.5*y/a;
// 	}
// }
// //---------------------------------------------------------------------------
// int   SolveP4Bi(double *x, double b, double d)	// solve equation x^4 + b*x^2 + d = 0
// {
// 	double D = b*b-4*d;
// 	if( D>=0 ) 
// 	{
// 		double sD = sqrt(D);
// 		double x1 = (-b+sD)/2;
// 		double x2 = (-b-sD)/2;	// x2 <= x1
// 		if( x2>=0 )				// 0 <= x2 <= x1, 4 real roots
// 		{
// 			double sx1 = sqrt(x1);
// 			double sx2 = sqrt(x2);
// 			x[0] = -sx1;
// 			x[1] =  sx1;
// 			x[2] = -sx2;
// 			x[3] =  sx2;
// 			return 4;
// 		}
// 		if( x1 < 0 )				// x2 <= x1 < 0, two pair of imaginary roots
// 		{
// 			double sx1 = sqrt(-x1);
// 			double sx2 = sqrt(-x2);
// 			x[0] =    0;
// 			x[1] =  sx1;
// 			x[2] =    0;
// 			x[3] =  sx2;
// 			return 0;
// 		}
// 		// now x2 < 0 <= x1 , two real roots and one pair of imginary root
// 			double sx1 = sqrt( x1);
// 			double sx2 = sqrt(-x2);
// 			x[0] = -sx1;
// 			x[1] =  sx1;
// 			x[2] =    0;
// 			x[3] =  sx2;
// 			return 2;
// 	} else { // if( D < 0 ), two pair of compex roots
// 		double sD2 = 0.5*sqrt(-D);
// 		CSqrt(-0.5*b, sD2, x[0],x[1]);
// 		CSqrt(-0.5*b,-sD2, x[2],x[3]);
// 		return 0;
// 	} // if( D>=0 ) 
// } // SolveP4Bi(double *x, double b, double d)	// solve equation x^4 + b*x^2 d
// //---------------------------------------------------------------------------
// #define SWAP(a,b) { t=b; b=a; a=t; }
// static void  dblSort3( double &a, double &b, double &c) // make: a <= b <= c
// {
// 	double t;
// 	if( a>b ) SWAP(a,b);	// now a<=b
// 	if( c<b ) {
// 		SWAP(b,c);			// now a<=b, b<=c
// 		if( a>b ) SWAP(a,b);// now a<=b
// 	}
// }
// //---------------------------------------------------------------------------
// int   SolveP4De(double *x, double b, double c, double d)	// solve equation x^4 + b*x^2 + c*x + d
// {
// 	//if( c==0 ) return SolveP4Bi(x,b,d); // After that, c!=0
// 	if( fabs(c)<1e-14*(fabs(b)+fabs(d)) ) return SolveP4Bi(x,b,d); // After that, c!=0

// 	int res3 = SolveP3( x, 2*b, b*b-4*d, -c*c);	// solve resolvent
// 	// by Viet theorem:  x1*x2*x3=-c*c not equals to 0, so x1!=0, x2!=0, x3!=0
// 	if( res3>1 )	// 3 real roots, 
// 	{				
// 		dblSort3(x[0], x[1], x[2]);	// sort roots to x[0] <= x[1] <= x[2]
// 		// Note: x[0]*x[1]*x[2]= c*c > 0
// 		if( x[0] > 0) // all roots are positive
// 		{
// 			double sz1 = sqrt(x[0]);
// 			double sz2 = sqrt(x[1]);
// 			double sz3 = sqrt(x[2]);
// 			// Note: sz1*sz2*sz3= -c (and not equal to 0)
// 			if( c>0 )
// 			{
// 				x[0] = (-sz1 -sz2 -sz3)/2;
// 				x[1] = (-sz1 +sz2 +sz3)/2;
// 				x[2] = (+sz1 -sz2 +sz3)/2;
// 				x[3] = (+sz1 +sz2 -sz3)/2;
// 				return 4;
// 			}
// 			// now: c<0
// 			x[0] = (-sz1 -sz2 +sz3)/2;
// 			x[1] = (-sz1 +sz2 -sz3)/2;
// 			x[2] = (+sz1 -sz2 -sz3)/2;
// 			x[3] = (+sz1 +sz2 +sz3)/2;
// 			return 4;
// 		} // if( x[0] > 0) // all roots are positive
// 		// now x[0] <= x[1] < 0, x[2] > 0
// 		// two pair of comlex roots
// 		double sz1 = sqrt(-x[0]);
// 		double sz2 = sqrt(-x[1]);
// 		double sz3 = sqrt( x[2]);

// 		if( c>0 )	// sign = -1
// 		{
// 			x[0] = -sz3/2;					
// 			x[1] = ( sz1 -sz2)/2;		// x[0]±i*x[1]
// 			x[2] =  sz3/2;
// 			x[3] = (-sz1 -sz2)/2;		// x[2]±i*x[3]
// 			return 0;
// 		}
// 		// now: c<0 , sign = +1
// 		x[0] =   sz3/2;
// 		x[1] = (-sz1 +sz2)/2;
// 		x[2] =  -sz3/2;
// 		x[3] = ( sz1 +sz2)/2;
// 		return 0;
// 	} // if( res3>1 )	// 3 real roots, 
// 	// now resoventa have 1 real and pair of compex roots
// 	// x[0] - real root, and x[0]>0, 
// 	// x[1]±i*x[2] - complex roots, 
// 	// x[0] must be >=0. But one times x[0]=~ 1e-17, so:
// 	if (x[0] < 0) x[0] = 0;
// 	double sz1 = sqrt(x[0]);
// 	double szr, szi;
// 	CSqrt(x[1], x[2], szr, szi);  // (szr+i*szi)^2 = x[1]+i*x[2]
// 	if( c>0 )	// sign = -1
// 	{
// 		x[0] = -sz1/2-szr;			// 1st real root
// 		x[1] = -sz1/2+szr;			// 2nd real root
// 		x[2] = sz1/2; 
// 		x[3] = szi;
// 		return 2;
// 	}
// 	// now: c<0 , sign = +1
// 	x[0] = sz1/2-szr;			// 1st real root
// 	x[1] = sz1/2+szr;			// 2nd real root
// 	x[2] = -sz1/2;
// 	x[3] = szi;
// 	return 2;
// } // SolveP4De(double *x, double b, double c, double d)	// solve equation x^4 + b*x^2 + c*x + d
// //-----------------------------------------------------------------------------
// double N4Step(double x, double a,double b,double c,double d)	// one Newton step for x^4 + a*x^3 + b*x^2 + c*x + d
// {
// 	double fxs= ((4*x+3*a)*x+2*b)*x+c;	// f'(x)
// 	if (fxs == 0) return x;	//return 1e99; <<-- FIXED!
// 	double fx = (((x+a)*x+b)*x+c)*x+d;	// f(x)
// 	return x - fx/fxs;
// } 
// //-----------------------------------------------------------------------------
// // x - array of size 4
// // return 4: 4 real roots x[0], x[1], x[2], x[3], possible multiple roots
// // return 2: 2 real roots x[0], x[1] and complex x[2]±i*x[3], 
// // return 0: two pair of complex roots: x[0]±i*x[1],  x[2]±i*x[3], 
// int   quadratic_equation(double *x,double a,double b,double c,double d) {	// solve equation x^4 + a*x^3 + b*x^2 + c*x + d by Dekart-Euler method
// 	// move to a=0:
// 	double d1 = d + 0.25*a*( 0.25*b*a - 3./64*a*a*a - c);
// 	double c1 = c + 0.5*a*(0.25*a*a - b);
// 	double b1 = b - 0.375*a*a;
// 	int res = depressed_quartic_equation(x, b1, c1, d1);
// 	if( res == 4) 
// 		{ x[0]-= a/4; x[1]-= a/4; x[2]-= a/4; x[3]-= a/4; }
// 	else if (res==2) 
// 		{ 
// 			x[0]-= a/4; 
// 			x[1]-= a/4; 
// 			x[2]-= a/4; 
// 		}
// 	else             
// 		{ 
// 			x[0]-= a/4; 
// 			x[2]-= a/4; 
// 		}
// 	// one Newton step for each real root:
// 	if( res>0 )
// 	{
// 		x[0] = N4Step(x[0], a,b,c,d);
// 		x[1] = N4Step(x[1], a,b,c,d);
// 	}
// 	if( res>2 )
// 	{
// 		x[2] = N4Step(x[2], a,b,c,d);
// 		x[3] = N4Step(x[3], a,b,c,d);
// 	}
// 	return res;
// }


int 	intersection_torus(t_ray *ray, void *tr, double *t)
{
 	t_torus *tor;
  	tor = (t_torus *)tr;
  	int res;
  	double root[4];

  	t_vect C1 = tor->pos;
  	t_vect A1 = tor->dir;
  	double R = tor->maj_r;
	double r = tor->min_r;
  	t_vect Q = vector_substract(&ray->origin, &C1);
  	double u = vector_dot_product(&A1, &Q);
  	double v = vector_dot_product(&A1, &ray->dir);

  	double a = 1 - v * v;
  	double b = 2 * (vector_dot_product(&Q, &ray->dir) - u * v);
  	double c = vector_dot_product(&Q, &Q) - u * u;
	double d = vector_dot_product(&Q, &Q) + R * R - r * r;

	double A4 = 1;
	t_vect tmp2 = vector_mult(4, &Q);
	double B4 = vector_dot_product(&tmp2, &ray->dir);
	double C4 = 2 * d + (B4 * B4)/4 - 4 * R * R * a;
	double D4 = B4 * d - 4 * R * R * b;
	double E4 = d * d - 4 * R * R * c;
	//res = quadratic_equation(root, A4, B4, C4, D4, E4);
	//знайти найменше невідємне число в root	
	res =0;
	return (res);
}


int 	intersection_triangle(t_ray *r, void *triangle, double *t) // Möller–Trumbore intersection algorithm
{
	t_triangle	*tr;
	double 		det;
	double 		u;
	double 		v;
	t_vect 		tvec;
	t_vect 		qvec;
	double 		t0;

	tr = (t_triangle *)triangle;
	t_vect pvec = vector_cross_product(&r->dir, &tr->v1);
	det = vector_dot_product(&tr->v0, &pvec);
	if (fabs(det) > 0.000001f)
	{
		det = 1.0 / det;
		tvec = vector_substract(&r->origin, &tr->a);
		u = vector_dot_product(&tvec, &pvec) * det;
		if (u < 0.0f || u > 1.0f)
			return(0);
		qvec = vector_cross_product(&tvec, &tr->v0);
		v = vector_dot_product(&r->dir, &qvec) * det;
		if (v < 0.0f || u + v > 1.0f)
	 		return (0);
	 	t0 = vector_dot_product(&tr->v1, &qvec) * det;
	 	if (t0 > 0.000001f)
	 	{	
	 		*t = t0;
	 		return(1);
		}
	}
	return (0);
}


int		intersection_cylinder(t_ray *r, void *c, double *t)
{
	t_cylinder	*cyl;
	t_vect		tm1;
	t_vect		tm2;
	t_vect		delta;
	t_equation	n;

	cyl = (t_cylinder *)c;
	tm1 = vector_mult(vector_dot_product(&r->dir, &cyl->dir), &cyl->dir);
	tm1 = vector_substract(&r->dir, &tm1);
	n.a = vector_dot_product(&tm1, &tm1);
	delta = vector_substract(&r->origin, &cyl->pos);
	tm2 = vector_mult(vector_dot_product(&delta, &cyl->dir), &cyl->dir);
	tm2 = vector_substract(&delta, &tm2);
	n.b = 2 * vector_dot_product(&tm1, &tm2);
	n.c = vector_dot_product(&tm2, &tm2) - pow(cyl->r, 2);
	return (quadratic_equation(&n, t));
}

int		intersection_plane(t_ray *r, void *plane, double *t)
{
	t_plane *p;
	double	t0;
	int		i;
	t_vect	point;

	p = (t_plane *)plane;
	i = 0;
	if (vector_dot_product(&p->norm, &r->dir) != 0)
	{
		point = vector_substract(&p->point, &r->origin);
		t0 = vector_dot_product(&p->norm, &point) / \
			vector_dot_product(&p->norm, &r->dir);
		if (t0 > 0.00001f)
		{
			i = 1;
			*t = t0;
		}
	}
	return (i);
}

int		intersection_cone(t_ray *r, void *cone, double *t)
{
	t_cone		*cn;
	t_vect		tm1;
	t_vect		tm2;
	t_vect		delta;
	t_equation	n;

	cn = (t_cone *)cone;
	tm1 = vector_mult(vector_dot_product(&r->dir, &cn->dir), &cn->dir);
	tm1 = vector_substract(&r->dir, &tm1);
	n.a = pow(cos(cn->rad), 2) * vector_dot_product(&tm1, &tm1) - \
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&r->dir, &cn->dir), 2);
	delta = vector_substract(&r->origin, &cn->pos);
	tm2 = vector_mult(vector_dot_product(&delta, &cn->dir), &cn->dir);
	tm2 = vector_substract(&delta, &tm2);
	n.b = 2 * pow(cos(cn->rad), 2) * vector_dot_product(&tm1, &tm2) - \
			2 * pow(sin(cn->rad), 2) * vector_dot_product(&r->dir, &cn->dir) * \
				vector_dot_product(&delta, &cn->dir);
	n.c = pow(cos(cn->rad), 2) * vector_dot_product(&tm2, &tm2) - \
			pow(sin(cn->rad), 2) * pow(vector_dot_product(&delta, &cn->dir), 2);
	return (quadratic_equation(&n, t));
}

int		intersection_sphere(t_ray *r, void *sphere, double *t)
{
	t_vect		dist;
	t_equation	n;
	t_sphere	*s;

	s = (t_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
	return (quadratic_equation(&n, t));
}
