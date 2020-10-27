#ifndef ROS2_TIMERBASE_HPP_
#define ROS2_TIMERBASE_HPP_

#include "node_handle.hpp"
#include <chrono>
#include <memory>
#include <functional>

namespace ros2 {

class TimerBase
{
public:
    using SharedPtr = std::shared_ptr<TimerBase>;

    TimerBase(std::chrono::milliseconds msec, std::function<void(void)> callback)
    {
        setInterval(msec.count());
        callback_ = callback;
        last_call_time_ms_ = 0;
    }

    void setInterval(uint32_t msec)
    {
        this->callback_interval_ms_ = msec;
    }

    bool isTimeToCallback()
    {
        if(this->callback_interval_ms_ > 0 && dds_getMilliseconds() - this->last_call_time_ms_ >= this->callback_interval_ms_)
        {
            this->last_call_time_ms_ = dds_getMilliseconds();
            return true;
        }
        return false;
    }

    void call()
    {
        callback_();
    }

private:
    uint32_t callback_interval_ms_;
    uint32_t last_call_time_ms_;
    std::function<void(void)> callback_;
};

}

#endif // ROS2_TIMERBASE_HPP_