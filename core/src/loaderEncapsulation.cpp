/*
** EPITECH PROJECT, 2020
** libLoader
** File description:
** libLoader
*/

#include "loaderEncapsulation.hpp"

void *Arcade::loaderEncapsulation::encapC_dlopen(const char *filename, int flag)
{
	return (dlopen(filename, flag));
}

void *Arcade::loaderEncapsulation::encapC_dlsym(void *handle, const char *symbol)
{
	return (dlsym(handle, symbol));
}

DIR *Arcade::loaderEncapsulation::encapC_opendir(const char *name)
{
	return (opendir(name));
}

struct dirent *Arcade::loaderEncapsulation::encapC_readdir(DIR *dirp)
{
	return (readdir(dirp));
}

char *Arcade::loaderEncapsulation::encapC_dlerror(void)
{
	return (dlerror());
}

int Arcade::loaderEncapsulation::encapC_dlclose(void *handle)
{
	if (handle != NULL)
		return (dlclose(handle));
	else
		return (0);
}

int Arcade::loaderEncapsulation::encapC_closedir(DIR *dirp)
{
	return (closedir(dirp));
}