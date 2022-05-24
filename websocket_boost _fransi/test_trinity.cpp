// Sends a WebSocket message and prints the response

#include "trinity.h"
#include "structOaris.h"
#include "mensajeOaris.h"
#include <iomanip> // for output manipulator std::setprecision()

void updateStructBufferData(Struct_oaris &struct_oaris)
{
    struct_oaris.msg_id =100;
    struct_oaris.time_stamp=1123460121;
    struct_oaris.environment_type = 0;
    struct_oaris.jammer_indication = true;
    struct_oaris.position.lat=0.1234567;
    struct_oaris.position.lon=-0.1234567;
    struct_oaris.position.alt=8888;
    struct_oaris.sensor_track_id=1000;
    struct_oaris.time_of_information=123456789;
    struct_oaris.time_of_initiation=123456789;
    struct_oaris.track_phase=3;
    struct_oaris.velocity_component.angle_of_climb=1.1234;
    struct_oaris.velocity_component.course=12.123456;
    struct_oaris.velocity_component.speed=1234.12345678;
    struct_oaris.subsystem_id=10;
    struct_oaris.sensor_track_pre_identification=2;
    struct_oaris.sensor_track_pre_recognition=1;
};

void convertVectorCharToCharPointer(const std::vector<unsigned char> vector, unsigned char* pointer_char)
{
    std::cout <<  "asa" << std::endl;
    std::cout <<  "vector.size()" << vector.size() << std::endl;
    std::cout <<  "vector[0]" << vector[0] << std::endl;
    for (int i=0;i<vector.size();i++)
    {
        std::cout <<  vector[i] << std::endl;
        pointer_char[i] = vector[i];
    }
};

