/*!
 * \file
 * \brief
 */

#ifndef EVENTTIMESTAMP_PROCESSOR_HPP_
#define EVENTTIMESTAMP_PROCESSOR_HPP_

#include <ctime>

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "EventHandler2.hpp"

namespace Processors {
namespace EventTimestamp {

/*!
 * \class EventTimestamp_Processor
 * \brief EventTimestamp processor class.
 */
class EventTimestamp_Processor: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	EventTimestamp_Processor(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~EventTimestamp_Processor();

	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Retrieves data from device.
	 */
	bool onStep();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	void onEvent();

	Base::EventHandler2 h_onEvent;

	Base::DataStreamOut <struct timespec> out_timestamp;

	struct timespec clockResolution;
};

}//: namespace EventTimestamp
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_COMPONENT("EventTimestamp", Processors::EventTimestamp::EventTimestamp_Processor)

#endif /* EVENTTIMESTAMP_PROCESSOR_HPP_ */
