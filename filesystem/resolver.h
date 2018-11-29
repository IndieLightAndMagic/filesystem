/*
    resolver.h -- A simple class for cross-platform path resolution

    Copyright (c) 2015 Wenzel Jakob <wenzel@inf.ethz.ch>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include "path.h"

namespace GTech{
    namespace filesystem{ 
    /**
     * \brief Simple class for resolving paths on Linux/Windows/Mac OS
     *
     * This convenience class looks for a file or directory given its name
     * and a set of search paths. The implementation walks through the
     * search paths in order and stops once the file is found.
     */
    class resolver {
    public:
        typedef std::vector<path>::iterator iterator;
        typedef std::vector<path>::const_iterator const_iterator;

        resolver() {
            m_paths.push_back(path::getcwd());
        }

        size_t size() const { return m_paths.size(); }

        iterator begin() { return m_paths.begin(); }
        iterator end()   { return m_paths.end(); }

        const_iterator begin() const { return m_paths.begin(); }
        const_iterator end()   const { return m_paths.end(); }

        void erase(iterator it) { m_paths.erase(it); }

        void prepend(const path &path) { m_paths.insert(m_paths.begin(), path); }
        void append(const path &path) { m_paths.push_back(path); }
        const path &operator[](size_t index) const { return m_paths[index]; }
        path &operator[](size_t index) { return m_paths[index]; }

        path resolve(const path &value) const {
            for (const_iterator it = m_paths.begin(); it != m_paths.end(); ++it) {
                path combined = *it / value;
                if (combined.exists())
                    return combined;
            }
            return value;
        }

        friend std::ostream &operator<<(std::ostream &os, const resolver &r) {
            os << "resolver[" << std::endl;
            for (size_t i = 0; i < r.m_paths.size(); ++i) {
                os << "  \"" << r.m_paths[i] << "\"";
                if (i + 1 < r.m_paths.size())
                    os << ",";
                os << std::endl;
            }
            os << "]";
            return os;
        }
        /**
        * @brief      Static resolution for asset integration. Suppose you have a foo.dae scene file and within it an object named "Cube". This private funciton will return a tuple of strings: ["scene.dae", "Cube"]. This function is inteded to be used within ResourceManager Class methods as it is private. 
        *
        * @param[in]  spath  The string path of the resource it could be something like ex1: "../scene.dae/Cube" or ex2: "../scene.dae" or ex3:"/Cube" and ex4:"Cube". 
        *
        * @return For ex1 if the file "../scene.dae" actually exists the returned tuple will be ["fullpath/scene.dae","../scene.dae", "Cube"], if it doesn't ["","Cube"]. For ex2 whether it exists or not "../scene.dae" would be correspondently ["../scene.dae", ""], ["",""]. For ex3 and ex4 ["","Cube"]    
        */
        static std::tuple<std::string, std::string, std::string> ResourceNameResolution(const std::string& resourcePathString){

            //Create Path
            auto path = GTech::filesystem::path{resourcePathString};

            //Create a string to store the resource name
            std::string resourceName{};

            //While the path doesn't exist and it is not empty:
            while (!path.exists() && !path.empty()){
                //Add path endpoint to the beginning of resourceName 
                resourceName = resourceName.empty() ? path.filename() : path.filename() + std::string{"/"} + resourceName;

                //Strip the endpoint out of path
                path = path.parent_path();
            }

            //If the path is empty or it doesn't exist return an empty string for the path and a resource name.
            if (path.empty() || !path.exists()){
                return std::make_tuple(std::string{}, std::string{}, resourceName);
            }

            //The path exists: return it and the resource name
            return std::make_tuple(path.make_absolute().str(), path.str(), resourceName);

        }

    private:
        std::vector<path> m_paths;
    };

    }
}