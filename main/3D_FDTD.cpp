#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// spacial interval

// lengh of analysis [mm]
#define x_lengh_max 8 
#define y_lengh_max 27
#define z_lenth_max 1.8

// spacial interval without PML layer
#define x x_lengh_max * (0.001 / dx) - 2 * L
#define y y_lengh_max * (0.001 / dy) - 2 * L
#define z z_lenth_max * (0.001 / dz) - 2 * L

#define pi acos(-1.00)

#define dx 0.0001
#define dy 0.0001
#define dz 0.00005
#define M 1.0		//coefficient of determination for attenuation frequency characteristic
#define L 6		//depth of absorbing boundary		even number!!!!!!!!!!!!!!!!!

// ege of body [mm]
#define body_x_low 0
#define body_x_high 8
#define body_y_low 0
#define body_y_high 15
#define body_z_low 0
#define body_z_high 1.2

// edge of hole [mm]
#define hole_x_low 2
#define hole_x_high 6
#define hole_y_low 15
#define hole_y_high 19
#define hole_z_low 0.6
#define hole_z_high 1.2

// coefficients for equation of continuity
#define eta_Vmaxx (((M + 1) / (4.0 * (double)L)) * (c * dt / dx) * 27.63)
#define eta_Vmaxy (((M + 1) / (4.0 * (double)L)) * (c * dt / dy) * 27.63)
#define eta_Vmaxz (((M + 1) / (4.0 * (double)L)) * (c * dt / dz) * 27.63)

static int	n, n_max = 0;						// time step, spatial step
static int	i_max, j_max, k_max;				// discrete points on a boundary
static double	c = 344.0;						// sound speed(m/s)
static double	kap = 1.4 * pow(10.0, 5.0);		// bulk modulus of air(N/m^2)
static double	rho = 1.205;					// air density(kg/m^3)
static double	dt = 0.0, dh = 0.0;				// time interval(s) spatial interval(m)
static double   coeffi_p;						// coefficient for calculating particle velovity
static double   coeffi_k;						// coefficient for calculating sound pressure
static double	vx_coef, vy_coef, vz_coef;
static double 	px_coef, py_coef, pz_coef;
static double	HOLE_X_LOW, HOLE_X_HIGH, HOLE_Y_LOW, HOLE_Y_HIGH, HOLE_Z_LOW, HOLE_Z_HIGH;

static double   M1;						    	// coefficient for an absorbing boundary(MUR)

static double coeffi_input;

static double threshold = 100.0;


struct fact{
			double*** vx;
			double*** vy;
        	double*** vz;
		};

struct fact1{
			double*** p;
			double*** px;
			double*** py;
			double*** pz;
		};

#include "input_signal.h"
#include "sound_pressure.h"
#include "particle_velocity.h"
#include "boundary.h"
#include "enclosure.h"

