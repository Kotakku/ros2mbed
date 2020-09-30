#include "mbed.h"
#include <cstdint>
#include <ctime>
#include <chrono>

using std::milli;
using std::micro;
using namespace std::chrono;

namespace ros2
{
namespace ExMbed
{
class SysTimer : public mbed::Timer
{
public:
    SysTimer()
    {
        Timer::start();
    }
};

}

static ExMbed::SysTimer system_timer;
}

extern "C" uint32_t dds_getMilliseconds(void)
{
    return ros2::system_timer.read_ms();
}

extern "C" uint32_t dds_getMicroseconds(void)
{
    return ros2::system_timer.read_us();
}