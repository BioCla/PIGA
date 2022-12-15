namespace mathy {
	template <class T>
	int numDigits(T number) {
		int digits = 0;
		if (number < 0)
			digits = 1; // remove this line if '-' counts as a digit
		while (number)
		{
			number /= 10;
			digits++;
		}
		return digits;
	}
}