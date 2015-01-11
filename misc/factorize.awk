#usage: awk -f factorize.awk
{
	n = int($1)
	m = n
	num = 0
	for ( i = 2; (i^2 <= m) && (m > 2); ) {
		if (m % i == 0) {
			m = m / i
			num++
			factors = (factors == "") ? i : (factors "*" i)
			continue
		}
		i++
	}
	if (num > 0)
		factors = factors "*" m
	print n, (factors == "") ? "is prime" : ("= " factors)
}
