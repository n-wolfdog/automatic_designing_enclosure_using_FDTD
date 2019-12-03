void	calculation_sound_pressure(struct fact* value, struct fact1* value1)
{
	for(int i = 0; i < (i_max - 1); i++)
	{
		for(int j = 0; j < (j_max - 1); j++)
		{
			for(int k = 0; k < (k_max - 1); k++){
			// inside a body
				if((0 <= i && i < (i_max - 1)) && (0 <= j && j < 150) && (0 <= k && k < 24)) // body section
				{
					value1[0].p[i][j][k] = value1[1].p[i][j][k]
					-(px_coef * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]))
					-(py_coef * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]))
					-(pz_coef * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]));
				}
				else if((20 <= i && i < 60) && (150 <= j && j < 190) && (12 <= k && k < 24)) // hole section
				{
					value1[0].p[i][j][k] = value1[1].p[i][j][k]
					-(px_coef * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]))
					-(py_coef * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]))
					-(pz_coef * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]));
				}

			// outside a body
				else if((0 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))) // analysis space
				{
					value1[0].p[i][j][k] = value1[1].p[i][j][k]
					-(px_coef * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]))
					-(py_coef * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]))
					-(pz_coef * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]));
				}

				else{
					value1[0].p[i][j][k] = 0.0;
				}
			}
		}
	}
}