int	main(void)
{
	int i, j, k;
	struct fact* value;
	struct fact1* value1;
	value=(fact*)malloc(sizeof(fact) * (2));
	value1=(fact1*)malloc(sizeof(fact1) * (2));

    // increase cells for absorbing boundary
	i_max = x + 2 * L + 1;
	j_max = y + 2 * L + 1;
	k_max = z + 2 * L + 1;

	// hole model
	HOLE_X_LOW = (0.001 / dx) * hole_x_low;
	HOLE_X_HIGH = (0.001 / dx) * hole_x_high;
	HOLE_Y_LOW = (0.001 / dy) * hole_y_low;
	HOLE_Y_HIGH = (0.001 / dy) * hole_y_high;
	HOLE_Z_LOW = (0.001 / dz) * hole_z_low;
	HOLE_Z_HIGH = (0.001 / dz) * hole_z_high;

    ///////////////////////////////////////////////////// secure memories /////////////////////////////////////////////
	printf("securing memories...\n");
	// particle velocity in the direction of x axis(m/s)
		value[0].vx = (double***)malloc(sizeof(double) * i_max);
		value[1].vx = (double***)malloc(sizeof(double) * i_max);
		if(value[0].vx == NULL || value[1].vx == NULL){
			printf("cannot secure memories. 1\n");
			exit(1);
		}
		else{
			for(i = 0; i < i_max; i++){
				value[0].vx[i] = (double**)malloc(sizeof(double) * j_max);
				value[1].vx[i] = (double**)malloc(sizeof(double) * j_max);
				if(value[0].vx[i] == NULL || value[1].vx[i] == NULL){
					printf("cannot secure memories. 2\n");
					exit(1);
				}
				else
					for(j = 0; j < j_max; j++){
						value[0].vx[i][j] = (double*)malloc(sizeof(double) * k_max);
						value[1].vx[i][j] = (double*)malloc(sizeof(double) * k_max);
						if(value[0].vx[i][j] == NULL || value[1].vx[i][j] == NULL){
							printf("cannot secure memories. 3\n");
							exit(1);
						}
						else;
					}
			}printf("completed. 1\n");
		}

	// particle velocity in the direction of y axis(m/s)
		value[0].vy = (double***)malloc(sizeof(double) * i_max);
		value[1].vy = (double***)malloc(sizeof(double) * i_max);
		if(value[0].vy == NULL || value[1].vy == NULL){
			printf("cannot secure memories. 4\n");
			exit(1);
		}
		else{
			for(i = 0; i < i_max; i++){
				value[0].vy[i] = (double**)malloc(sizeof(double) * j_max);
				value[1].vy[i] = (double**)malloc(sizeof(double) * j_max);
				if(value[0].vy[i] == NULL || value[1].vy[i] == NULL){
					printf("cannot secure memories. 5\n");
					exit(1);
				}
				else
					for(j = 0; j < j_max; j++){
						value[0].vy[i][j] = (double*)malloc(sizeof(double) * k_max);
						value[1].vy[i][j] = (double*)malloc(sizeof(double) * k_max);
						if(value[0].vy[i][j] == NULL || value[1].vy[i][j] == NULL){
							printf("cannot secure memories. 6\n");
							exit(1);
						}
						else;
					}
			}printf("completed. 2\n");
		}

    // particle velocity in the direction of z axis(m/s)
		value[0].vz = (double***)malloc(sizeof(double) * i_max);
		value[1].vz = (double***)malloc(sizeof(double) * i_max);
		if(value[0].vz == NULL || value[1].vz == NULL){
			printf("cannot secure memories. 7\n");
			exit(1);
		}
		else{
			for(i = 0; i < i_max; i++){
				value[0].vz[i] = (double**)malloc(sizeof(double) * j_max);
				value[1].vz[i] = (double**)malloc(sizeof(double) * j_max);
				if(value[0].vz[i] == NULL || value[1].vz[i] == NULL){
					printf("cannot secure memories. 8\n");
					exit(1);
				}
				else
					for(j = 0; j < j_max; j++){
						value[0].vz[i][j] = (double*)malloc(sizeof(double) * k_max);
						value[1].vz[i][j] = (double*)malloc(sizeof(double) * k_max);
						if(value[0].vz[i][j] == NULL || value[1].vz[i][j] == NULL){
							printf("cannot secure memories. 9\n");
							exit(1);
						}				
						else;
					}
			}printf("completed. 3\n");
		}

	// sound pressure(Pa)
		value1[0].p = (double***)malloc(sizeof(double) * (i_max - 1));
		value1[1].p = (double***)malloc(sizeof(double) * (i_max - 1));
		if(value1[0].p == NULL || value1[1].p == NULL){
			printf("cannot secure memories. 10\n");
			exit(1);
		}
		else{
			for(i = 0; i < (i_max - 1); i++){
				value1[0].p[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				value1[1].p[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				if(value1[0].p[i] == NULL || value1[1].p[i] == NULL){
					printf("cannot secure memories. 11\n");
					exit(1);
				}
				else{
					for(j = 0; j < (j_max - 1); j++){
						value1[0].p[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						value1[1].p[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						if(value1[0].p[i][j] == NULL || value1[1].p[i][j] == NULL){
							printf("cannot secure memories. 12\n");
							exit(1);
						}
						else;
					}
				}
			}printf("completed. 4\n");
		}

	// sound pressure(Pa) x axis
		value1[0].px = (double***)malloc(sizeof(double) * (i_max - 1));
		value1[1].px = (double***)malloc(sizeof(double) * (i_max - 1));
		if(value1[0].px == NULL || value1[1].px == NULL){
			printf("cannot secure memories. 13\n");
			exit(1);
		}
		else{
			for(i = 0; i < (i_max - 1); i++){
				value1[0].px[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				value1[1].px[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				if(value1[0].px[i] == NULL || value1[1].px[i] == NULL){
					printf("cannot secure memories. 14\n");
					exit(1);
				}
				else{
					for(j = 0; j < (j_max - 1); j++){
						value1[0].px[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						value1[1].px[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						if(value1[0].px[i][j] == NULL || value1[1].px[i][j] == NULL){
							printf("cannot secure memories. 15\n");
							exit(1);
						}
						else;
					}
				}
			}printf("completed. 5\n");
		}

	// sound pressure(Pa) y axis
		value1[0].py = (double***)malloc(sizeof(double) * (i_max - 1));
		value1[1].py = (double***)malloc(sizeof(double) * (i_max - 1));
		if(value1[0].py == NULL || value1[1].py == NULL){
			printf("cannot secure memories. 16\n");
			exit(1);
		}
		else{
			for(i = 0; i < (i_max - 1); i++){
				value1[0].py[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				value1[1].py[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				if(value1[0].py[i] == NULL || value1[1].py[i] == NULL){
					printf("cannot secure memories. 17\n");
					exit(1);
				}
				else{
					for(j = 0; j < (j_max - 1); j++){
						value1[0].py[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						value1[1].py[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						if(value1[0].py[i][j] == NULL || value1[1].py[i][j] == NULL){
							printf("cannot secure memories. 18\n");
							exit(1);
						}
						else;
					}
				}
			}printf("completed. 6\n");
		}

	// sound pressure(Pa) z axis
		value1[0].pz = (double***)malloc(sizeof(double) * (i_max - 1));
		value1[1].pz = (double***)malloc(sizeof(double) * (i_max - 1));
		if(value1[0].pz == NULL || value1[1].pz == NULL ){
			printf("cannot secure memories. 19\n");
			exit(1);
		}
		else{
			for(i = 0; i < (i_max - 1); i++){
				value1[0].pz[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				value1[1].pz[i] = (double**)malloc(sizeof(double) * (j_max - 1));
				if(value1[0].pz[i] == NULL || value1[1].pz[i] == NULL){
					printf("cannot secure memories. 20\n");
					exit(1);
				}
				else{
					for(j = 0; j < (j_max - 1); j++){
						value1[0].pz[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						value1[1].pz[i][j] = (double*)malloc(sizeof(double) * (k_max - 1));
						if(value1[0].pz[i][j] == NULL || value1[1].pz[i][j] == NULL){
							printf("cannot secure memories. 21\n");
							exit(1);
						}
						else;
					}
				}
			}printf("completed. 7\n");
		}

	////////// plot enclosure //////////
	bool ***enc;

		enc = (bool***)malloc(sizeof(double) * (i_max - 1));
		enc = (bool***)malloc(sizeof(double) * (i_max - 1));
		if(enc == NULL){
			printf("cannot secure memories. 22\n");
			exit(1);
		}
		else{
			for(i = 0; i < (i_max - 1); i++){
				enc[i] = (bool**)malloc(sizeof(double) * (j_max - 1));
				enc[i] = (bool**)malloc(sizeof(double) * (j_max - 1));
				if(enc[i] == NULL){
					printf("cannot secure memories. 23\n");
					exit(1);
				}
				else{
					for(j = 0; j < (j_max - 1); j++){
						enc[i][j] = (bool*)malloc(sizeof(double) * (k_max - 1));
						enc[i][j] = (bool*)malloc(sizeof(double) * (k_max - 1));
						if(enc[i][j] == NULL){
							printf("cannot secure memories. 24\n");
							exit(1);
						}
						else;
					}
				}
			}printf("completed. 8\n");
		}


	//////////////////////////////////////// show variables //////////////////////////////////////////////////
	dt = 5.0 * pow(10.0, -8.0);
	printf("time interval delta t[s]: %le\n", dt);

	dh = 0.0001;
	printf("spatial interval delta h[m]: %le\n", dh);

	printf("Stability condition: %le\n", 1.0 / (c * (sqrt((1.0 / (dx * dx)) + (1.0 / (dy * dy)) + (1.0 / (dz * dz))))));
	if(dt >= 1.0 / (c * (sqrt((1.0 / (dx * dx)) + (1.0 / (dy * dy)) + (1.0 / (dz * dz)))))){
		printf("TIME INTERVAL IS TOO LONG!\n");
		exit(1);
	}

	else{
		printf("Time interval is ok.\n");
	}
	//////////////////////////////////////// definition of coefficients ////////////////////////////////////////

	coeffi_p = (dt / (rho * dh));
	coeffi_k = (kap * dt / dh);

	vx_coef = (dt / (rho * dx));
	vy_coef = (dt / (rho * dy));
	vz_coef = (dt / (rho * dz));

	px_coef = kap * dt / dx;
	py_coef = kap * dt / dy;
	pz_coef = kap * dt / dz;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	double d1, d2, d3;
	double *data_x, *data_y, *data_z, *data_vx, *data_vy, *data_vz, *data_px, *data_py, *data_pz, *data_re_x, *data_re_vx, *data_re_px, *data_re_y, *data_re_vy ,*data_re_py, *data_re_z, *data_re_vz ,*data_re_pz;

	data_x = (double *)calloc((L + 1), sizeof(double));
	data_y = (double *)calloc((L + 1), sizeof(double));
	data_z = (double *)calloc((L + 1), sizeof(double));

	data_vx = (double *)calloc((L + 1), sizeof(double));
	data_px = (double *)calloc(L, sizeof(double));

	data_vy = (double *)calloc((L + 1), sizeof(double));
	data_py = (double *)calloc(L, sizeof(double));

    data_vz = (double *)calloc((L + 1), sizeof(double));
	data_pz = (double *)calloc(L, sizeof(double));


	data_re_x = (double *)calloc((L + 1), sizeof(double));
	data_re_vx = (double *)calloc((L + 1), sizeof(double));
	data_re_px = (double *)calloc(L, sizeof(double));

	data_re_y = (double *)calloc((L + 1), sizeof(double));
	data_re_vy = (double *)calloc((L + 1), sizeof(double));
	data_re_py = (double *)calloc(L, sizeof(double));

    data_re_z = (double *)calloc((L + 1), sizeof(double));
	data_re_vz = (double *)calloc((L + 1), sizeof(double));
	data_re_pz = (double *)calloc(L, sizeof(double));

	for(i = 0; i < L; i++)
	{
		d1 = eta_Vmaxx * pow((((double)i + 1.0) / (double)L), (double)M);
		d2 = eta_Vmaxy * pow((((double)i + 1.0) / (double)L), (double)M);
		d3 = eta_Vmaxz * pow((((double)i + 1.0) / (double)L), (double)M);
		
		data_x[i] = (1.0 - d1) / (1.0 + d1); // Mx
		data_y[i] = (1.0 - d2) / (1.0 + d2); // My
		data_z[i] = (1.0 - d3) / (1.0 + d3); // Mz

		data_vx[i] = vx_coef / (1.0 + d1);
		data_vy[i] = vy_coef / (1.0 + d2);
		data_vz[i] = vz_coef / (1.0 + d3);

		data_px[i] = px_coef / (1.0 + d1);
		data_py[i] = py_coef / (1.0 + d2);
		data_pz[i] = pz_coef / (1.0 + d3);

		data_re_x[(int)L - i - 1] = data_x[i];
		data_re_y[(int)L - i - 1] = data_y[i];
		data_re_z[(int)L - i - 1] = data_z[i];

		data_re_vx[(int)L - i - 1] = data_vx[i];
		data_re_vy[(int)L - i - 1] = data_vy[i];
		data_re_vz[(int)L - i - 1] = data_vz[i];

		data_re_px[(int)L - i - 1] = data_px[i];
		data_re_py[(int)L - i - 1] = data_py[i];
		data_re_pz[(int)L - i - 1] = data_pz[i];
	}

	// plot enclosure data
	for(i = 0; i < i_max; i++){
		for(j = 0; j < j_max; j++){
			for(k = 0; k < k_max; k++){
				enc[i][j][k] = false;				
			}
		}
	}
	plotEnclosure(enc);

	//////////////////////////////////////// setting up files //////////////////////////////////////////////////

	FILE *data_velocity_x, *data_velocity_y, *data_velocity_z, *data_sound_pressure, *data_sound_pressure_td, *data_gaussian_pulse, *data_vx_td, *data_vy_td, *data_vz_td, *data_sound_pressure_test_1_td , *data_sound_pressure_test_2_td, *data_sound_pressure_test_3_td;
	FILE *data_p_pml_1, *data_p_pml_2, *data_p_pml_3, *data_p_pml_4;
	FILE *data_enclosure;
	data_velocity_x = fopen("data_vx.dat", "w"); // velocity distribution of particles on a plane(y axis)
	data_velocity_y = fopen("data_vy.dat", "w"); // velocity distribution of particles on a plane (x axis)
	data_velocity_z = fopen("data_vz.dat", "w"); // sound pressure distribution on a plane
	data_sound_pressure = fopen("data_p.dat", "w"); // sound pressure distribution at points of observation
	data_sound_pressure_td = fopen("data_p_td.dat", "w"); // sound pressure distribution on time domain at points of observation
	data_gaussian_pulse = fopen("data_gaussian_pulse.dat", "w"); // gaussian pulse of particle velocity
	data_vx_td = fopen("data_vx_td.dat", "w");
	data_vy_td = fopen("data_vy_td.dat", "w");
	data_vz_td = fopen("data_vz_td.dat", "w");
	data_sound_pressure_test_1_td = fopen("data_p_test_hole_td.dat", "w");
	data_sound_pressure_test_2_td = fopen("data_p_test_body_td.dat", "w");
	data_sound_pressure_test_3_td = fopen("data_p_test_edge_td.dat", "w");
	data_p_pml_1 = fopen("data_p_pml_1.dat", "w");
	data_p_pml_2 = fopen("data_p_pml_2.dat", "w");
	data_p_pml_3 = fopen("data_p_pml_3.dat", "w");
	data_p_pml_4 = fopen("data_p_pml_4.dat", "w");

	data_enclosure = fopen("data_enclosure.dat", "w");

	//////////////////////////////////////// boundary condition ////////////////////////////////////////////////
	printf("input a value of time step(integer):");
	scanf("%d", &n_max);
	printf("(delta t) * (time step) = %lf\n", dt * n_max);

	// normalization(make all particle velocities and sound pressures as zero)
	for(i = 0; i < i_max; i++){
		for(j = 0; j < j_max; j++){
			for(k = 0; k < k_max; k++){
				value[0].vx[i][j][k] = 0.0;
				value[1].vx[i][j][k] = 0.0;
				value[0].vy[i][j][k] = 0.0;
				value[1].vy[i][j][k] = 0.0;
				value[0].vz[i][j][k] = 0.0;
				value[1].vz[i][j][k] = 0.0;				
			}
		}
	}

	for(i = 0; i < (i_max - 1); i++){
		for(j = 0; j < (j_max - 1); j++){
			for(k = 0; k < (k_max - 1); k++){
				value1[0].p[i][j][k] = 0.0;
				value1[1].p[i][j][k] = 0.0;
				value1[0].px[i][j][k] = 0.0;
				value1[1].px[i][j][k] = 0.0;
				value1[0].py[i][j][k] = 0.0;
				value1[1].py[i][j][k] = 0.0;
				value1[0].pz[i][j][k] = 0.0;
				value1[1].pz[i][j][k] = 0.0;				
			}
		}
	}
	printf("normalization has been done.\n");
	printf("calculating...\n");
	
	///////////////////////////////////// FDTD /////////////////////////////////////////////////////////////////
	time_t start = time(NULL);
	// update time step 
	for(n = 0; n < n_max; n++){

		// calculating particle velocities and sound pressures at each points			
		calculation_velocity(value, value1);
		// calculation of sound pressure
		calculation_sound_pressure(value, value1);
		// calculations of sound pressure on an absorbing boundary
		PML(i_max, j_max, k_max, value, value1, data_x, data_re_x, data_vx, data_re_vx, data_px, data_re_px,
																	data_y, data_re_y, data_vy, data_re_vy, data_py, data_re_py,
																	data_z, data_re_z, data_vz, data_re_vz, data_pz, data_re_pz);

		// time shifting
		for(i = 0; i < i_max; i++){
			for(j = 0; j < j_max; j++){
				for(k = 0; k < k_max; k++){
					value[1].vx[i][j][k] = value[0].vx[i][j][k];
					value[1].vy[i][j][k] = value[0].vy[i][j][k];
					value[1].vz[i][j][k] = value[0].vz[i][j][k];
				}
			}
		}

		for(i = 0; i < (i_max - 1); i++){
			for(j = 0; j < (j_max - 1); j++){
				for(k = 0; k < (k_max - 1); k++){
					value1[1].p[i][j][k] = value1[0].p[i][j][k];
					value1[1].px[i][j][k] = value1[0].px[i][j][k];
					value1[1].py[i][j][k] = value1[0].py[i][j][k];
					value1[1].pz[i][j][k] = value1[0].pz[i][j][k];
				}
			}
		}
		fprintf(data_sound_pressure_td, "%le %le\n", n * dt, value1[0].p[40][200][18]); // the point for analysis
		fprintf(data_gaussian_pulse, "%le %le\n", n * dt, value[0].vz[40][75][0]); // middle point of diaphragm
		fprintf(data_vx_td, "%le %le\n", n * dt, value[0].vx[40][200][18]);
		fprintf(data_vy_td, "%le %le\n", n * dt, value[0].vy[40][200][18]);
		fprintf(data_vz_td, "%le %le\n", n * dt, value[0].vz[40][200][18]);
		fprintf(data_sound_pressure_test_1_td, "%le %le\n", n * dt, value1[0].p[40][180][18]);
		fprintf(data_sound_pressure_test_2_td, "%le %le\n", n * dt, value1[0].p[40][75][18]);
		fprintf(data_sound_pressure_test_3_td, "%le %le\n", n * dt, value1[0].p[40][189][18]);
		fprintf(data_p_pml_1, "%le %le\n", n * dt, value1[0].p[15][193][18]);
		fprintf(data_p_pml_2, "%le %le\n", n * dt, value1[0].p[65][193][18]);
		fprintf(data_p_pml_3, "%le %le\n", n * dt, value1[0].p[3][193][18]);
		fprintf(data_p_pml_4, "%le %le\n", n * dt, value1[0].p[77][193][18]);

		if(value1[0].p[40][200][18] >= threshold){
			printf("THE RESULT IS GOING TO INIFINITY!!\n");
			exit(1);
		}
	}

	time_t end = time(NULL);

////////// calculation time //////////
	int caltime, h, m, s;
	caltime = end - start;
	h = caltime / 3600;
	caltime %= 3600;
	m = caltime / 60;
	caltime %= 60;
	s = caltime;
	printf("time: %d:%d:%d\n", h, m, s);
	
////////////////////////////// output ////////////////////////////////////////////////////////////////////////////

		for(i = 0; i < i_max; i++){
			for(j = 0; j < j_max; j++){
				for(k = 0; k < k_max; k++)
				{
					fprintf(data_velocity_x, "%le %le %le %le\n", i * dx, j * dy, k * dz, value[0].vx[i][j][k]);
					fprintf(data_velocity_y, "%le %le %le %le\n", i * dx, j * dy, k * dz, value[0].vy[i][j][k]);
					fprintf(data_velocity_z, "%le %le %le %le\n", i * dx, j * dy, k * dz, value[0].vz[i][j][k]);
				}
				fprintf(data_velocity_x, "\n");
				fprintf(data_velocity_y, "\n");
				fprintf(data_velocity_z, "\n");
			}
			fprintf(data_velocity_x, "\n");
			fprintf(data_velocity_y, "\n");
			fprintf(data_velocity_z, "\n");
		}

		for(i = 0; i < (i_max - 1); i++){
			for(j = 0; j < (j_max - 1); j++){
				for(k = 0; k < (k_max - 1); k++)
				{
					fprintf(data_sound_pressure, "%le %le %le %le\n", i * dx, j * dy, k * dz, value1[0].p[i][j][k]);
					fprintf(data_enclosure, "%le %le %le %le\n", i * dx, j * dy, k * dz, enc[i][j][k]);
				}
				fprintf(data_sound_pressure, "\n");
			}
			fprintf(data_sound_pressure, "\n");
		}

	///////////////////////////////////////////////// free memories //////////////////////////////////////////////
	printf("free memories...\n");
	
	// particle velocity
	for(int i = 0; i < i_max; i++){
		for(int j = 0; j < j_max; j++){
			free(value[0].vx[i][j]);
			free(value[1].vx[i][j]);
			free(value[0].vy[i][j]);
			free(value[1].vy[i][j]);
			free(value[0].vz[i][j]);
			free(value[1].vz[i][j]);
		}
	}

	for(int i = 0; i < i_max; i++){
		free(value[0].vx[i]);
		free(value[1].vx[i]);
		free(value[0].vy[i]);
		free(value[1].vy[i]);
		free(value[0].vz[i]);
		free(value[1].vz[i]);
	}

	free(value[0].vx);
	free(value[1].vx);
	free(value[0].vy);
	free(value[1].vy);
	free(value[0].vz);
	free(value[1].vz);
	free(value);

	//sound pressure
	for(int i = 0; i < (i_max - 1); i++){
		for(int j = 0; j < (j_max - 1); j++){
			free(value1[0].px[i][j]);
			free(value1[1].px[i][j]);
			free(value1[0].py[i][j]);
			free(value1[1].py[i][j]);
			free(value1[0].pz[i][j]);
			free(value1[1].pz[i][j]);
			free(value1[0].p[i][j]);
			free(value1[1].p[i][j]);

			free(enc[i][j]);
		}
	}

	for(int i = 0; i < (i_max - 1); i++){
		free(value1[0].px[i]);
		free(value1[1].px[i]);
		free(value1[0].py[i]);
		free(value1[1].py[i]);
		free(value1[0].pz[i]);
		free(value1[1].pz[i]);
		free(value1[0].p[i]);
		free(value1[1].p[i]);

		free(enc[i]);
	}

	free(value1[0].px);
	free(value1[1].px);
	free(value1[0].py);
	free(value1[1].py);
	free(value1[0].pz);
	free(value1[1].pz);
	free(value1[0].p);
	free(value1[1].p);
	free(value1);

	free(enc);

	// coefficients
	free(data_x);
	free(data_y);
	free(data_z);
	free(data_vx);
	free(data_vy);
	free(data_vz);
	free(data_px);
	free(data_py);
	free(data_pz);
	free(data_re_x);
	free(data_re_y);
	free(data_re_z);
	free(data_re_vx);
	free(data_re_vy);
	free(data_re_vz);
	free(data_re_px);
	free(data_re_py);
	free(data_re_pz);

	printf("Done.\n");
	///////////////////////////////////////////////// close the files ////////////////////////////////////////////

	fclose(data_velocity_x);
	fclose(data_velocity_y);
	fclose(data_velocity_z);
	fclose(data_sound_pressure);
	fclose(data_sound_pressure_td);
	fclose(data_gaussian_pulse);
	fclose(data_vx_td);
	fclose(data_vy_td);
	fclose(data_vz_td);
	fclose(data_sound_pressure_test_1_td);
	fclose(data_sound_pressure_test_2_td);
	fclose(data_sound_pressure_test_3_td);
	fclose(data_p_pml_1);
	fclose(data_p_pml_2);
	fclose(data_p_pml_3);
	fclose(data_p_pml_4);
	fclose(data_enclosure);
	return(0);
}
