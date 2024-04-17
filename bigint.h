/* big shoe lmfao */

// https://infoarena.ro/lucrul-cu-nr-mari
//numerele sunt memorate in ordine inversa intr-un vector
//prima valoare este numarul de cifre
//restul valorilor sunt cifrele in sine
//L C1 C2 C3 C4 ... etc etc
//ex: 2023 -> 4 3 2 0 2

class bigint {
public:
	bigint() { number[0] = 1; number[1] = 0; }
	bigint(unsigned long long n)
	{
		number[0] = 0;
		while (n)
		{
			number[0]++;
			number[number[0]] = n % 10;
			n /= 10;
		}
	}

	bigint(const char* n)
	{
		number[0] = strlen(n);		
		for (int i = 1; i <= number[0]; i++)
			number[i] = n[number[0] - i] - '0';
	}

	bigint(const bigint& n)
	{
		for (int i = 0; i <= n[0]; i++)
			number[i] = n[i];
	}

	bigint& operator=(const bigint& n)
	{
		for (int i = 0; i <= n[0]; i++)
			number[i] = n[i];

		return *this;
	}

	bigint operator+(bigint& b)
	{
		int T = 0;
		bigint& a = *this; //practic doar dau nume la primul bigint pentru readability
		bigint result;

		//adaugarea zerourilor la numarul cu mai putine cifre
		//pentru a preveni calcule cu valori neinitializate
		if (b[0] > a[0])
		{
			for (int i = a[0] + 1; i <= b[0]; i++)
				a[i] = 0;
		}
		else
		{
			for (int i = b[0] + 1; i <= a[0]; i++)
				b[i] = 0;
		}

		//rezultatul va avea numarul de cifre >= cu cel al numarului cel mai mare
		result[0] = (a[0]>=b[0]?a[0]:b[0]);

		//efectiv adunarea cum am invatat-o la pregatitoare
		for (int i = 1; i <= result[0]; i++)
		{
			result[i] = a[i] + b[i] + T;
			T = result[i] / 10;
			result[i] %= 10;
		}

		//daca valoarea cu ordinul cel mai mare a fost >9
		//atunci mutam cifra zecilor pe pozitia urmatoare in vector
		if (T)
			result[++result[0]] = T;

		return result;
	}

	//se presupune ca a > b, altfel se returneaza 0
	bigint operator-(bigint& b)
	{
		int T = 0;
		bigint& a = *this;
		bigint result;

		if (a < b)
		{
			return result; //practic return 0
		}

		//adaugarea zerourilor la numarul cu mai putine cifre
		//pentru a preveni calcule cu valori neinitializate
		for (int i = b[0] + 1; i <= a[0]; i++)
			b[i] = 0;

		result[0] = a[0];

		for (int i = 1; i <= result[0]; i++)
		{
			result[i] = a[i] - (b[i] + T);

			//verificam daca trebuie imprumut
			if (result[i] < 0)
				T = 1;
			else
				T = 0;

			//daca trebuie imprumut inseamna ca valoarea de ordin i a iesit negativa
			if (T)
				result[i] += 10;
		}

		//se reduce numarul de cifre cat timp cifra cea mai semnificativa este 0
		while (!result[result[0]] && result[0] > 1)
			result[0]--;

		return result;
	}

	bigint operator*(unsigned int x)
	{
		unsigned int T = 0;
		bigint result;

		result[0] = number[0];

		//adunare repetata
		for (int i = 1; i <= result[0]; i++)
		{
			result[i] = number[i] * x + T;
			T = result[i] / 10;
			result[i] = result[i] % 10;
		}

		//ce a mai ramas e mutat in pozitiile urmatoare
		while (T)
		{
			result[++result[0]] = T % 10;
			T /= 10;
		}

		return result;
	}

	bigint operator*(bigint& b)
	{
		unsigned int T = 0;
		bigint& a = *this;
		bigint result;

		//initializare numar de cifre
		result[0] = a[0] + b[0] - 1;
		for (int i = 1; i <= a[0] + b[0]; i++)
			result[i] = 0;

		//adunarea produselor intermediare
		for (int i = 1; i <= a[0]; i++)
			for (int j = 1; j <= b[0]; j++)
				result[i + j - 1] += a[i] * b[j];

		//corectarea rezultatului
		for (int i = 1; i <= result[0]; i++)
		{
			result[i] += T;
			T = result[i] / 10;
			result[i] %= 10;
		}

		//ca la adunare, daca ramane ceva in plus adaugam la pozitia urmatoare
		if (T)
			result[++result[0]] = T;

		return result;
	}

