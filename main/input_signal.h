// define a diaphragm
void input_v(struct fact* value)
{
	double T = 0.646/20000;
	coeffi_input = pow(((dt * n - T) / (0.29 * T)), 2.0);
	for(int i = 15; i < 65; i++){
		for(int j = 20; j < 130; j++)
		{
			value[0].vz[i][j][0] = 0.00001 * exp(-1.0 * coeffi_input);
		}
	}
}
