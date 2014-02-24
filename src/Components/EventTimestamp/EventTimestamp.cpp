/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>
#include <errno.h>
#include <boost/bind.hpp>

#include "EventTimestamp.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace EventTimestamp {

EventTimestamp_Processor::EventTimestamp_Processor(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello EventTimestamp_Processor\n";
}

EventTimestamp_Processor::~EventTimestamp_Processor()
{
	LOG(LTRACE) << "Good bye EventTimestamp_Processor\n";
}

void EventTimestamp_Processor::prepareInterface()
{
	LOG(LTRACE) << "EventTimestamp_Processor::initialize\n";

	// Register data streams, events and event handlers HERE!
	registerStream("out_timestamp", &out_timestamp);

	h_onEvent.setup(boost::bind(&EventTimestamp_Processor::onEvent, this));
	registerHandler("onEvent", &h_onEvent);

	if(clock_getres(CLOCK_REALTIME, &clockResolution) == -1){
		LOG(LFATAL) << "clock_getres() failed. " << strerror(errno);
	}

	double resolution = clockResolution.tv_sec + clockResolution.tv_nsec * 1e-9;
	LOG(LNOTICE)<< "Clock resolution (clock_getres()) = " << resolution;
}

bool EventTimestamp_Processor::onInit()
{
	LOG(LTRACE) << "EventTimestamp_Processor::initialize\n";

	return true;
}

void EventTimestamp_Processor::onEvent()
{
	struct timespec currentTime;
	currentTime.tv_nsec = 0;
	currentTime.tv_sec = 0;
	if(clock_gettime(CLOCK_REALTIME, &currentTime) == -1){
		LOG(LFATAL) << "clock_gettime() failed. " << strerror(errno);
	}

	out_timestamp.write(currentTime);
}

bool EventTimestamp_Processor::onFinish()
{
	LOG(LTRACE) << "EventTimestamp_Processor::finish\n";

	return true;
}

bool EventTimestamp_Processor::onStep()
{
	LOG(LTRACE) << "EventTimestamp_Processor::step\n";
	return true;
}

bool EventTimestamp_Processor::onStop()
{
	return true;
}

bool EventTimestamp_Processor::onStart()
{
	return true;
}

}//: namespace EventTimestamp
}//: namespace Processors
