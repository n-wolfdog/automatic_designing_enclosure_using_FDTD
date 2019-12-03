void plotEnclosure(bool ***enc){
for(int i = 0; i < (i_max - 1); i++)
	{
		for(int j = 0; j < (j_max - 1); j++)
		{
			for(int k = 0; k < (k_max - 1); k++){
                // x axis
				// body
				if((i == 0) && (0 <= j && j < 150) && (0 <= k && k < 24)){// lower
					enc[i][j][k] = true;
				}

				if((i == (i_max - 2)) && (0 <= j && j < 150) && (0 <= k && k < 24)){// higher
					enc[i][j][k] = true;
				}

				// hole
				if((i == (20 - 1)) && (150 <= j && j < 190) && (12 <= k && k < 24)){// lower
					enc[i][j][k] = true;
				}

				if((i == (60 - 1)) && (150 <= j && j < 190) && (12 <= k && k < 24)){// higher
					enc[i][j][k] = true;
				}

				// analysis
				if((i == 0) && (190 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))){// lower
					enc[i][j][k] = true;
				}

				if((i == (i_max - 2)) && (190 <= j && j < (j_max - 1)) && (0 <= k && k < (k_max - 1))){// higher
					enc[i][j][k] = true;
				}

			// y axis

				// body
				if((0 <= i && i < (i_max - 1)) && (j == 0) && (0 <= k && k < 24)){// lower
					enc[i][j][k] = true;
				}

				if((0 <= i && i < 20) && (j == ((150 - 1))) && (12 <= k && k < 24)){// higher (x: lower, z: higher)
					enc[i][j][k] = true;
				}

				if((60 <= i && i < (i_max - 1)) && (j == (150 - 1)) && (12 <= k && k < 24)){// higher (x: higher, z: higher)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (j == (150 - 1)) && (0 <= k && k < 12)){// higher (x: middle, z: lower)
					enc[i][j][k] = true;
				}

				// analysis
				if((0 <= i && i < 20) && (j == (190 - 1)) && (12 <= k && k < 24)){// lower (x: lower, z: middle)
					enc[i][j][k] = true;
				}

				if((60 <= i && i < (i_max - 1)) && (j == (190 - 1)) && (12 <= k && k < 24)){// lower (x: higher, z: middle)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (j == (190 - 1)) && (0 <= k && k < 12)){// lower (x: middle, z: lower)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (j == (190 - 1)) && (24 <= k && k < (k_max - 1))){// lower (x: middle, z: higher)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (j == (j_max - 2)) && (0 <= k && k < (k_max - 1))){// lower (x: middle, z: higher)
					enc[i][j][k] = true;
				}

			// z axis

				// body
				if((0 <= i && i < (i_max - 1)) && (0 <= j && j < 20) && (k == 0)){// lower (y: lower)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < 15) && (20 <= j && j < 130) && (k == 0)){// lower (x: lower, y: middle)
					enc[i][j][k] = true;
				}

				if((65 <= i && i < (i_max - 1)) && (20 <= j && j < 130) && (k == 0)){// lower (x: higher, y: middle)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (130 <= j && j < 150) && (k == 0)){// lower (y: higher)
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (0 <= j && j < 150) && (k == (24 - 1))){// lower (y: higher)
					enc[i][j][k] = true;
				}

				// hole
				if((20 <= i && i < 60) && (150 <= j && j < 190) && (k == (12 - 1))){// lower
					enc[i][j][k] = true;
				}

				if((20 <= i && i < 60) && (150 <= j && j < 190) && (k == (24 - 1))){// higher
					enc[i][j][k] = true;
				}

				// analysis
				if((0 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (k == 0)){// lower
					enc[i][j][k] = true;
				}

				if((0 <= i && i < (i_max - 1)) && (190 <= j && j < (j_max - 1)) && (k == (k_max - 2))){// higher
					enc[i][j][k] = true;
				}
            }
        }
    }
}