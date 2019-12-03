void	calculation_velocity(struct fact* value, struct fact1* value1)
{
	input_v(value);
	
	for(int i = 0; i < i_max; i++)
	{
		for(int j = 0; j < j_max; j++)
		{
			for(int k = 0; k < k_max; k++){

			// x axis
				// body
				if(((1 <= i && i < (i_max - 1)) && (0 <= j && j <= 149) && (0 <= k && k < 24))){
					value[0].vx[i][j][k] = value[1].vx[i][j][k] - vx_coef * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
				}

				// hole
				if((21 <= i && i <= (60 - 1)) && (150 <= j && j <= 189) && (12 <= k && k < 24)){
					value[0].vx[i][j][k] = value[1].vx[i][j][k] - vx_coef * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
				}

				// analysis
				if((1 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))){
					value[0].vx[i][j][k] = value[1].vx[i][j][k] - vx_coef * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
				}

			// y axis
				// body
				if((0 <= i && i < (i_max - 1)) && (1 <= j && j <= 149) && (0 <= k && k < 24)){
					value[0].vy[i][j][k] = value[1].vy[i][j][k] - vy_coef * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
				}

				// hole
				if((20 <= i && i < 60) && (150 <= j && j <= 190) && (12 <= k && k < 24)){
					value[0].vy[i][j][k] = value[1].vy[i][j][k] - vy_coef * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
				}

				// analysis
				if((0 <= i && i < (i_max - 1)) && (191 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))){
					value[0].vy[i][j][k] = value[1].vy[i][j][k] - vy_coef * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
				}

			// z axis
				// body
				if((0 <= i && i < (i_max - 1)) && (0 <= j && j <= 149) && (1 <= k && k < 24)){
					value[0].vz[i][j][k] = value[1].vz[i][j][k] - vz_coef * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
				}

				// hole
				if((20 <= i && i < 60) && (150 <= j && j < 190) && ((12 + 1) <= k && k < 24)){
					value[0].vz[i][j][k] = value[1].vz[i][j][k] - vz_coef * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
				}

				// analysis
				if((0 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (1 <= k && k < (k_max - 1))){
					value[0].vz[i][j][k] = value[1].vz[i][j][k] - vz_coef * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
				}

		// ---------------------     boundaries     --------------------

			// x axis
				// body
				if((i == 0) && (0 <= j && j < 150) && (0 <= k && k < 24)){// lower
					value[0].vx[i][j][k] = 0.0;
				}

				if((i == (i_max - 1)) && (0 <= j && j < 150) && (0 <= k && k < 24)){// higher
					value[0].vx[i][j][k] = 0.0;
				}

				// hole
				if((i == 20) && (150 <= j && j < 190) && (12 <= k && k < 24)){// lower
					value[0].vx[i][j][k] = 0.0;
				}

				if((i == 60) && (150 <= j && j < 190) && (12 <= k && k < 24)){// higher
					value[0].vx[i][j][k] = 0.0;
				}

				// analysis
				if((i == 0) && (190 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))){// lower
					value[0].vx[i][j][k] = 0.0;
				}

				if((i == (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))){// higher
					value[0].vx[i][j][k] = 0.0;
				}

			// y axis

				// body
				if((0 <= i && i < (i_max - 1)) && (j == 0) && (0 <= k && k < 24)){// lower
					value[0].vy[i][j][k] = 0.0;
				}

				if((0 <= i && i < 20) && (j == 150) && (12 <= k && k < 24)){// higher (x: lower, z: higher)
					value[0].vy[i][j][k] = 0.0;
				}

				if((60 <= i && i < (i_max - 1)) && (j == 150) && (12 <= k && k < 24)){// higher (x: higher, z: higher)
					value[0].vy[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (j == 150) && (0 <= k && k < 12)){// higher (x: middle, z: lower)
					value[0].vy[i][j][k] = 0.0;
				}

				// analysis
				if((0 <= i && i < 20) && (j == 190) && (12 <= k && k < 24)){// lower (x: lower, z: middle)
					value[0].vy[i][j][k] = 0.0;
				}

				if((60 <= i && i < (i_max - 1)) && (j == 190) && (12 <= k && k < 24)){// lower (x: higher, z: middle)
					value[0].vy[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (j == 190) && (0 <= k && k < 12)){// lower (x: middle, z: lower)
					value[0].vy[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (j == 190) && (24 <= k && k < (k_max - 1))){// lower (x: middle, z: higher)
					value[0].vy[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (j == (j_max - 1)) && (0 <= k && k < (k_max - 1))){// lower (x: middle, z: higher)
					value[0].vy[i][j][k] = 0.0;
				}

			// z axis

				// body
				if((0 <= i && i < (i_max - 1)) && (0 <= j && j < 20) && (k == 0)){// lower (y: lower)
					value[0].vz[i][j][k] = 0.0;
				}

				if((0 <= i && i < 15) && (20 <= j && j < 130) && (k == 0)){// lower (x: lower, y: middle)
					value[0].vz[i][j][k] = 0.0;
				}

				if((65 <= i && i < (i_max - 1)) && (20 <= j && j < 130) && (k == 0)){// lower (x: higher, y: middle)
					value[0].vz[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (130 <= j && j < 150) && (k == 0)){// lower (y: higher)
					value[0].vz[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (0 <= j && j < 150) && (k == 24)){// lower (y: higher)
					value[0].vz[i][j][k] = 0.0;
				}

				// hole
				if((20 <= i && i < 60) && (150 <= j && j < 190) && (k == 12)){// lower
					value[0].vz[i][j][k] = 0.0;
				}

				if((20 <= i && i < 60) && (150 <= j && j < 190) && (k == 24)){// higher
					value[0].vz[i][j][k] = 0.0;
				}

				// analysis
				if((0 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (k == 0)){// lower
					value[0].vz[i][j][k] = 0.0;
				}

				if((0 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (k == (k_max - 1))){// higher
					value[0].vz[i][j][k] = 0.0;
				}
			}
		}
	}
}
