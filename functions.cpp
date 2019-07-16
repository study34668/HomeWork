using namespace std;

#ifndef FUNCTIONS
#define FUNCTIONS

double toScore(string s)
{
	double score;
	int score_int = 0, num;
	
	int i = 0;
	while( i < s.length() && s[i] != '.' )
	{
		num = s[i]-48;
		if( num < 0 || num > 9 ) return -1;
		score_int = score_int*10 + num;
	}
	
	double score_double = 0.00;
	i = s.length()-1;
	while( i >= 0 && s[i] != '.' )
	{
		num = s[i]-48;
		if( num < 0 || num > 9 ) return -1;
		score_double = score_double/10.0 + (double)num;
	}
	score_double /= 10.0;
	
	score = (double)score_int + score_double;
	return score;
}

int toNumber(string s) //字符变成数字 
{
	int number = 0, len = s.length(), k, num;
	
	if( s[0] == '-' )
	{
		k = -1;
		s.erase(0, 1);
	} else if( s[0] == '+' ) {
		k = 1;
		s.erase(0, 1);
	} else {
		k = 1;
	}
	
	for(int i=0; i<len; i++)
	{
		num = s[i]-48;
		if( num < 0 || num > 9 ) return 0;
		number = number*10 + num;
	}
	
	number *= k;
	
	return number;
}

string toString(int number) //数字变成字符 
{
	int k;
	char num;
	string result = "";
	
	if( number < 0 ) 
	{
		k = -1;
		number *= -1;
	} else {
		k = 1;
	}
	
	if( number == 0 ) return "0";
	
	while( number > 0 )
	{
		num = number % 10 + 48;
		result = num + result;
		number /= 10;
	}
	
    if( k == -1 )
    {
    	result = "-" + result;
	}
	
	return result;
}

#endif
