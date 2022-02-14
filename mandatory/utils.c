#include "../includes/philosophers.h"

int	positive_atoi(char *str)
{
	int	a;
	int	status;

	a = -1;
	status = 1;
	if (str[0] == '+')
		a++;
	if (!str[a + 1])
		status = 0;
	while (str[++a])
	{
		if (str[a] < '0' || str[a] > '9')
			status = 0;
	}
	if (status)
		return (ft_atoi(str));
	else
		return (-1);
}

unsigned long long	get_time(void)
{
	struct timeval		time;
	unsigned long long	total;

	gettimeofday(&time, NULL);
	total = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (total);
}
