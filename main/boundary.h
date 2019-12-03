// PML model of 3D
/* Description
	- Direction of radiation from a hole: y axis
	- Number of sections: 26
	- Index numbers
		- 1 <- lower area, 2 <- middle area, 3 <- higher area
		- first number <- y axis, second number <- z axis, third number <- x axis
			ex. PML 1.1.1 -> PML 2(y axis: middle) . 1 (z axis: low) . 3(x axis: high)
	
*/
void	PML(int i_max, int j_max, int k_max, struct fact* value, struct fact1* value1,
	double* data_x, double* data_re_x, double* data_vx, double* data_re_vx, double* data_px, double* data_re_px,
	double* data_y, double* data_re_y, double* data_vy, double* data_re_vy, double* data_py, double* data_re_py,
	double* data_z, double* data_re_z, double* data_vz, double* data_re_vz, double* data_pz, double* data_re_pz)
{
	int i, j, k;
	int i_low, i_high, j_low, j_high, k_low, k_high;
	
	for(i = 0; i < (i_max - 1); i++){
		i_low = i;
		i_high = i - (x + L);

		for(j = 0; j < (j_max - 1); j++){
			j_low = j - 190;
			j_high = j - (y + L);

			for(k = 0; k < (k_max - 1); k++){
				k_low = k;
				k_high = k - (z + L);
			// --- section of sides ---
				// PML 1 (y axis: low)
				if(190 <= j && j < (190 + L)){

					// PML 1.1 (z axis: low)
					if(0 <= k && k < L){

						// PML 1.1.1 (attenuation: x axis(negative), y axis(negative), z axis(negative))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
						

						// PML 1.1.2 (attenuation: y axis(negative), z axis(negative))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						//PML 1.1.3 attenuation: x axis(positive), y axis(negative), z axis(negative))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
					}

					// PML 1.2 (z axis: middle)
					if(L <= k && k <= (z + L)){

						// PML 1.2.1 (attenuation: x axis(negative), y axis(negative))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
						}

						// PML 1.2.2 (attenuation: y axis(negative))
						if(((L <= i && i < 20) && (12 <= k && k < 24)) || ((60 <= i && i <= (x + L)) && (12 <= k && k < 24)) || ((L <= i && i <= (x + L)) && (L <= k && k < 12)) || ((L <= i && i <= (x + L)) && (24 <= k && k <= (z + L)))){ //FIXME: split them

							// sound pressure
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].p[i][j][k] = value1[0].py[i][j][k];

							// velocity
							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j -  1][k]);
							}
						}				

						// PML 1.2.3 (attenuation: x axis(positive), y axis(negative))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j + 1][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
						}
					}

					// PML 1.3 (z axis: high)
					if((z + L) <= k && k < (k_max - 1)){
						
						// PML 1.3.1 (attenuation: x axis(negative), y axis(negative), z axis(positive))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
							
							if((z + L) < k){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 1.3.2 (attenuation: y axis(negative), z axis(positive))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((190 + 1) <= j){
								value[0].vy[i][j][k]  = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if((z + L) < k){
							value[0].vz[i][j][k]  = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 1.3.3 (attenuation: x axis(positive), y axis(negative), z axis(positive))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_re_y[j_low] * value1[1].py[i][j][k] - data_re_py[j_low] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((190 + 1) <= j){
								value[0].vy[i][j][k] = data_re_y[j_low] * value[1].vy[i][j][k] - data_re_vy[j_low] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
							if((z + L) < k){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
					}
				}
				
				// PML 2 (y axis: middle)
				if((190 + L) <= j && j <= (y + L))
				{
					// PML 2.1 (z axis: low)
					if(0 <= k && k < L){

						// PML 2.1.1 (attenuation: x axis(negative), z axis(negative))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 2.1.2 (attenuation: z axis(negative))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].pz[i][j][k] = data_z[k_low] * value1[1].pz[i][j][k] - data_pz[k_low] * (value[0].vz[i][j + 1][k] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].pz[i][j][k];

							// velocity
							if(1 <= k){
								value[0].vz[i][j][k] = data_z[k_low] * value[1].vz[i][j][k] - data_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 2.1.3 (attenuation: x axis(positive), z axis(negative))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
					}

					// PML 2.2 (z axis: middle)
					if(L <= k && k <= (z + L)){

						// PML 2.2.1(attenuation: x axis(negative))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}
						}

						// PML 2.2.3 (attenuation: x axis(positive))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k];


							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}
						}
					}

					// PML 2.3 (z axis: high)
					if((z + L) <= k && k < (k_max - 1)){

						// PML 2.3.1 (attenuation: x axis(negative), z axis(positive))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i + 1][j][k] = data_re_x[i_low] * value[1].vx[i + 1][j][k] - data_re_vx[i_low] * (value1[0].p[i + 1][j][k] - value1[0].p[i][j][k]);
							}

							if((z + L) < k){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 2.3.2 (attenuation: z axis(positive))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].pz[i][j][k];

							// velocity
							if((z + L) < k){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 2.3.3 (attenuation: x axis(positive), z axis(positive))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((z + L) < i){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
					}
				}

				// PML 3 (y axis: high)
				if((y + L) <= j && j < (j_max - 1)){

					// PML 3.1 (z axis: low)
					if(0 <= k && k < L){

						// PML 3.1.1 (attenuation: x axis(negative), y axis(positive), z axis(negative))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 3.1.2 (attenuation: y axis(positive), z axis(negative))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((y + L) < j){
							value[0].vy[i][j][k]  = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						//PML 3.1.3 attenuation: x axis(positive), y axis(positive), z axis(negative))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_re_z[k_low] * value1[1].pz[i][j][k] - data_re_pz[k_low] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if(1 <= k){
								value[0].vz[i][j][k] = data_re_z[k_low] * value[1].vz[i][j][k] - data_re_vz[k_low] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
					}

					// PML 3.2 (z axis: middle)
					if(L <= k && k <= (z + L)){

						// PML 3.2.1 (attenuation: x axis(negative), y axis(positive))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
						}

						// PML 3.2.2 (attenuation: y axis(positive))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].p[i][j][k] = value1[0].py[i][j][k];

							// velocity
							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
						}

						// PML 3.2.3 (attenuation: x axis(positive), y axis(positive))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k] = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}
						}
					}

					// PML 3.3 (z axis: high)
					if((z + L) <= k && k < (k_max - 1)){
						
						// PML 3.3.1 (attenuation: x axis(negative), y axis(positive), z axis(positive))
						if(0 <= i && i < L){

							// sound pressure
							value1[0].px[i][j][k] = data_re_x[i_low] * value1[1].px[i][j][k] - data_re_px[i_low] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if(1 <= i){
								value[0].vx[i][j][k] = data_re_x[i_low] * value[1].vx[i][j][k] - data_re_vx[i_low] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if((z + L) < k){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 3.3.2 (attenuation: y axis(positive), z axis(positive))
						if(L <= i && i <= (x + L)){

							// sound pressure
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((y + L) < j){
							value[0].vy[i][j][k] = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if((z + L) < k){
							value[0].vz[i][j][k] = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}

						// PML 3.3.3 (attenuation: x axis(positive), y axis(positive), z axis(positive))
						if((x + L) <= i && i < (i_max - 1)){

							// sound pressure
							value1[0].px[i][j][k] = data_x[i_high] * value1[1].px[i][j][k] - data_px[i_high] * (value[0].vx[i + 1][j][k] - value[0].vx[i][j][k]);
							value1[0].py[i][j][k] = data_y[j_high] * value1[1].py[i][j][k] - data_py[j_high] * (value[0].vy[i][j + 1][k] - value[0].vy[i][j][k]);
							value1[0].pz[i][j][k] = data_z[k_high] * value1[1].pz[i][j][k] - data_pz[k_high] * (value[0].vz[i][j][k + 1] - value[0].vz[i][j][k]);
							value1[0].p[i][j][k] = value1[0].px[i][j][k] + value1[0].py[i][j][k] + value1[0].pz[i][j][k];

							// velocity
							if((x + L) < i){
							value[0].vx[i][j][k]  = data_x[i_high] * value[1].vx[i][j][k] - data_vx[i_high] * (value1[0].p[i][j][k] - value1[0].p[i - 1][j][k]);
							}

							if((y + L) < j){
							value[0].vy[i][j][k]  = data_y[j_high] * value[1].vy[i][j][k] - data_vy[j_high] * (value1[0].p[i][j][k] - value1[0].p[i][j - 1][k]);
							}

							if((z + L) < k){
							value[0].vz[i][j][k]  = data_z[k_high] * value[1].vz[i][j][k] - data_vz[k_high] * (value1[0].p[i][j][k] - value1[0].p[i][j][k - 1]);
							}
						}
					}
				}
			}			
		}
	}
}
