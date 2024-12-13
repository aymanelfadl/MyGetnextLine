#include "get_next_line.h"


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *res;
    size_t lens1;
    size_t lens2;

    lens1 = 0;
    lens2 = 0;
    if (!s1 && !s2)
        return NULL;
    if (s1)
        lens1 = ft_strlen(s1);
    if (s2)
        lens2 = ft_strlen(s2);
    res = malloc(lens1 + lens2 + 1);
    if (!res)
        return NULL;
    if (s1)
        ft_memcpy(res, s1, lens1);
    if (s2)
        ft_memcpy(res + lens1, s2, lens2);
    res[lens1 + lens2] = '\0';
    return res;
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dst && !src)
		return (NULL);
    if (dst == src)
        return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0' && *s == '\0')
		return ((char *)s);
	return (NULL);
}
