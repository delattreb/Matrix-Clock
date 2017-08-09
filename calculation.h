//
// Created by Bruno on 11/07/2017.
//





//
// ReoderMatrix
//
void ReoderMatrix(char hourbinary[4][7], char binary[4], int line)
{
	for (int i = 0; i <= 3; i++)
		hourbinary[i][line] = binary[i];
}

//
// IntToBinary
//
void IntToBinary(char binary[4], long tempDecimal)
{
	int index = 0, cpt = 0;
	while (tempDecimal != 0)
	{
		binary[index] = (tempDecimal % 2) + 0x30;
		tempDecimal /= 2;
		index++;
		cpt++;
	}
	for (int i = cpt; i <= 3; i++)
		binary[i] = '0';
	strrev(binary); //Reverse character
}