	//https://infoarena.ro/lucrul-cu-nr-mari?action=download&file=impart1.jpg&safe_only=true
	bigint operator/(unsigned int& x)
	{
		bigint result;

		result[0] = number[0];

		unsigned int R = 0;
		for (int i = number[0]; i >= 1; i--)
		{
			R = R * 10 + number[i];
			result[i] = R / x;
			R %= x;
		}

		while (!result[result[0]] && result[0] > 1)
			result[0]--;

		return result;
	}

	unsigned int operator%(unsigned int& x)
	{
		unsigned int R = 0;

		for (int i = number[0]; i >= 1; i--)
			R = (R * 10 + number[i]) % x;
		return R;
	}

	//https://infoarena.ro/lucrul-cu-nr-mari?action=download&file=impart2.jpg&safe_only=true
	bigint operator/(bigint& b)
	{
		bigint& a = *this;
		bigint result;
		bigint rest;

		rest[0] = 0;
		result[0] = a[0];

		for (int i = a[0]; i >= 1; i--)
		{
			shift_left(rest, 1);
			rest[1] = a[i];
			result[i] = 0;
			while (b <= rest)
			{
				result[i]++;
				rest = rest - b;
			}
		}

		while (!result[result[0]] && result[0] > 1)
			result[0]--;

		return result;
	}

	bigint operator%(bigint& b)
	{
		bigint& a = *this;
		bigint result;
		bigint rest;

		rest[0] = 0;
		result[0] = a[0];

		for (int i = a[0]; i >= 1; i--)
		{
			shift_left(rest, 1);
			rest[1] = a[i];
			result[i] = 0;
			while (b <= rest)
			{
				result[i]++;
				rest = rest - b;
			}
		}

		return rest;
	}

	bool operator>(bigint& b)
	{
		int cmpResult = bigint_cmp(*this, b, true);
		return (cmpResult == -1 ? false : cmpResult);
	}

	bool operator>=(bigint& b)
	{
		int cmpResult = bigint_cmp(*this, b, true);
		return (cmpResult == -1 ? true : cmpResult);
	}

	bool operator<(bigint& b)
	{
		int cmpResult = bigint_cmp(*this, b, false);
		return (cmpResult == -1 ? false : cmpResult);
	}

	bool operator<=(bigint& b)
	{
		int cmpResult = bigint_cmp(*this, b, false);
		return (cmpResult == -1 ? true : cmpResult);
	}

	bool operator==(bigint& b)
	{
		int cmpResult = bigint_cmp(*this, b, false);
		return (cmpResult == -1 ? true : false);
	}

	bool operator!=(bigint& b)
	{
		int cmpResult = bigint_cmp(*this, b, false);
		return (cmpResult == -1 ? false : true);
	}

	int& operator[](int index) { return number[index]; }
	const int& operator[](int index) const { return number[index]; }

	friend std::ostream& operator<< (std::ostream& out, const bigint& n)
	{
		for (int i = n[0]; i >= 1; i--)
			out << n[i];

		return out;
	}

private:
	int number[150];

	//h=h*10^cnt, utilizat pentru impartirea numerelor mari
	void shift_left(bigint& h, int cnt)
	{
		memmove(&h[cnt + 1], &h[1], sizeof(int) * h[0]);
		memset(&h[1], 0, sizeof(int) * cnt);
		h[0] += cnt;
	}

	int bigint_cmp(bigint& a, bigint& b, bool biggerThan)
	{
		//eliminam zerouri care pot ramane dupa unele operatii
		while (a[0] && a[a[0]] == 0)
			a[0]--;
		while (b[0] && b[b[0]] == 0)
			b[0]--;

		//se compara numarul de cifre
		if (a[0] > b[0])
			return biggerThan;
		else if (a[0] < b[0])
			return !biggerThan;

		//daca numarul de cifre e egal atunci comparam cifra cu cifra
		for (int i = a[0]; i >= 1; i--)
		{
			if (a[i] > b[i])
				return biggerThan;
			else if (a[i] < b[i])
				return !biggerThan;
		}

		return -1;
	}
};