//
// Created by haotian on 7/22/18.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "myslam/common_include.h"
/*
 * Config 类负责参数文件的读取,并在程序任意地方都可随时提供参数的值。所以我们把 Config 写成单件模式(Singleton)。
 * 它只有一个全局对象,当我们设置参数文件时,创建该对象并读取参数文件,随后就可以在任意地方访问参数值,最后在程序结束时自动销毁。
 */
namespace myslam{
    class Config{
    private:
        static std::shared_ptr<Config> config_;
        cv::FileStorage file_;

        Config(){}; // private constructor makes a singleton
    public:
        ~Config();  // close the file when deconstructing

        // set a new config file
        static void setParameterFile( const std::string& filename );

        // access the parameter values
        /*
         * 由于参数实质值可能为整数、浮点数或字符串,所以我们通过一个模板函数 get,来获得任意类型的参数值
         */
        template <typename T>
        static T get(const std::string& key){
            return T( Config::config_->file_[key] );
        }
    };
}

#endif //CONFIG_H
