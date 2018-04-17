#include <jni.h>
#include <string>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class gps_position
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & degrees;
        ar & minutes;
        ar & seconds;
    }
public:
    int degrees;
    int minutes;
    float seconds;

    gps_position(){};
    gps_position(int d, int m, float s) : degrees(d), minutes(m), seconds(s)
    {};
};

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_devyh_boostforandroidexample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    const char* filename = "/storage/emulated/0/seriTest.bin";

    std::ofstream ofs(filename);

    const gps_position g(35, 59, 24.567f);
    {
        boost::archive::text_oarchive oa(ofs);
        oa << g;
    }

    gps_position newg;
    {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> newg;
    }

    char buff[100];
    snprintf(buff, sizeof(buff), "Serialized value (%d, %d, %.3f)", newg.minutes, newg.degrees, newg.seconds);
    std::string buffAsStdStr = buff;

    return env->NewStringUTF(buffAsStdStr.c_str());
}