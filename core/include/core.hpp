/*
** EPITECH PROJECT, 2020
** Core
** File description:
** Core
*/

#ifndef __CORE_HPP__
# define __CORE_HPP__

# include <string>
# include <vector>

namespace Arcade {
    class Core {
        public:
            static std::vector<std::string> &readDirectory(const std::string &folder1, const std::string &folder2);
        private:
        protected:
    };
}

#endif /* __!CORE_HPP__ */