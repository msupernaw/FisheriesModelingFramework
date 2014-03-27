/* 
 * File:   Object.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 9:25 AM
 */

#ifndef OBJECT_HPP
#define	OBJECT_HPP
#include <string>
#include <sstream>

namespace noaa {
    namespace nmfs {

        /*!
         * Creates a unique identifier.
         * @return 
         */
        class ObjectIDGenerator {
        public:
            static ObjectIDGenerator * Instance();

            const unsigned long Next() {
                return ++_id;
            }
        private:

            ObjectIDGenerator() : _id(0) {
            }

            unsigned long _id;
        };

        static ObjectIDGenerator* only_copy;

        inline ObjectIDGenerator *
        ObjectIDGenerator::Instance() {

            if (!only_copy) {
                only_copy = new ObjectIDGenerator();
            }

            return only_copy;
        }

        
        /**
         * Base class for system objects to inherit from.
         */
        class Object {
            uint32_t id;
            std::string name;

        public:

            Object() {
                std::stringstream ss;
                this->id = ObjectIDGenerator::Instance()->Next();
                ss << "noaa::Object[" << this->id << "]";
                this->name = ss.str();
            }

            std::string GetName() const {
                return name;
            }

            void SetName(std::string name) {
                this->name = name;
            }

            uint32_t GetId() const {
                return id;
            }

            virtual std::string ToString() {
                return GetName();
            }

            virtual void Initialize() {

            }

            template<class TYPE>
            bool InstanceOf() {
                TYPE* v = dynamic_cast<TYPE*> (this);
                if (v != 0) {
                    return true;
                } else {
                    return false;
                }
            }

        };

    }
}

std::ostream& operator <<(std::ostream &out, noaa::nmfs::Object &obj) {
    out << obj.ToString();
    return out;
}

std::stringstream& operator <<(std::stringstream &out, noaa::nmfs::Object &obj) {
    out << obj.ToString();
    return out;
}



#endif	/* OBJECT_HPP */