int main(int argc, char** argv)
{

    // test 1. se guarda bien la estructura de datos en MensajeOaris
    Struct_oaris struct_oaris;
    updateStructBufferData(struct_oaris);
    //std::cout << struct_oaris<< std::endl;
    MensajeOaris mensaje_oaris;

    mensaje_oaris.setStruct(struct_oaris);
    
    
    Struct_oaris getstruct = mensaje_oaris.getStruct();
    //std::cout << getstruct<< std::endl;
    //  end test1 ///////////////////////////////////////////////////
     //error mensaje_oaris.pack();

    // test 2 se prueba el pack de int, 
    std::cout << "\033[1;31mtest 2\033[0m\n"<< std::endl;
    std::vector<unsigned char> buffer_test_int;
    const int variable_test_int = 123456;
    std::cout << "positive int to pack: " << std::setprecision(10) <<  variable_test_int << std::endl;
    Trinity::pack(variable_test_int, buffer_test_int, 32);
    
    int variable_get_int;
    Trinity::unpack(variable_get_int, buffer_test_int, 0, 32,0,32, false);
    std::cout << "positive unpacked float " << variable_get_int << std::endl;
    std::cout << " ********************** " << std::endl;

    //negative
    std::vector<unsigned char> buffer_test_int_neg;
    const int variable_test_int_neg = -123456;
    std::cout << "negative int to pack: " << std::setprecision(10) <<  variable_test_int_neg << std::endl;
    Trinity::pack(variable_test_int_neg, buffer_test_int_neg, 32);
    
    int variable_get_int_neg;
    Trinity::unpack(variable_get_int_neg, buffer_test_int_neg, 0, 32,0,32, true);
    std::cout << "negative unpacked int " << variable_get_int_neg << std::endl;
    std::cout << " ********************** " << std::endl;

    //long
    std::vector<unsigned char> buffer_test_long;
    const long variable_test_long = 12345678123456;
    std::cout << "positive long to pack: " << std::setprecision(10) <<  variable_test_long << std::endl;
    Trinity::pack(variable_test_long, buffer_test_long, 64);
    
    long variable_get_long;
    Trinity::unpack(variable_get_long, buffer_test_long, 0, 64,0,64, false);
    std::cout << "positive unpacked long " << variable_get_long << std::endl;
    std::cout << " ********************** " << std::endl;

    //long negative
    std::vector<unsigned char> buffer_test_long_neg;
    const long variable_test_long_neg = 12345678123456;
    std::cout << "negative long to pack: " << std::setprecision(10) <<  variable_test_long_neg << std::endl;
    Trinity::pack(variable_test_long_neg, buffer_test_long_neg, 64);
    
    long variable_get_long_neg;
    Trinity::unpack(variable_get_long_neg, buffer_test_long_neg, 0, 64,0,64, true);
    std::cout << "negative unpacked long " << variable_get_long_neg << std::endl;
    std::cout << " ********************** " << std::endl;
    // ////

    // test 3 se prueba pack y unpack de float
    std::cout << "\033[1;31mtest 3\033[0m\n"<< std::endl;
    //positive
    std::vector<unsigned char> buffer_test_float;
    const float variable_test_float = 123.123456;
    std::cout << "positive float to pack: " << std::setprecision(10) <<  variable_test_float << std::endl;
    Trinity::pack(variable_test_float, buffer_test_float, 32, 16, 16);
   
    float variable_get_float;
    Trinity::unpack(variable_get_float, buffer_test_float, 0, 32,0,32, false, 16, 16);
    std::cout << "positive unpacked float " << variable_get_float << std::endl;
    std::cout << " ********************** " << std::endl;

    // negative
    std::vector<unsigned char> buffer_test_float_neg;
    const float variable_test_float_neg = -311.123456;
    std::cout << "negative float to pack: " << std::setprecision(10) <<  variable_test_float_neg << std::endl;
    Trinity::pack(variable_test_float_neg, buffer_test_float_neg, 32, 16, 16);
   
    float variable_get_float_neg;
    Trinity::unpack(variable_get_float_neg, buffer_test_float_neg, 0, 32,0,32, true, 16, 16);
    std::cout << "negative unpacked float " << variable_get_float_neg << std::endl;
    std::cout << " ********************** " << std::endl;
    //otro escalado binario
    std::vector<unsigned char> buffer_test_float_neg_esc;
    const float variable_test_float_neg_esc = -188.123456;
    std::cout << "negative float to pack: " << std::setprecision(10) <<  variable_test_float_neg_esc << std::endl;
    Trinity::pack(variable_test_float_neg_esc, buffer_test_float_neg_esc, 32, 10, 22);
   
    float variable_get_float_neg_esc;
    Trinity::unpack(variable_get_float_neg_esc, buffer_test_float_neg_esc, 0, 32,0,32, true, 10, 22);
    std::cout << "negative unpacked float " << variable_get_float_neg_esc << std::endl;
    std::cout << " ********************** " << std::endl;

    //otro escalado binario positivo
    std::vector<unsigned char> buffer_test_float_pos_esc;
    const float variable_test_float_pos_esc = 188.123456;
    std::cout << "positive float to pack: " << std::setprecision(10) <<  variable_test_float_pos_esc << std::endl;
    Trinity::pack(variable_test_float_pos_esc, buffer_test_float_pos_esc, 32, 10, 22);
   
    float variable_get_float_pos_esc;
    Trinity::unpack(variable_get_float_pos_esc, buffer_test_float_pos_esc, 0, 32,0,32, false, 10, 22);
    std::cout << "positive unpacked float " << variable_get_float_pos_esc << std::endl;
    std::cout << " ********************** " << std::endl;

    //doubles

    //positive
    std::vector<unsigned char> buffer_test_double;
    const double variable_test_double = 123.123456;
    std::cout << "positive double to pack: " << std::setprecision(10) <<  variable_test_double << std::endl;
    Trinity::pack(variable_test_double, buffer_test_double, 64, 32, 32);
   
    double variable_get_double;
    Trinity::unpack(variable_get_double, buffer_test_double, 0, 64,0,64, false, 32, 32);
    std::cout << "positive unpacked double " << variable_get_double << std::endl;
    std::cout << " ********************** " << std::endl;

    // negative
    std::vector<unsigned char> buffer_test_double_neg;
    const double variable_test_double_neg = -311.123456;
    std::cout << "negative double to pack: " << std::setprecision(10) <<  variable_test_double_neg << std::endl;
    Trinity::pack(variable_test_double_neg, buffer_test_double_neg, 64, 32, 32);
   
    double variable_get_double_neg;
    Trinity::unpack(variable_get_double_neg, buffer_test_double_neg, 0, 64,0,64, true, 32, 32);
    std::cout << "negative unpacked double " << variable_get_double_neg << std::endl;
    std::cout << " ********************** " << std::endl;

    //otro escalado binario
    std::vector<unsigned char> buffer_test_double_neg_esc;
    const double variable_test_double_neg_esc = -188.123456789;
    std::cout << "negative double to pack: " << std::setprecision(15) <<  variable_test_double_neg_esc << std::endl;
    Trinity::pack(variable_test_double_neg_esc, buffer_test_double_neg_esc, 64, 32, 32);
   
    double variable_get_double_neg_esc;
    Trinity::unpack(variable_get_double_neg_esc, buffer_test_double_neg_esc, 0, 64,0,64, true, 32, 32);
    std::cout << "negative unpacked double " << std::setprecision(15) << variable_get_double_neg_esc << std::endl;
    std::cout << " ********************** " << std::endl;

    //otro escalado binario positivo
    std::vector<unsigned char> buffer_test_double_pos_esc;
    const double variable_test_double_pos_esc = 1881.123456789012;
    std::cout << "positive double to pack: " << std::setprecision(20) <<  variable_test_double_pos_esc << std::endl;
    Trinity::pack(variable_test_double_pos_esc, buffer_test_double_pos_esc, 64, 14, 50);
   
    double variable_get_double_pos_esc;
    Trinity::unpack(variable_get_double_pos_esc, buffer_test_double_pos_esc, 0, 64,0,64, false, 14, 50);
    std::cout << "positive unpacked double " << variable_get_double_pos_esc << std::endl;
    std::cout << " ********************** " << std::endl;
};
     