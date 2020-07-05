/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade
*/

#ifndef __LOADERENCAPSULATION_HPP__
# define __LOADERENCAPSULATION_HPP__

# include <string>
# include <dlfcn.h>
# include <cstring>
# include <dirent.h>

namespace Arcade {
	class loaderEncapsulation {
	public:
		static void *encapC_dlopen(const char *filename, int flag);
		static void *encapC_dlsym(void *handle, const char *symbol);
		static DIR *encapC_opendir(const char *name);
		static struct dirent *encapC_readdir(DIR *dirp);
		static char *encapC_dlerror(void);
		static int encapC_dlclose(void *handle);
		static int encapC_closedir(DIR *dirp);
	private:
	protected:
	};
}

#endif /* __!LOADERENCAPSULATION_HPP__ */