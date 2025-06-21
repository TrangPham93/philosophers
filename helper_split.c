/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:00:55 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 14:46:07 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static size_t	ft_countword(const char *s, char c)
{
	size_t	count;
	size_t	word_flag;

	count = 0;
	word_flag = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (word_flag == 1)
			{
				count++;
				word_flag = 0;
			}
		}
		else
			word_flag = 1;
		s++;
	}
	if (word_flag == 1)
		count++;
	return (count);
}

static void	ft_free_words_arr(char **word_arr, size_t count)
{
	while (count--)
		free(word_arr[count]);
	free(word_arr);
}

static char	*ft_word_extract(const char *s, char c)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (s[word_len] != c && s[word_len])
	{
		word_len++;
	}
	word = ft_substr(s, 0, word_len);
	if (!word)
	{
		return (NULL);
	}
	return (word);
}

static char	**ft_process(char const *s, char c, size_t i, char **words_arr)
{
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words_arr[i] = ft_word_extract(s, c);
			if (words_arr[i] == NULL)
			{
				ft_free_words_arr(words_arr, i);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	words_arr[i] = NULL;
	return (words_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**words_arr;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = ft_countword(s, c);
	words_arr = malloc((word_count + 1) * sizeof(char *));
	if (words_arr == NULL)
		return (NULL);
	i = 0;
	words_arr = ft_process(s, c, i, words_arr);
	if (!words_arr)
	{
		return (NULL);
	}
	return (words_arr);
}
